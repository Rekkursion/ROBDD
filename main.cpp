#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "Utility.h"
#define DEBUG_MAIN

int main(int argc, char** argv) {
	if (!getInput(argc, argv))
		return 0;

	initBDD();
	solve(1, 0, 0);

	#ifdef DEBUG_MAIN
	for (int k = 0; k < (1 << inputNum); k++) {
		std::cout << BDD[k];
	}
	pause;
	#endif

	reduce();
	outputDotFile();

	#ifdef DEBUG_MAIN
	for (int k = 0; k < (1 << inputNum); k++) {
		std::cout << BDD[k];
	}
	pause;
	#endif

	return 0;
}