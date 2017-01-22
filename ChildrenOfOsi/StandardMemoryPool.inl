/**
*	\brief		allocate the memory
*	\remarks	if the pool has not enough space available, NULL is returned. If the pool has exactly the amount of memory you need, allocation will fail since 16 bytes are required to store the block header.
*               Moreover if bounds check is enabled it will require even more space to write the guards.
*               When guards are enabled all it may happen that a free block is big enough but allocation fail because of the way checks are performed. This is meant to be like this since it allows the whole
*               function to be faster.
*	\return		a pointer for the required size
*/
inline void*	StandardMemoryPool::allocate(DWORD _size)
{
    DWORD requiredSize = _size + sizeof(Chunk);

    // If guards are required, add their size
    if(m_boundsCheck)
        requiredSize += s_boundsCheckSize * 2;

    // Now search for a block big enough
    Chunk* block = (Chunk*)( m_boundsCheck == 1 ? m_poolMemory + s_boundsCheckSize : m_poolMemory);
    while(block)
    {
        if(block->m_free && block->m_userdataSize >= requiredSize ) break;
        block = block->m_next;
    }

    BYTE* blockData = (BYTE*)block;

    // If block is found, return NULL
    if(!block) return NULL;

    // If the block is valid, create a new free block with what remains of the block memory
    DWORD freeUserDataSize = block->m_userdataSize - requiredSize;
    if( freeUserDataSize > s_minFreeBlockSize)
    {
        Chunk freeBlock(freeUserDataSize);
        freeBlock.m_next = block->m_next;
        freeBlock.m_prev = block;
        freeBlock.write( blockData + requiredSize );
        if(freeBlock.m_next)
            freeBlock.m_next->m_prev = (Chunk*)(blockData + requiredSize);
        if(m_boundsCheck)
            memcpy( blockData + requiredSize - s_boundsCheckSize, s_startBound, s_boundsCheckSize );
        block->m_next = (Chunk*)(blockData + requiredSize);
        block->m_userdataSize = _size;
    }

    // If a block is found, update the pool size
    m_freePoolSize -= block->m_userdataSize;

    // Set the memory block
    block->m_free = false;

    // Move the memory around if guards are needed
    if(m_boundsCheck)
    {
        memcpy( blockData - s_boundsCheckSize, s_startBound, s_boundsCheckSize );
        memcpy( blockData + sizeof(Chunk) + block->m_userdataSize, s_endBound, s_boundsCheckSize );
    }

    //Trash on alloc if required
    if(m_trashOnAlloc)
        memset(blockData + sizeof(Chunk), s_trashOnAllocSignature, block->m_userdataSize);
	
	return (blockData + sizeof(Chunk));
}
/**
*	\brief		free the allocated memory
*/
inline void	StandardMemoryPool::free(void* ptr)
{
    // is a valid node?
    if(!ptr) return;
    Chunk* block = (Chunk*)( (BYTE*)ptr - sizeof(Chunk) );
    ASSERT(block->m_free == false, "This block is already free");
    if(block->m_free) return;

    DWORD fullBlockSize = block->m_userdataSize + sizeof(Chunk) + (m_boundsCheck == 1 ? s_boundsCheckSize * 2 : 0);
    m_freePoolSize += block->m_userdataSize;

    Chunk* headBlock = block;
    Chunk* prev = block->m_prev;
    Chunk* next = block->m_next;

    // If the node before is free I merge it with this one
    if(block->m_prev && block->m_prev->m_free)
    {
        headBlock = block->m_prev;
        prev = block->m_prev->m_prev;
        next = block->m_next;

        // Include the prev node in the block size so we trash it as well
        fullBlockSize += m_boundsCheck == 1 ? block->m_prev->m_userdataSize + sizeof(Chunk) + s_boundsCheckSize * 2 : block->m_prev->m_userdataSize + sizeof(Chunk);

        // If there is a next one, we need to update its pointer
        if(block->m_next)
        {
            // We will re point the next
            block->m_next->m_prev = headBlock;

            // Include the next node in the block size if it is free so we trash it as well
            if( block->m_next->m_free )
            {
                // We will point to next's next
                next = block->m_next->m_next;
                if(block->m_next->m_next)
                    block->m_next->m_next->m_prev = headBlock;

                fullBlockSize += m_boundsCheck == 1 ? block->m_next->m_userdataSize + sizeof(Chunk) + s_boundsCheckSize * 2 : block->m_next->m_userdataSize + sizeof(Chunk);
            }
        }
    }
    else
    // If next node is free lets merge it to the current one
    if(block->m_next && block->m_next->m_free)
    {
        headBlock = block;
        prev = block->m_prev;
        next = block->m_next->m_next;

        // Include the next node in the block size so we trash it as well
        fullBlockSize += m_boundsCheck == 1 ? block->m_next->m_userdataSize + sizeof(Chunk) + s_boundsCheckSize * 2 : block->m_next->m_userdataSize + sizeof(Chunk);
    }

    // Create the free block
    BYTE* freeBlockStart = (BYTE*)headBlock;
    if(m_trashOnFree)
        memset( m_boundsCheck == 1 ? freeBlockStart - s_boundsCheckSize : freeBlockStart, s_trashOnFreeSignature, fullBlockSize );

    DWORD freeUserDataSize = fullBlockSize - sizeof(Chunk);
    freeUserDataSize = (m_boundsCheck == 1) ? freeUserDataSize - s_boundsCheckSize * 2 : freeUserDataSize;    

    Chunk freeBlock(freeUserDataSize);
    freeBlock.m_prev = prev;
    freeBlock.m_next = next;
    freeBlock.write(freeBlockStart);

    // Move the memory around if guards are needed
    if(m_boundsCheck)
    {
        memcpy( freeBlockStart - s_boundsCheckSize, s_startBound, s_boundsCheckSize );
        memcpy( freeBlockStart + sizeof(Chunk) + freeUserDataSize, s_endBound, s_boundsCheckSize );
    }
}

