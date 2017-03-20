#include "stdafx.h"
#include "ObjConfig.h"
#include <ctime>

bool MakeForest = true;
bool PlacePlant = false;
bool rand_gen = false;
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


ObjConfig::ObjConfig()
{
}


ObjConfig::~ObjConfig()
{
}


void ObjConfig::import_config(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{
	if (Jungle_Config) {
		WhichJson = "config.json";
	}
	else {
		WhichJson = "oasis_config.json";
	}

	int numberOfWorldObj = 0;

	if (rand_gen) {
		make_stuff(recVec, gameplay_func, tBuffer);
	}
	else {
		Json::Value root;
		Json::Reader reader;


		std::ifstream file(WhichJson);
		
		file >> root;
		
		for (auto itr = root.begin(); itr != root.end(); itr++)
		{
			set_world_obj(recVec, gameplay_func, tBuffer, (*itr)["x"].asFloat(), (*itr)["y"].asFloat(),
				(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
				(*itr)["name"].asString(), (*itr)["tex_file"].asString(),
				(*itr)["frame_num"].asInt(),
				(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
				(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat());
			numberOfWorldObj++;
		}
		std::cout << "done" << endl;
		std::cout << "Number of World Objs "<< numberOfWorldObj << endl;
	}



}

void ObjConfig::make_stuff(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{
	Json::Value root;
	Json::Reader reader;


	std::ifstream file(WhichJson);
	file >> root;

	for (auto itr = root.begin(); itr != root.end(); itr++)
	{

		if (MakeForest || PlacePlant) {

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
			(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat());


	}

	//std::cout << "done" << endl;
	if (MakeForest || PlacePlant) {

		Json::Value root;
		Json::Reader reader;
		std::ifstream in_file(WhichJson);
		in_file >> root;
		in_file.close();


		//std::cout << "Makeing Forest" << endl;
		int XDistancs = abs(topLeftx - topRightx);
		int YDistancs = abs(topLefty - botLefty);
		srand(time(0));
		for (int i = 100; i < 250; i++) {
			float randomX;
			float randomY;
			int offsetLeft;
			int offsetRight;
			int offsetTop;
			int offsetBot;

			randomX = rand() % XDistancs + topLeftx;
			randomY = rand() % YDistancs + topLefty;
			stringstream TreeName;
			TreeName << "Jungle_Element_Num_" << i;
			string WhichSprite;
			if (PlacePlant) {
				string PlantSprites[]{
					"Jungle_Bush",
					"Jungle_Flower1",
					"Jungle_Flower2",
					"Jungle_Flower3",
					"Jungle_Plant1",
					"Jungle_Plant2",
					"Jungle_Plant3",
					"Jungle_Plant4",
					"Jungle_scrub1",
					"Jungle_scrub2",
					"Jungle_scrub3",
					"Jungle_scrub4"
				};
				WhichSprite = PlantSprites[rand() % 12];
				set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, 50, 50, TreeName.str(), WhichSprite, 1, 500, 500, 500, 500);

			}
			else {

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
				set_world_obj(recVec, gameplay_func, tBuffer, randomX, randomY, 500.0, 500.0, TreeName.str(), WhichSprite, 1, offsetLeft, offsetRight, offsetTop, offsetBot);


			}

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
			//std::cout << "Here" << endl;




		}
	}

}



void ObjConfig::set_world_obj(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width, float hight,
	std::string name, std::string tex_file, int frame_num, float bodyx1, float bodyx2, float bodyy1, float bodyy2)
{

	LOG(Containers::texture_table[tex_file]);
	if (Containers::texture_table[tex_file]) {

		std::cout << tex_file << "Already in Table /////////////////////////////" << endl;
	}
	else
	{
		std::cout << tex_file << "Not in Table /////////////////////////////" << endl;

		gameplay_func->add_texture(tex_file, 0, 0, 0);

		//set file takes up memory
		tBuffer->run();
		Containers::texture_table[tex_file]->setFile("Assets/Sprites/" + tex_file + ".png", frame_num);

	}



	gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);

	tBuffer->run();

	Containers::worldObj_table[name]->setWidth(width);
	Containers::worldObj_table[name]->setHeight(hight);

	Containers::worldObj_table[name]->sprite.setTexture(Containers::texture_table[tex_file]);
	Containers::worldObj_table[name]->setInteractable(false);

	Containers::worldObj_table[name]->offsetBody(0, bodyx1, bodyx2, bodyy1, bodyy2);

	recVec->push_back(Containers::worldObj_table[name]);

}

