#pragma once

// include
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "BDDNode.h"

// define
#define CMD_I	".i"
#define CMD_O	".o"
#define CMD_ILB	".ilb"
#define CMD_OB	".ob"
#define CMD_P	".p"
#define CMD_E	".e"

// define
#define uint unsigned int
#define pause system("PAUSE")
#define DEBUG

// function prototype
bool getInput(int, char**);
bool initBDD();
bool solve(int, int, int);
bool isSameVector(const std::vector<uint>&, const std::vector<uint>&);
bool reduce();
bool outputDotFile();

// global variable
int inputNum;
int outputNum;
int posNum;
std::string dotFileName;

// global variable
std::vector<std::string> inputNames;
std::vector<std::string> outputNames;
std::set<uint> possibleNumbers;
std::vector<BDDNode> BDD;

// function definition
bool isSameVector(const std::vector<uint>& vec1, const std::vector<uint>& vec2) {
	if (vec1.size() != vec2.size())
		return false;

	for (int k = 0; k < vec1.size(); k++) {
		if (vec1[k] != vec2[k])
			return false;
	}

	return true;
}

bool getInput(int argc, char** argv) {

	// The number of argument is not 3.
	if (argc != 3) {
		std::cout << "Wrong arguments\n";
		return false;
	}

	dotFileName = argv[2];

	std::ifstream fin;
	fin.open(argv[1], std::ios::in);

	// PLA file does not exist.
	if (fin.fail()) {
		std::cout << "PLA file not found\n";
		return false;
	}

	/*

	.i 3
	.o 1
	.ilb a b c
	.ob f
	.p 2
	-11 1
	1-1 1
	.e
	*/

	std::string word;
	while (fin >> word) {

		// .i
		if (word == CMD_I) {
			fin >> inputNum;
			possibleNumbers.clear();
		}

		// .o
		else if (word == CMD_O) {
			fin >> outputNum;
		}

		// .ilb
		else if (word == CMD_ILB) {
			inputNames.clear();
			inputNames.resize(inputNum);

			for (int k = 0; k < inputNum; k++)
				fin >> inputNames[k];
		}

		// .ob
		else if (word == CMD_OB) {
			outputNames.clear();
			outputNames.resize(outputNum);

			for (int k = 0; k < outputNum; k++)
				fin >> outputNames[k];
		}

		// .p
		else if (word == CMD_P) {
			fin >> posNum;
		}

		// .e
		else if (word == CMD_E) {
			// end of input
			break;
		}

		// pos
		else {
			std::string input;
			std::string output;
			std::vector<int> posTmpVec;
			int posTmpVecLen;

			input = word;
			posTmpVec.push_back(0);

			fin >> output;

			for (int k = inputNum - 1, cif = 1; k >= 0; k--, cif <<= 1) {
				switch (input[k]) {

					case '-':
						posTmpVecLen = posTmpVec.size();
						for (int j = 0; j < posTmpVecLen; j++)
							posTmpVec.push_back(posTmpVec[j] + cif);
						break;

					case '1':
						for (int j = 0; j < posTmpVec.size(); j++)
							posTmpVec[j] += cif;
						break;
				}
			}

			for (int k = 0; k < posTmpVec.size(); k++)
				possibleNumbers.insert(posTmpVec[k]);
		}
	} // end of while loop for fin
	fin.close();

	#ifdef DEBUG
	for (std::set<uint>::iterator it = possibleNumbers.begin(); it != possibleNumbers.end(); it++)
		std::cout << (*it) << ", ";
	std::cout << std::endl;

	for (int k = 0; k < inputNum; k++)
		std::cout << k << " " << inputNames[k] << std::endl;
	#endif

	return true;
}

bool initBDD() {

	BDD.clear();
	BDD.resize(1 << (inputNum + 1));
	BDD[0].setLeftId(1);
	//BDD[0].setRightId(1);

	int depth = 1;
	int depthChangeUpBound = 1;

	for (int idx = 1; idx < BDD.size(); idx++) {

		// rekkursion
		BDD[idx] = BDDNode(idx, ((idx << 1) < (1 << inputNum)) ? (idx << 1) : (BDD.size() - 1), (((idx << 1) + 1) < (1 << inputNum)) ? ((idx << 1) + 1) : (BDD.size() - 2), (depth <= inputNum) ? inputNames[depth - 1] : "NULL");
		BDD[idx].isTerminal = (depth > inputNum);

		if (idx == depthChangeUpBound) {
			depth++;
			depthChangeUpBound = (depthChangeUpBound << 1) + 1;
		}
	}

	BDDNode::setTerminalId_0(BDD.size() - 1);
	BDDNode::setTerminalId_1(BDD.size() - 2);

	#ifdef DEBUG
	for (std::vector<BDDNode>::iterator it = BDD.begin() + 1; it != BDD.end(); it++)
		std::cout << it->getName() << ", " << it->getId() << ", " << it->getLeftId() << ", " << it->getRightId() << ", " << it->isTerminal << std::endl;
	#endif

	return true;
}

