#pragma once
#include "common.h"

class MemNode
{

private:
	MemNode* next;
	bool is_available;
	void* block_pointer;

public:

	MemNode();
	MemNode(const MemNode& orig);
	virtual ~MemNode();
	bool hasNext();
	MemNode* getNext();
	void setNext(MemNode* newNext);
	bool getAvailability();
	void setAvailability(bool avail);
	void* getBlockPointer();
	void setBlockPointer(void* ptr);

};

