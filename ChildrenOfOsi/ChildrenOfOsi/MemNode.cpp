#include "stdafx.h"
#include "MemNode.h"


MemNode::MemNode() {
	next = NULL;
	LOG("MemNode Object Constructed");
}

/*
MemNode::MemNode(const MemNode& orig) {
	next = orig.next;
	is_available = orig.is_available;
	LOG("MemNode Object Constructed");
}
*/
MemNode::~MemNode() {
	LOG("MemNode Object Destroyed");
}


bool MemNode::hasNext() {
	if (next != NULL)
		return true;
	else
		return false;
}

MemNode* MemNode::getNext() {
	return next;
}

void MemNode::setNext(MemNode* newNext) {
	if (newNext == NULL)
		next = NULL;
	else
		next = newNext;
}

bool MemNode::getAvailability() {
	return is_available;
}

void MemNode::setAvailability(bool avail) {
	is_available = avail;
}

void* MemNode::getBlockPointer() {
	return block_pointer;
}

void MemNode::setBlockPointer(void* ptr) {
	block_pointer = ptr;
}