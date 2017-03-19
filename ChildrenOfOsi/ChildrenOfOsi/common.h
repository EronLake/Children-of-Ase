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

#define SHANGO 1
#define YEMOJA 2
#define OYA 3
#define OSHOSI 4
#define OGUN 5


static int frame_count = 0;

//toggles debug longging statements 
#define DEBUG 0

#if DEBUG 
#define LOG(input) //std::////cout << "LOG:" << input << std::endl
#else 
#define LOG(input) 

#endif
