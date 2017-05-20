#pragma once
// file: common.h 
// commonly used libs

#include "stdafx.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <string>
#include <chrono>
#include <thread>
#include <cstring>
#include <cstdint>
#include <array>
#include <iterator>
#include <map>
#include <cstdlib>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <set>

#define SHANGO 1
#define YEMOJA 2
#define OYA 3
#define OSHOSI 4
#define OGUN 5

//static double map_zoom = 1.5; //initialized in main

//Texture* rect = new Texture();
//toggles debug longging statements 

#define DEBUG 1
#define MAP_EDITOR 0
#define START_FULLSCREEN false
#define MOUSE_VISIBLE true
#define LOAD_REGIONS 1 //0==Load Config should be empty || 1==Load All || 2==Load Oasis || 3==Load Jungle
#define LOAD_MAP 1
#define RIVER_COLLIDE 0
#define PRELOAD_TEX 0
#define THREAD_PHYSICS 1
#define WRITE_TO_LOG 0

/*
this variable allows the game to zoom and out
this zooms is used in renderHelper.cpp GameWindow.cpp and Input.cpp
also specified to zoom for the map editor mode
*/
#if MAP_EDITOR 
#define map_zoom 4
#else 
#define map_zoom 1


#endif

#if DEBUG 
#define LOG(input) //std:://////cout << "LOG:" << input << std::endl
#else 
#define LOG(input) 
#endif
