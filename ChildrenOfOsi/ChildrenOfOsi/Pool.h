#pragma once
#include "stdafx.h"  
#include <stdlib.h>     
#include <time.h>
#include <iostream>
#include <string>
#include "Hero.h"
#include "SplSoldier.h"
#include "LivingObj.h"
#include "LivingObj.h"
#include "WorldObj.h"
#include "NPC.h"
#include "Projectile.h"


#ifndef POOL_H
#define POOL_H

#endif /* POOL_H */

class MemoryPool {
public:
	MemoryPool(size_t size) {};
	~MemoryPool() {};
	char* next = NULL;
	char* end = NULL;
	size_t pool_size;
	size_t block_size;
	size_t num_of_blocks;

};

class MemNode {
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
private:
	MemNode* next;
	bool is_available;
	void* block_pointer;
};

class Warrior {
public:
	Warrior(int hp, bool ali, float _x, float _y)
	{
		health = hp;
		alive = ali;
		x = _x;
		y = _y;
	}

	Warrior() :health(500), alive(true), x(0), y(200) {};

	~Warrior() {};

	int health;
	bool alive;
	float x;
	float y;


};

MemNode* init_pool(MemoryPool *p, size_t bsize);
size_t get_free_pool_size(MemoryPool* p);
void destroy_pool(MemoryPool* p);
MemoryPool* create_pool(size_t sizeInBytes);
void destroy_MemNode_list(MemNode* head_ptr);
MemNode* make_Available(MemNode* head_ptr, MemoryPool* p, size_t node_number);
void* find_available_block(MemNode* head_ptr);



