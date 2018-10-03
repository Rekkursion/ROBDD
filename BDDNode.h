#pragma once
#include <string>
#include <vector>

class BDDNode {

public:
	BDDNode();
	BDDNode(int, int, int, std::string);
	virtual ~BDDNode();

	int getId();
	void setId(int);

	int getLeftId();
	void setLeftId(int);

	int getRightId();
	void setRightId(int);

	std::string getName();
	void setName(std::string);

	bool isTerminal;

private:
	int id;
	int leftId, rightId;
	std::string name;
	
};