bool solve(int curNodeId, int curNumber, int curNumberBit) {

	if (BDD[curNodeId].isTerminal) {
		int father = curNodeId >> 1;

		if (possibleNumbers.count(curNumber)) {
			if(curNodeId & 1 == 0)
				BDD[father].setLeftId(BDDNode::getTerminalId(1));
			else
				BDD[father].setRightId(BDDNode::getTerminalId(1));
		}
		else {
			if (curNodeId & 1 == 0)
				BDD[father].setLeftId(BDDNode::getTerminalId(0));
			else
				BDD[father].setRightId(BDDNode::getTerminalId(0));
		}

		return true;
	}
	else {
		solve(curNodeId << 1, curNumber << 1, curNumberBit + 1);
		solve((curNodeId << 1) + 1, (curNumber << 1) | 1, curNumberBit + 1);
	}

	#ifdef DEBUG
	std::cout << curNodeId << ", " << curNumber << ", " << curNumberBit << std::endl;
	//pause;
	#endif

	int curPosition = inputNum - 1;
	bool isOkay = true;
	std::vector<uint> remainedNumbers;

	for (std::set<uint>::iterator it_s = possibleNumbers.begin(); it_s != possibleNumbers.end(); it_s++) {

		isOkay = true;
		curPosition = inputNum - 1;

		for (int k = curNumberBit - 1; k >= 0; k--, curPosition--) {
			int possibleNumberMSB = ((*it_s) >> curPosition) & 1;
			int curNumberMSB = (curNumber >> k) & 1;

			if (possibleNumberMSB != curNumberMSB) {
				isOkay = false;
				break;
			}
		}

		if (isOkay)
			remainedNumbers.push_back(*it_s);
	}

	#ifdef DEBUG
	for (std::vector<uint>::iterator it_v = remainedNumbers.begin(); it_v != remainedNumbers.end(); it_v++)
		std::cout << "|" << (*it_v) << "|\n";
	std::cout << std::endl;
	//system("PAUSE");
	#endif

	if (remainedNumbers.empty()) {
		if ((curNodeId & 1) == 0)
			BDD[curNodeId >> 1].setLeftId(BDDNode::getTerminalId(0));
		else
			BDD[curNodeId >> 1].setRightId(BDDNode::getTerminalId(0));

		BDD[curNodeId].setName("NULL");
	}

	return true;
}

bool reduce() {
	int size = 1 << inputNum;
	int noNeedId;
	bool stillHasTheSameNode = false;


	#ifdef DEBUG
	for (int k = 0; k < size; k++) {
		std::cout << BDD[k];
	}
	pause;
	#endif

	// merge the same nodes
	for (int k = 0; k < size; k++) {
		stillHasTheSameNode = false;

		for (int j = k + 1; j < size; j++) {
			if (BDD[j].getName() != "NULL" && BDD[j].getName() == BDD[k].getName() && BDD[j].getLeftId() == BDD[k].getLeftId() && BDD[j].getRightId() == BDD[k].getRightId()) {

				noNeedId = BDD[j].getId();

				BDD[noNeedId].setName("NULL");
				//BDD[j].setId(BDD[k].getId());

				for (int i = 0; i < size; i++) {
					if (BDD[i].getLeftId() == noNeedId)
						BDD[i].setLeftId(BDD[k].getId());

					if (BDD[i].getRightId() == noNeedId)
						BDD[i].setRightId(BDD[k].getId());
				}

				stillHasTheSameNode = true;
				break;
			}
		}

		if (stillHasTheSameNode)
			k = 0;
	}

	#ifdef DEBUG
	for (int k = 0; k < size; k++) {
		std::cout << BDD[k];
	}
	pause;
	#endif

	// remove the redundant nodes
	for (int k = 0; k < size; k++) {
		if (BDD[k].getLeftId() == BDD[k].getRightId()) {

			for (int j = 0; j < size; j++) {
				if (BDD[j].getLeftId() == BDD[k].getId())
					BDD[j].setLeftId(BDD[k].getLeftId());

				if (BDD[j].getRightId() == BDD[k].getId())
					BDD[j].setRightId(BDD[k].getLeftId());
			}
		}
	}

	// remove the redundant nodes (cont' d)
	std::set<uint> existNodes;
	existNodes.clear();
	existNodes.insert(BDD[1].getId());
	for (int k = 0; k < size; k++) {
		if (BDD[k].getName() != "NULL") {
			existNodes.insert(BDD[k].getLeftId());
			existNodes.insert(BDD[k].getRightId());
		}
	}

	// remove the redundant nodes (cont' d)
	for (int k = 0; k < size; k++) {
		if (!existNodes.count(BDD[k].getId())) {
			BDD[k].setName("NULL");
		}
	}

	// remove the duplicated nodes
	for (int k = 0; k < size; k++) {
		for (int j = k + 1; j < size; j++) {
			if (BDD[k] == BDD[j]) {
				BDD[j].setName("NULL");
			}
		}
	}

	return true;
}

bool outputDotFile() {
	std::string dot = "";
	int size = (1 << inputNum);

	std::ofstream fout(dotFileName, std::ios::out);

	fout << "digraph ROBDD {\n";

	for (int k = 0; k < size; k++) {
		if (BDD[k].getName() == "NULL")
			continue;

		fout << "\t" << BDD[k].getId() << " [label=\"" << BDD[k].getName() << "\"]\n";
	}

	fout << "\t" << BDDNode::getTerminalId(0) << " [label=0, shape=box];\n";
	fout << "\t" << BDDNode::getTerminalId(1) << " [label=1, shape=box];\n\n";

	for (int k = 0; k < size; k++) {
		if (BDD[k].getName() == "NULL")
			continue;

		fout << "\t" << BDD[k].getId() << " -> " << BDD[k].getLeftId() << " [label=\"0\", style=solid]\n";
		fout << "\t" << BDD[k].getId() << " -> " << BDD[k].getRightId() << " [label=\"1\", style=solid]\n";
	}
	fout << "}\n";

	fout.close();

	return true;
}