/**
*	\brief		Make an integrity test whether the bounds check flag is true
*/
inline bool	StandardMemoryPool::integrityCheck() const
{
    if( m_boundsCheck == 1 ) 
    {
        Chunk* temp = (Chunk*)(m_poolMemory + s_boundsCheckSize);

        while(temp != NULL)
        {
            if(memcmp(((BYTE*)temp) - s_boundsCheckSize, s_startBound, s_boundsCheckSize) != 0) return false; 
            if(memcmp(((BYTE*)temp) + sizeof(Chunk) + temp->m_userdataSize, s_endBound, s_boundsCheckSize) != 0) return false; 

            temp = temp->m_next;
        }
    }
    return true;
}

/**
*	\brief		Dump the memory state to file
*/
inline void	StandardMemoryPool::dumpToFile(const std::string& fileName, const DWORD itemsPerLine) const
{
    FILE* f = NULL;
    fopen_s(&f, fileName.c_str(), "w+");
    if(f)
    {
        fprintf(f, "Memory pool ----------------------------------\n");
        fprintf(f, "Type: Standard Memory\n");
        fprintf(f, "Total Size: %d\n", m_totalPoolSize);
        fprintf(f, "Free Size: %d\n", m_freePoolSize);

        // Now search for a block big enough
        Chunk* block = (Chunk*)( m_boundsCheck == 1 ? m_poolMemory + s_boundsCheckSize : m_poolMemory);

        while(block)
        {
            if(block->m_free)
                fprintf(f, "Free:\t0x%08x [Bytes:%d]\n", block, block->m_userdataSize);
            else
                fprintf(f, "Used:\t0x%08x [Bytes:%d]\n", block, block->m_userdataSize);
            block = block->m_next;
        }

        fprintf(f, "\n\nMemory Dump:\n");
        BYTE* ptr = m_poolMemory;
        BYTE* charPtr = m_poolMemory;

        fprintf(f, "Start: 0x%08x\n", ptr);
        BYTE i = 0;

        // Write the hex memory data
        DWORD bytesPerLine = itemsPerLine * 4;

        fprintf(f, "\n0x%08x: ", ptr);
        fprintf(f, "%02x", *(ptr) );
        ++ptr;
        for(i = 1; ((DWORD)(ptr - m_poolMemory) < m_totalPoolSize); ++i, ++ptr)
        {
            if(i == bytesPerLine)
            {
                // Write all the chars for this line now
                fprintf(f, "  ", charPtr);
                for(DWORD charI = 0; charI<bytesPerLine; ++charI, ++charPtr)
                    fprintf(f, "%c", *charPtr);
                charPtr = ptr;

                // Write the new line memory data
                fprintf(f, "\n0x%08x: ", ptr);
                fprintf(f, "%02x", *(ptr) );
                i = 0;
            }
            else
                fprintf(f, ":%02x", *(ptr) );
        }

        // Fill any gaps in the tab
        if( (DWORD)(ptr - m_poolMemory) >= m_totalPoolSize)
        {
            DWORD lastLineBytes = i;
            for(i; i< bytesPerLine; i++)
                fprintf(f," --");

            // Write all the chars for this line now
            fprintf(f, "  ", charPtr);
            for(DWORD charI = 0; charI<lastLineBytes; ++charI, ++charPtr)
                fprintf(f, "%c", *charPtr);
            charPtr = ptr;
        }
    }

    fclose(f);
}