#pragma once

#include "MemoryPool.h"
#include "malloc.h"
#include "math.h"
#include <string>
#include "../Errors.h"

/**
*	\brief Standard memory pool permits to allocate and deallocate memory from a pool.
*/
class StandardMemoryPool : public MemoryPool{
public:
	// Methods
	//-----------------------------------------	
	inline void*            allocate(DWORD size);
    inline void             free(void* ptr);
    inline bool             integrityCheck() const;
	inline void             dumpToFile(const std::string& fileName, const DWORD itemsPerLine) const;

    // Static
    //-----------------------------------------	
    static const BYTE       s_minFreeBlockSize = 16;

private:	
	friend class MemoryPoolManager;

	// Ctors/Dtor
	//-----------------------------------------
	StandardMemoryPool(DWORD sizeInBytes, bool boundCheck)
    {
        //Set the bound check
        if(boundCheck) m_boundsCheck = 1;

        //Allocate the total memory
        m_poolMemory = ::new unsigned char[sizeInBytes];

        m_freePoolSize = sizeInBytes - sizeof(Chunk);
        m_totalPoolSize = sizeInBytes;

        // Trash it if required
        if(m_trashOnCreation)
            memset(m_poolMemory, s_trashOnCreation, sizeInBytes);

        //Allocate the first free block
        if(m_boundsCheck)
        {
            m_freePoolSize -= s_boundsCheckSize * 2;

            Chunk freeChunk(sizeInBytes - sizeof(Chunk) - 2 * s_boundsCheckSize);
            freeChunk.write(m_poolMemory + s_boundsCheckSize);
            memcpy( m_poolMemory, s_startBound, s_boundsCheckSize );
            memcpy( m_poolMemory + sizeInBytes - s_boundsCheckSize , s_endBound, s_boundsCheckSize );
        }
        else
        {
            Chunk freeChunk(sizeInBytes - sizeof(Chunk));
            freeChunk.write(m_poolMemory);
        }
	}

	~StandardMemoryPool()
	{
    }

private:	
    // Structure
    //-----------------------------------------	
    class Chunk
    {
    public:
        Chunk(DWORD userDataSize) : m_next(NULL), m_prev(NULL), m_userdataSize(userDataSize), m_free(true) {};
        void write(void* dest){ memcpy(dest, this, sizeof(Chunk) ); }
        void read(void* src){ memcpy(this, src, sizeof(Chunk) ); }

        Chunk*  m_next;
        Chunk*  m_prev;
        DWORD   m_userdataSize;
        bool    m_free;
    };

	// Attributes
	//-----------------------------------------
    BYTE*		        m_poolMemory;
};

#include "StandardMemoryPool.inl"
