#pragma once

#include "MemoryPoolManager.h"
#include <new>

/*
*	Overload of operator new for memory pool allocation
*/
inline void* operator new(size_t size, MemoryPool& pool)
{
	void* ptr = pool.allocate(size);
	ASSERT(ptr, "Not enough memory from this pool");
	return ptr;
}

/*
*	Overload of operator delete
*/
inline void operator delete(void* ptr, MemoryPool& pool)
{
	pool.free(ptr);
}

/*
*	Overload of operator delete for memory pool allocation
*/
template<class T> 
void __delete__(T* ptr, MemoryPool& pool)
{
	if (ptr) {
		ptr->~T();
		pool.free(ptr);
	}
}


#undef      DELETE

#define		NEW(memoryPool)						new(*memoryPool)
#define		DELETE(memoryPool, ptr)				__delete__(ptr, *memoryPool)
#define		POOL(name)							(MemoryPoolManager::it().getPool(name))
