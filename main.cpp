#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "Utility.h"

int main(int argc, char** argv) {
	if (!getInput(argc, argv))
		return 0;

	initBDD();
	solve(1, 0, 0);
	reduce();
	outputDotFile();

	for (int k = 0; k < (1 << inputNum); k++) {
		std::cout << BDD[k];
	}

	return 0;
}