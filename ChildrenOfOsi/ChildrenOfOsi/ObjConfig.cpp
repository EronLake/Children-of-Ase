#include "stdafx.h"
#include "ObjConfig.h"
#include <ctime>

bool MakeForest = false;
bool PlacePlant = false;
bool rand_gen = false;
bool PlaceOasisPlant = false;
bool PlaceOasisShrub = false;
bool Jungle_Config = true;
float topLeftx;
float topLefty;
float topRightx;
float topRighty;
float botLeftx;
float botLefty;
float botRightx;
float botRighty;

string WhichJson;
unordered_map<Texture*, pair<string, int>> ObjConfig::textureMap;
std::set<Texture*> ObjConfig::standard_con;
std::set<Texture*> ObjConfig::oasis_con;
std::set<Texture*> ObjConfig::jungle_con;
std::set<Texture*> ObjConfig::mountain_con;
std::set<Texture*> ObjConfig::marsh_con;

ObjConfig::ObjConfig()
{
}


ObjConfig::~ObjConfig()
{
}


void ObjConfig::import_config(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{
	string ConfigFiles[]{
		"config_oasis.json",
		"config_jungle.json"
	};

	int region = 0;
	if (Jungle_Config) {
		WhichJson = "config.json";
		region = JUNGLE;
	}
	else {
		WhichJson = "config.json";
		region = OASIS;
	}

	int numberOfWorldObj = 0;

	if (MakeForest || PlacePlant || PlaceOasisPlant || PlaceOasisShrub) {
		make_stuff(recVec, gameplay_func, tBuffer, region);
	}
	else {
		if (LOAD_REGIONS == 0) {
			bool alive = true;
			Json::Value root;
			while (alive) {

				Json::Reader reader;
				Json::CharReaderBuilder builder;
				//std::string test = 
				std::ifstream test("../ChildrenofOsi/config.json", std::ifstream::binary);
				std::string errs;
				bool ok = reader.parse(test, root, false);
				if (!ok)
				{
					// report to the user the failure and their locations in the document.
					std::cout << errs.c_str() << "\n";
				}

				std::string encoding = root.get("encoding", "UTF-8").asString();
				std::cout << encoding << "\n";
				alive = false;
				test.close();
			}
			for (auto itr = root.begin(); itr != root.end(); itr++)
			{

				set_world_obj(recVec, gameplay_func, tBuffer, (*itr)["x"].asFloat(), (*itr)["y"].asFloat(),
					(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
					(*itr)["name"].asString(), (*itr)["tex_file"].asString(),
					(*itr)["frame_num"].asInt(),
					(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
					(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat(), region);
				numberOfWorldObj++;
			}
		}
		else if (LOAD_REGIONS == 1) {
			for (int i = 0; i < 2; i++) {
				bool alive = true;
				Json::Value root;
				while (alive) {

					Json::Reader reader;
					Json::CharReaderBuilder builder;
					//std::string test = 
					std::ifstream test("../ChildrenofOsi/" + ConfigFiles[i], std::ifstream::binary);
					std::string errs;
					bool ok = reader.parse(test, root, false);
					if (!ok)
					{
						// report to the user the failure and their locations in the document.
						std::cout << errs.c_str() << "\n";
					}

					std::string encoding = root.get("encoding", "UTF-8").asString();
					std::cout << encoding << "\n";
					alive = false;
					test.close();
				}

				for (auto itr = root.begin(); itr != root.end(); itr++)
				{
					set_world_obj(recVec, gameplay_func, tBuffer, (*itr)["x"].asFloat(), (*itr)["y"].asFloat(),
						(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
						(*itr)["name"].asString(), (*itr)["tex_file"].asString(),
						(*itr)["frame_num"].asInt(),
						(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
						(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat(), region);
					numberOfWorldObj++;
				}
			}
		}
		else if (LOAD_REGIONS == 2) {
			bool alive = true;
			Json::Value root;
			while (alive) {

				Json::Reader reader;
				Json::CharReaderBuilder builder;
				//std::string test = 
				std::ifstream test("../ChildrenofOsi/" + ConfigFiles[0], std::ifstream::binary);
				std::string errs;
				bool ok = reader.parse(test, root, false);
				if (!ok)
				{
					// report to the user the failure and their locations in the document.
					std::cout << errs.c_str() << "\n";
				}

				std::string encoding = root.get("encoding", "UTF-8").asString();
				std::cout << encoding << "\n";
				alive = false;
				test.close();
			}

			for (auto itr = root.begin(); itr != root.end(); itr++)
			{
				set_world_obj(recVec, gameplay_func, tBuffer, (*itr)["x"].asFloat(), (*itr)["y"].asFloat(),
					(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
					(*itr)["name"].asString(), (*itr)["tex_file"].asString(),
					(*itr)["frame_num"].asInt(),
					(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
					(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat(), region);
				numberOfWorldObj++;
			}
		}
		else if (LOAD_REGIONS == 3)
		{
			bool alive = true;
			Json::Value root;
			while (alive) {

				Json::Reader reader;
				Json::CharReaderBuilder builder;
				//std::string test = 
				std::ifstream test("../ChildrenofOsi/" + ConfigFiles[1], std::ifstream::binary);
				std::string errs;
				bool ok = reader.parse(test, root, false);
				if (!ok)
				{
					// report to the user the failure and their locations in the document.
					std::cout << errs.c_str() << "\n";
				}

				std::string encoding = root.get("encoding", "UTF-8").asString();
				std::cout << encoding << "\n";
				alive = false;
				test.close();
			}

			for (auto itr = root.begin(); itr != root.end(); itr++)
			{
				set_world_obj(recVec, gameplay_func, tBuffer, (*itr)["x"].asFloat(), (*itr)["y"].asFloat(),
					(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
					(*itr)["name"].asString(), (*itr)["tex_file"].asString(),
					(*itr)["frame_num"].asInt(),
					(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
					(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat(), region);
				numberOfWorldObj++;
			}
		}

		std::cout << "done" << endl;
		std::cout << "Number of World Objs " << numberOfWorldObj << endl;
	}



}

void ObjConfig::make_stuff(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, int region)
{

	if (Jungle_Config) {
		WhichJson = "config.json";
		region = JUNGLE;
	}
	else {
		WhichJson = "config.json";
		region = OASIS;
	}
	bool alive = true;
	Json::Value root;
	while (alive) {

		Json::Reader reader;
		Json::CharReaderBuilder builder;
		//std::string test = 
		std::ifstream test("../ChildrenofOsi/"+WhichJson, std::ifstream::binary);
		std::string errs;
		bool ok = reader.parse(test, root, false);
		if (!ok)
		{
			// report to the user the failure and their locations in the document.
			std::cout << errs.c_str() << "\n";
		}

		std::string encoding = root.get("encoding", "UTF-8").asString();
		std::cout << encoding << "\n";
		alive = false;
		test.close();
	}

	for (auto itr = root.begin(); itr != root.end(); itr++)
	{

		if (MakeForest || PlacePlant || PlaceOasisPlant || PlaceOasisShrub) {

			if ((*itr)["name"].asString() == "JungleTopLeft") {
				topLeftx = (*itr)["x"].asFloat();
				topLefty = (*itr)["y"].asFloat();

			}
			else if ((*itr)["name"].asString() == "JungleTopRight")
			{
				topRightx = (*itr)["x"].asFloat();
				topRighty = (*itr)["y"].asFloat();
			}
			else if ((*itr)["name"].asString() == "JungleBotLeft") {
				botLeftx = (*itr)["x"].asFloat();
				botLefty = (*itr)["y"].asFloat();
			}
			else if ((*itr)["name"].asString() == "JungleBotRight") {
				botRightx = (*itr)["x"].asFloat();
				botRighty = (*itr)["y"].asFloat();
			}

		}
		set_world_obj(recVec, gameplay_func, tBuffer, (*itr)["x"].asFloat(), (*itr)["y"].asFloat(),
			(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
			(*itr)["name"].asString(), (*itr)["tex_file"].asString(),
			(*itr)["frame_num"].asInt(),
			(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
			(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat(), region);


	}

	////std:://cout << "done" << endl;
	if (MakeForest || PlacePlant) {

		bool alive = true;
		Json::Value root;
		while (alive) {

			Json::Reader reader;
			Json::CharReaderBuilder builder;
			//std::string test = 
			std::ifstream test("../ChildrenofOsi/"+WhichJson, std::ifstream::binary);
			std::string errs;
			bool ok = reader.parse(test, root, false);
			if (!ok)
			{
				// report to the user the failure and their locations in the document.
				std::cout << errs.c_str() << "\n";
			}

			std::string encoding = root.get("encoding", "UTF-8").asString();
			std::cout << encoding << "\n";
			alive = false;
			test.close();
		}
	

		////std:://cout << "Makeing Forest" << endl;
		int XDistancs = abs(topLeftx - topRightx);
		int YDistancs = abs(topLefty - botLefty);
		srand(time(0));
		for (int i = 601; i < 800; i++) {
			float randomX;
			float randomY;
			float offsetLeft;
			float offsetRight;
			float offsetTop;
			float offsetBot;

			randomX = rand() % XDistancs + topLeftx;
			randomY = rand() % YDistancs + topLefty;
			stringstream TreeName;
			TreeName << "Jungle_Element_Num_" << i;
			string WhichSprite;
			if (PlacePlant) {
				string PlantSprites[]{
					"Jungle_shrub1",
					"Jungle_shrub2",
					"Jungle_shrub3",
					"Jungle_shrub4",
					"Jungle_shrub5",
					"Jungle_shrub6",

				};
				int random = rand() % 6;
				WhichSprite = PlantSprites[random];
				int randomShrubsize = rand() % (175 * 100 - 75 * 100 + 1) + 10 * 100;
				randomShrubsize = randomShrubsize / 100;
				int offestleft = randomShrubsize;
				switch (random)
				{
				case 0:
					offsetLeft = randomShrubsize*.2473;
					offsetRight = randomShrubsize*.2448;
					offsetTop = randomShrubsize*.5467;
					offsetBot = randomShrubsize*.3125;
					set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, randomShrubsize, randomShrubsize, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot, JUNGLE);

					break;
				case 1:
					offsetLeft = randomShrubsize*.2473;
					offsetRight = randomShrubsize*.2448;
					offsetTop = randomShrubsize*.5467;
					offsetBot = randomShrubsize*.3125;
					set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, randomShrubsize, randomShrubsize, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot, JUNGLE);

					break;
				case 2:
					offsetLeft = randomShrubsize*.2473;
					offsetRight = randomShrubsize*.2448;
					offsetTop = randomShrubsize*.5467;
					offsetBot = randomShrubsize*.3125;
					set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, randomShrubsize, randomShrubsize, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot, JUNGLE);

					break;
				case 3:
					offsetLeft = randomShrubsize*.2875;
					offsetRight = randomShrubsize*.2175;
					offsetTop = randomShrubsize*.625;
					offsetBot = randomShrubsize*.0875;
					set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, randomShrubsize, randomShrubsize, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot, JUNGLE);

					break;
				case 4:
					offsetLeft = randomShrubsize*.329;
					offsetRight = randomShrubsize*.249;
					offsetTop = randomShrubsize*.714;
					offsetBot = randomShrubsize*.1;
					set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, randomShrubsize, randomShrubsize, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot, JUNGLE);

					break;
				case 5:
					offsetLeft = randomShrubsize*.3125;
					offsetRight = randomShrubsize*.325;
					offsetTop = randomShrubsize*.479;
					offsetBot = randomShrubsize*.3375;
					set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, randomShrubsize, randomShrubsize, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot, JUNGLE);

					break;
				}
				std::ofstream file;
				file.open("../ChildrenofOsi/" + WhichJson);

				//populate 'value_obj' with the objects, arrays etc.
				Json::Value new_obj = {};

				new_obj["x"] = floor(randomX); new_obj["y"] = floor(randomY);
				new_obj["hight"] = randomShrubsize; new_obj["width"] = randomShrubsize;
				new_obj["frame_num"] = 1;
				new_obj["name"] = TreeName.str(); new_obj["tex_file"] = WhichSprite;
				new_obj["bodyx1"] = offsetLeft; new_obj["bodyx2"] = offsetRight; new_obj["bodyy1"] = offsetTop; new_obj["bodyy2"] = offsetBot;

				root[TreeName.str()] = new_obj;

				Json::StyledWriter styledWriter;
				file << styledWriter.write(root);

				file.close();
			}
			else if (MakeForest) {

				string TreeSprites[] = {
					"Jungle_Tree_1",
					"Jungle_Tree_2",
					"Jungle_Tree_3",
					"Jungle_Tree_4",
					"Jungle_Tree_5" };
				int random = rand() % 5;
				WhichSprite = TreeSprites[random];
				switch (random) {
				case 0:
					offsetLeft = 180;
					offsetRight = 180;
					offsetTop = 350;
					offsetBot = 95;

					break;
				case 1:
					offsetLeft = 210;
					offsetRight = 200;
					offsetTop = 420;
					offsetBot = 50;

					break;
				case 2:
					offsetLeft = 205;
					offsetRight = 225;
					offsetTop = 430;
					offsetBot = 30;
					break;
				case 3:
					offsetLeft = 205;
					offsetRight = 225;
					offsetTop = 430;
					offsetBot = 30;
					break;
				case 4:
					offsetLeft = 180;
					offsetRight = 180;
					offsetTop = 350;
					offsetBot = 95;
					break;
				}
				set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, 500.0, 500.0, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot, JUNGLE);
				std::ofstream file;
				file.open(WhichJson);

				//populate 'value_obj' with the objects, arrays etc.
				Json::Value new_obj = {};

				new_obj["x"] = floor(randomX); new_obj["y"] = floor(randomY);
				new_obj["hight"] = 500; new_obj["width"] = 500;
				new_obj["frame_num"] = 1;
				new_obj["name"] = TreeName.str(); new_obj["tex_file"] = WhichSprite;
				new_obj["bodyx1"] = offsetLeft; new_obj["bodyx2"] = offsetRight; new_obj["bodyy1"] = offsetTop; new_obj["bodyy2"] = offsetBot;

				root[TreeName.str()] = new_obj;

				Json::StyledWriter styledWriter;
				file << styledWriter.write(root);

				file.close();

			}
		}

	}
	else {
		bool alive = true;
		Json::Value root;
		while (alive) {

			Json::Reader reader;
			Json::CharReaderBuilder builder;
			//std::string test = 
			std::ifstream test("../ChildrenofOsi/" + WhichJson, std::ifstream::binary);
			std::string errs;
			bool ok = reader.parse(test, root, false);
			if (!ok)
			{
				// report to the user the failure and their locations in the document.
				std::cout << errs.c_str() << "\n";
			}

			std::string encoding = root.get("encoding", "UTF-8").asString();
			std::cout << encoding << "\n";
			alive = false;
			test.close();
		}

		std::cout << "Makeing Oasis" << endl;
		int XDistancs = abs(topLeftx - topRightx);
		int YDistancs = abs(topLefty - botLefty);
		srand(time(0));
		for (int i = 100; i < 200; i++) {
			float randomX;
			float randomY;
			float offsetLeft;
			float offsetRight;
			float offsetTop;
			float offsetBot;

			randomX = rand() % XDistancs + topLeftx;
			randomY = rand() % YDistancs + topLefty;
			stringstream TreeName;
			TreeName << "Oasis_Element_Num_" << i;
			string WhichSprite;

			if (PlaceOasisPlant) {
				string PlantSprites[]{
					"Oasis_Tree1",
					"Oasis_Tree2",
					"Oasis_Tree3"

				};
				int random = rand() % 3;
				WhichSprite = PlantSprites[random];
				int randomShrubsize = rand() % 100 + 500;
				int offestleft = randomShrubsize;
				switch (random)
				{
				case 0:
					offsetLeft = randomShrubsize*.3375;
					offsetRight = randomShrubsize*.3625;
					offsetTop = randomShrubsize*.7675;
					offsetBot = randomShrubsize*0.09;
					set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, randomShrubsize, randomShrubsize, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot, JUNGLE);

					break;
				case 1:
					offsetLeft = randomShrubsize*.5375;
					offsetRight = randomShrubsize*.3625;
					offsetTop = randomShrubsize*.8687;
					offsetBot = randomShrubsize*0.025;
					set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, randomShrubsize, randomShrubsize, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot, JUNGLE);

					break;
				case 2:
					offsetLeft = randomShrubsize*.455;
					offsetRight = randomShrubsize*.470;
					offsetTop = randomShrubsize*.813;
					offsetBot = randomShrubsize*.115;
					set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, randomShrubsize, randomShrubsize, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot, JUNGLE);

					break;
				}
				std::ofstream file;
				file.open(WhichJson);

				//populate 'value_obj' with the objects, arrays etc.
				Json::Value new_obj = {};

				new_obj["x"] = floor(randomX); new_obj["y"] = floor(randomY);
				new_obj["hight"] = randomShrubsize; new_obj["width"] = randomShrubsize;
				new_obj["frame_num"] = 1;
				new_obj["name"] = TreeName.str(); new_obj["tex_file"] = WhichSprite;
				new_obj["bodyx1"] = offsetLeft; new_obj["bodyx2"] = offsetRight; new_obj["bodyy1"] = offsetTop; new_obj["bodyy2"] = offsetBot;

				root[TreeName.str()] = new_obj;

				Json::StyledWriter styledWriter;
				file << styledWriter.write(root);

				file.close();
			}
			else {
				string PlantSprites[]{
					"Oasis_Shrub1",
					"Oasis_Shrub2",
					"Oasis_Shrub3",
					"Oasis_Shrub4",
					"Oasis_Shrub5",
					"Oasis_Shrub6",
					"Oasis_Shrub7",
					"Oasis_Shrub8",
					"Oasis_Shrub9",
					"Oasis_Shrub10",
					"Oasis_Shrub11"

				};
				int random = rand() % 11;
				WhichSprite = PlantSprites[random];
				int randomShrubsize = rand() % 10 + 60;
				int offestleft = randomShrubsize;
				set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, 70, 70, TreeName.str(), WhichSprite, 1, 70, 70, 70, 70, JUNGLE);

				std::ofstream file;
				file.open(WhichJson);

				//populate 'value_obj' with the objects, arrays etc.
				Json::Value new_obj = {};

				new_obj["x"] = floor(randomX); new_obj["y"] = floor(randomY);
				new_obj["hight"] = 70; new_obj["width"] = 70;
				new_obj["frame_num"] = 1;
				new_obj["name"] = TreeName.str(); new_obj["tex_file"] = WhichSprite;
				new_obj["bodyx1"] = offsetLeft; new_obj["bodyx2"] = offsetLeft; new_obj["bodyy1"] = offsetLeft; new_obj["bodyy2"] = offsetLeft;

				root[TreeName.str()] = new_obj;

				Json::StyledWriter styledWriter;
				file << styledWriter.write(root);

				file.close();
			}
		}
	}
}




void ObjConfig::set_world_obj(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width, float hight,
	std::string name, std::string tex_file, int frame_num, float bodyx1, float bodyx2, float bodyy1, float bodyy2, int region)
{

	if (tex_file == "") {
		int i = 1;
	}

	LOG(Containers::texture_table[tex_file]);
	if (Containers::texture_table[tex_file]) {

		//std:://cout << tex_file << "Already in Table /////////////////////////////" << endl;
	}
	else
	{
		//std:://cout << tex_file << "Not in Table /////////////////////////////" << endl;

		gameplay_func->add_texture(tex_file, 0, 0, 0);

		//set file takes up memory
		tBuffer->run();
		(textureMap)[Containers::texture_table[tex_file]] = pair<string, int>("Assets/Sprites/" + tex_file + ".png", frame_num);
		//Containers::texture_table[tex_file]->setFile("Assets/Sprites/" + tex_file + ".png", frame_num);
		switch (region) {
		case STANDARD:
			(standard_con).insert(Containers::texture_table[tex_file]);
			break;
		case OASIS:
			(oasis_con).insert(Containers::texture_table[tex_file]);
			break;
		case JUNGLE:
			(jungle_con).insert(Containers::texture_table[tex_file]);
			break;
		case MOUNTAIN:
			(mountain_con).insert(Containers::texture_table[tex_file]);
			break;
		case OGUNREG:
			(marsh_con).insert(Containers::texture_table[tex_file]);
			break;
		}
	}


	if (!Containers::worldObj_table[name]) {
		gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	}

	tBuffer->run();

	Containers::worldObj_table[name]->setName(name);
	Containers::worldObj_table[name]->setWidth(width);
	Containers::worldObj_table[name]->setHeight(hight);

	Containers::worldObj_table[name]->sprite.setTexture(Containers::texture_table[tex_file]);
	Containers::worldObj_table[name]->setInteractable(false);

	Containers::worldObj_table[name]->offsetBody(0, bodyx1, bodyx2, bodyy1, bodyy2);

	recVec->push_back(Containers::worldObj_table[name]);

}

