#include "stdafx.h"
#include "memManager.h"
#include "MemoryPool.h"

MemoryPool::MemoryPool(size_t size)
{
	LOG("MemoryPool Object Constructed");
}

MemoryPool::~MemoryPool()
{
	LOG("MemoryPool Object Destroyed");
};