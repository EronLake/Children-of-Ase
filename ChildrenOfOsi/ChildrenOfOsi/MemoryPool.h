#pragma once

#include <string>

#ifdef _DEBUG
#define TRASH_POOLS 1
#else
#define TRASH_POOLS 0
#endif

/**
*   Abstract memory pool class
*/
class MemoryPool
{
public:
    // Methods
    //-----------------------------------------	
    inline virtual void*    allocate(DWORD size) = 0;
    inline virtual void     free(void* ptr) = 0;
    inline virtual bool     integrityCheck() const = 0;
    inline virtual void     dumpToFile(const std::string& fileName, const DWORD itemsPerLine) const = 0;

    inline DWORD            getFreePoolSize() const { return m_freePoolSize; }
    inline DWORD            getTotalPoolSize() const { return m_totalPoolSize; }
    inline bool             hasBoundsCheckOn() const { return m_boundsCheck; }

    // Static
    //-----------------------------------------	
    static const BYTE   s_trashOnCreation = 0xCC;
    static const BYTE   s_trashOnAllocSignature = 0xAB;
    static const BYTE   s_trashOnFreeSignature  = 0xFE;
    static const BYTE   s_boundsCheckSize = 16;
    static const BYTE   s_startBound[s_boundsCheckSize];
    static const BYTE   s_endBound[s_boundsCheckSize];

protected:
    // Ctor/Dtor
    //-----------------------------------------
    MemoryPool() : m_totalPoolSize(0), m_freePoolSize(0), m_trashOnCreation(TRASH_POOLS), m_trashOnAlloc(TRASH_POOLS), m_trashOnFree(TRASH_POOLS), m_boundsCheck(0) {};
    virtual ~MemoryPool(){};

    // Variables
    //-----------------------------------------	
    DWORD       m_totalPoolSize;
    DWORD       m_freePoolSize;

    // Bitfield
    unsigned    m_trashOnCreation : 1;
    unsigned    m_trashOnAlloc : 1;
    unsigned    m_trashOnFree : 1;
    unsigned    m_boundsCheck : 1;

};