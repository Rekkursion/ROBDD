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

	for (int outputIdx = 0; outputIdx < outputNum; outputIdx++) {
		initBDD();
		solve(1, 0, 0, outputIdx);

		#ifdef DEBUG_MAIN
		for (int k = 0; k < (1 << inputNum); k++) {
			std::cout << BDD[k];
		}
		pause;
		#endif

		reduce();
		outputDotFile(outputIdx);

		#ifdef DEBUG_MAIN
		for (int k = 0; k < (1 << inputNum); k++) {
			std::cout << BDD[k];
		}
		pause;
		#endif
	}

	return 0;
}