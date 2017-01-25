#pragma once

#include "Errors.h"
#include "MemoryPool.h"
#include <map>
#include <string>

/**
*	\brief Memory pool manager permits to get a memory pool for allocations
*/
class MemoryPoolManager{
public:
	// Defines
	//-----------------------------------------	
	static const char* const	c_poolsFileXML;

	// Static Methods
	//-----------------------------------------	
	static MemoryPoolManager&	it() { static MemoryPoolManager instance(c_poolsFileXML); return instance; };
	
	// Methods
	//-----------------------------------------	
	MemoryPool*	getPool(const char* const name) 
	{ 
		std::map<std::string, MemoryPool*>::iterator it = m_pool.find(name); 
		if(it != m_pool.end())	return it->second;
		else
		{
			ERROR("Pool "+std::string(name)+" not found.");
			return NULL;
		}
    }

    /* Dump all the pools to some txt files*/
    void	dumpAllPools() const
    { 
        dumpAllPools("");
    }

	/* Dump all the pools to some txt files*/
	void	dumpAllPools(const std::string& prefix) const
	{ 
		std::map<std::string, MemoryPool*>::const_iterator it = m_pool.begin(); 
		for(it; it != m_pool.end(); ++it)
			it->second->dumpToFile(prefix+std::string(it->first)+".txt", 4);
    }

    /* Dump pool to some txt files*/
    void	dumpPool(const std::string& prefix, const MemoryPool* pool) const
    { 
        std::map<std::string, MemoryPool*>::const_iterator it = m_pool.begin(); 
        for(it; it != m_pool.end(); ++it)
            if( pool == it->second )
                it->second->dumpToFile(prefix+std::string(it->first)+".txt", 4);
    }

private:	
	// Ctors/Dtor
	//-----------------------------------------
	MemoryPoolManager(const char* const poolsFileXML);

    bool            isAValidPoolType(const char* poolType) const;
    MemoryPool*     allocateByPoolType(const char* poolType) const;

	// Attributes
	//-----------------------------------------
	std::map<std::string, MemoryPool*>	m_pool;
};
