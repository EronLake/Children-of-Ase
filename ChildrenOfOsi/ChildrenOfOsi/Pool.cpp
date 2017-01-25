#include <stdio.h>
#include "Pool.h"

MemNode::MemNode() {
	next = NULL;
}

MemNode::MemNode(const MemNode& orig) {
	next = orig.next;
	is_available = orig.is_available;
}

MemNode::~MemNode() {

}

MemNode* MemNode::getNext() {
	return next;
}

bool MemNode::hasNext() {
	if (next != NULL)
		return true;
	else
		return false;
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