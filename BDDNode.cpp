#include "BDDNode.h"



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
