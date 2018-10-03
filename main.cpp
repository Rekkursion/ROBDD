#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "IOData.h"
#define DEBUG

int main(int argc, char** argv) {
	if (!getInput(argc, argv))
		return 0;

	initBDD();
	solve();

	return 0;
}

bool getInput(int argc, char** argv) {

	// The number of argument is not 3.
	if (argc != 3) {
		std::cout << "Wrong arguments\n";
		return false;
	}

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
	//std::string line, word;
	//std::vector<std::string> words;

	while (fin >> word) {
		// .i
		if (word == CMD_I) {
			fin >> inputNum;

			possibleNumbers.clear();
			//isPosExist.clear();
			//isPosExist.resize((1 << inputNum) + 1);

			//for (int k = 0; k <= (1 << inputNum); k++)
			//	isPosExist[k] = false;
		}

		// .o
		else if (word == CMD_O) {
			fin >> outputNum;
		}

		// .ilb
		else if (word == CMD_ILB) {
			inputNames.clear();
			inputNames.resize(inputNum);

			for (int k = 0; k < inputNum; k++) {
				fin >> inputNames[k];
			}
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
		}

		// pos
		else {
			int num;
			fin >> num;

			if (num != 1)
				continue;

			std::vector<int> posTmpVec;
			int posTmpVecLen;

			posTmpVec.push_back(0);
			for (int k = inputNum - 1, cif = 1; k >= 0; k--, cif <<= 1) {

				switch (word[k]) {
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

			for (int k = 0; k < posTmpVec.size(); k++) {
				possibleNumbers.insert(posTmpVec[k]);
				//isPosExist[posTmpVec[k]] = true;
			}
		}
	}

	//while (std::getline(fin, line)) {

	//	words.clear();
	//	line += " ";
	//	word = "";

	//	for (int k = 0; k < line.length(); k++) {

	//		if (line[k] == ' ') {
	//			words.push_back(word);
	//			word = "";

	//			if (words[0] == CMD_ILB) {

	//				inputNames.resize(3);
	//				inputNames[0] = line;
	//			}
	//		}
	//		else
	//			word += line[k];
	//	}

	//	// .i
	//	if (words[0] == CMD_I) {
	//		inputNum = string2Int(words[1]);

	//		isPosExist.clear();
	//		isPosExist.resize((1 << inputNum) + 1);

	//		for (int k = 0; k <= (1 << inputNum); k++)
	//			isPosExist[k] = false;
	//	}

	//	// .o
	//	else if (words[0] == CMD_O) {
	//		outputNum = string2Int(words[1]);
	//	}

	//	// .ilb
	//	else if (words[0] == CMD_ILB) {
	//		//inputNames.clear();
	//		//inputNames.resize(inputNum);

	//		/*for (int k = 1; k <= inputNum; k++) {
	//			inputNames[k - 1] = words[k];
	//		}*/
	//	}

	//	// .ob
	//	else if (words[0] == CMD_OB) {
	//		for (std::vector<std::string>::iterator it = words.begin() + 1; it != words.end(); it++)
	//			outputNames.push_back((*it));
	//	}

	//	// .p
	//	else if (words[0] == CMD_P) {
	//		posNum = string2Int(words[1]);
	//	}

	//	// .e
	//	else if (words[0] == CMD_E) {
	//		// end of input
	//	}

	//	// pos
	//	else {
	//		if (words.size() >= 2 && words[1] != "1")
	//			continue;

	//		std::vector<int> posTmpVec;
	//		int posTmpVecLen;

	//		posTmpVec.push_back(0);
	//		for (int k = inputNum - 1, cif = 1; k >= 0; k--, cif <<= 1) {

	//			switch (words[0][k]) {
	//				case '-':
	//					posTmpVecLen = posTmpVec.size();
	//					for (int j = 0; j < posTmpVecLen; j++)
	//						posTmpVec.push_back(posTmpVec[j] + cif);
	//					break;

	//				case '1':
	//					for (int j = 0; j < posTmpVec.size(); j++)
	//						posTmpVec[j] += cif;
	//					break;
	//			}
	//		}

	//		for (int k = 0; k < posTmpVec.size(); k++)
	//			isPosExist[posTmpVec[k]] = true;
	//	}
	//}

	#ifdef DEBUG
	for (std::set<uint>::iterator it = possibleNumbers.begin(); it != possibleNumbers.end(); it++) {
		std::cout << (*it) << std::endl;
	}

	for (int k = 0; k < inputNum; k++)
		std::cout << k << " " << inputNames[k] << std::endl;
	#endif

	return true;
}

int string2Int(std::string str) {
	if (str.length() <= 0)
		return 0;

	int ret = 0;
	bool isNeg = (str[0] == '-') ? true : false;

	for (int k = isNeg ? 1 : 0; k < str.length(); k++) {
		if (str[k] >= 48 && str[k] <= 57)
			ret = (ret * 10) + ((int)str[k] - 48);
	}

	if (isNeg)
		ret *= -1;

	return ret;
}

bool initBDD() {

	BDD.clear();
	BDD.resize(1 << (inputNum + 1));

	int depth = 1;
	int depthChangeUpBound = 1;

	for (int idx = 1; idx < BDD.size(); idx++) {

		BDD[idx] = BDDNode(idx, idx << 1, (idx << 1) + 1, (depth <= inputNum) ? inputNames[depth - 1] : "NULL");
		BDD[idx].isTerminal = (depth > inputNum);

		if (idx == depthChangeUpBound) {
			depth++;
			depthChangeUpBound = (depthChangeUpBound << 1) + 1;
		}
	}

	#ifdef DEBUG
	for (std::vector<BDDNode>::iterator it = BDD.begin() + 1; it != BDD.end(); it++)
		std::cout << it->getName() << ", " << it->getId() << ", " << it->getLeftId() << ", " << it->getRightId() << ", " << it->isTerminal << std::endl;
	#endif

	return true;
}

bool solve() {

	int curPosition = inputNum - 1;
	std::vector<uint> zeroSideNumbers;
	std::vector<uint> oneSideNumbers;

	for (std::set<uint>::iterator it_s = possibleNumbers.begin(); it_s != possibleNumbers.end(); it_s++) {

		// 1 side
		if ((((*it_s) >> curPosition) & 1) == 1) {

		}

		// 0 side
		else {

		}
	}

	return true;
}