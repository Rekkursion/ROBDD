#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class BDDNode {

public:
	BDDNode();
	BDDNode(int, int, int, std::string);
	virtual ~BDDNode();

	friend std::ostream& operator<<(std::ostream&, BDDNode&);
	friend bool operator==(const BDDNode&, const BDDNode&);

	int getId();
	void setId(int);

	int getLeftId();
	void setLeftId(int);

	int getRightId();
	void setRightId(int);

	std::string getName();
	void setName(std::string);

	static int getTerminalId(int);
	static void setTerminalId_0(int);
	static void setTerminalId_1(int);

	bool isTerminal;

private:
	int id;
	int leftId, rightId;
	std::string name;

	static int terminalId_0;
	static int terminalId_1;
};