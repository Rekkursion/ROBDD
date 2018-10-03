#pragma once
#include <vector>
#include <string>
#include "BDDNode.h"
#define uint unsigned int

bool getInput(int, char**);
int string2Int(std::string);
bool initBDD();
bool solve();

#define CMD_I	".i"
#define CMD_O	".o"
#define CMD_ILB	".ilb"
#define CMD_OB	".ob"
#define CMD_P	".p"
#define CMD_E	".e"

int inputNum;
int outputNum;
int posNum;

std::vector<std::string> inputNames;
std::vector<std::string> outputNames;
//std::vector<bool> isPosExist;
std::set<uint> possibleNumbers;
std::vector<BDDNode> BDD;