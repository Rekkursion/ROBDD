#include "BDDNode.h"



int BDDNode::terminalId_0;
int BDDNode::terminalId_1;

BDDNode::BDDNode() {
	id = leftId = rightId = 0;
	name = "NULL";
}

BDDNode::BDDNode(int _id, int _leftId, int _rightId, std::string _name) {
	id = _id;
	leftId = _leftId;
	rightId = _rightId;
	name = _name;
}

BDDNode::~BDDNode() {}

std::ostream& operator<<(std::ostream& outStream, BDDNode& node) {
	outStream << node.getId() << ", " << node.getLeftId() << ", " << node.getRightId() << ", " << node.getName() << std::endl;
	return outStream;
}

bool operator==(const BDDNode& lSide, const BDDNode& rSide) {
	return (lSide.leftId == rSide.leftId && lSide.rightId == rSide.rightId && lSide.name == rSide.name && lSide.id == rSide.id && lSide.isTerminal == rSide.isTerminal);
}

int BDDNode::getId() {
	return id;
}
void BDDNode::setId(int newId) {
	id = newId;
}

int BDDNode::getLeftId() {
	return leftId;
}
void BDDNode::setLeftId(int newLeftId) {
	leftId = newLeftId;
}

int BDDNode::getRightId() {
	return rightId;
}
void BDDNode::setRightId(int newRightId) {
	rightId = newRightId;
}

std::string BDDNode::getName() {
	return name;
}
void BDDNode::setName(std::string newName) {
	name = newName;
}

int BDDNode::getTerminalId(int oneOrZero) {
	if (oneOrZero == 0)
		return terminalId_0;
	else if (oneOrZero == 1)
		return terminalId_1;

	return 0;
}
void BDDNode::setTerminalId_0(int newTerminalId_0) {
	terminalId_0 = newTerminalId_0;
}
void BDDNode::setTerminalId_1(int newTerminalId_1) {
	terminalId_1 = newTerminalId_1;
}