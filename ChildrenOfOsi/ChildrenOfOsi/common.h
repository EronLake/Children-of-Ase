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

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <functional>

#include <json/json.h>


class Common {
public:
	int debug;
	int map_editor;
	bool start_fullscreen;
	bool mouse_visible;
	int load_regions;
	int load_map;
	int river_collide;
	int preload_tex;
	int thread_physics;
	int write_to_log;

	float map_zoom_in_editor;
	float map_zoom_in_game;
	
	Common() {
		//THIS IS THE CODE THAT NEEDS TO BE COPIED EVERYWHERE
		Json::Value root;	
		Json::Reader reader;
		Json::CharReaderBuilder builder;
		//std::string test = 
		std::ifstream test("../ChildrenofOsi/common_config.json", std::ifstream::binary);
		std::string errs;
		bool ok = reader.parse(test, root, false);
		if (!ok)
		{
			// report to the user the failure and their locations in the document.
			std::cout << errs.c_str() << "\n";
		}
		test.close();
		//^THIS IS THE CODE THAT NEEDS TO BE COPIED EVERYWHERE

		std::string encoding = root.get("encoding", "UTF-8").asString();
		std::cout << encoding << "\n";

		debug = root["debug"].asInt();
		map_editor = root["map_editor"].asInt();
		start_fullscreen = root["start_fullscreen"].asBool();
		mouse_visible = root["mouse_visible"].asBool();
		load_regions = root["load_regions"].asInt();
		load_map = root["load_map"].asInt();
		river_collide = root["river_collide"].asInt();
		preload_tex = root["preload_tex"].asInt();
		thread_physics = root["thread_physics"].asInt();
		write_to_log = root["write_to_log"].asInt();

		map_zoom_in_editor = root["map_zoom_in_editor"].asFloat();
		map_zoom_in_game = root["map_zoom_in_game"].asFloat();
	};
};

static Common* config = new Common();


#define SHANGO 1
#define YEMOJA 2
#define OYA 3
#define OSHOSI 4
#define OGUN 5

//static double map_zoom = 1.5; //initialized in main

//Texture* rect = new Texture();
//toggles debug longging statements 

#define DEBUG 1 //cant use json
#define MAP_EDITOR 0 //cant use json
#define START_FULLSCREEN config->start_fullscreen
#define MOUSE_VISIBLE config->mouse_visible
#define LOAD_REGIONS config->load_regions //0==Load Config should be empty || 1==Load All || 2==Load Oasis || 3==Load Jungle
#define LOAD_MAP config->load_map
#define RIVER_COLLIDE config->river_collide
#define PRELOAD_TEX config->preload_tex
#define THREAD_PHYSICS config->thread_physics
#define WRITE_TO_LOG config->write_to_log

/*
this variable allows the game to zoom and out
this zooms is used in renderHelper.cpp GameWindow.cpp and Input.cpp
also specified to zoom for the map editor mode
*/
#if MAP_EDITOR 
#define map_zoom 6
#else 
#define map_zoom 1


#endif

#if DEBUG 
#define LOG(input) //std:://////cout << "LOG:" << input << std::endl
#else 
#define LOG(input) 
#endif
