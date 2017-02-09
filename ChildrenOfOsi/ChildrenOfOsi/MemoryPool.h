#pragma once

#include "stdafx.h"  
#include <stdlib.h>     
#include <time.h>
#include <iostream>
#include <string>
#include "Hero.h"
#include "SplSoldier.h"
#include "LivingObj.h"
#include "WorldObj.h"
#include "NPC.h"
#include "Projectile.h"


class MemoryPool {
public:

	char* next = NULL;
	char* end = NULL;
	size_t pool_size;
	size_t block_size;
	size_t num_of_blocks;

	MemoryPool(size_t size);
	~MemoryPool();
	
	
};