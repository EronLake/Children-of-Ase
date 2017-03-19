#include "stdafx.h"
#include "DialogueConfig.h"
#include "ConversationPoint.h"



DialogueConfig::DialogueConfig()
{
}


DialogueConfig::~DialogueConfig()
{
}

void DialogueConfig::import_config(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{

		Json::Value root;
		Json::Reader reader;


		std::ifstream file("Dialogue_config.json");
		file >> root;
		//for (auto itr = root.begin(); itr != root.end(); itr++)
		//{
			//set_conv_point(gameplay_func, tBuffer, (*itr)["name"].asString());
		//}
		//std::ofstream ofs;
		//ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
		
		for (auto itor = root["conversation_points"].begin(); itor != root["conversation_points"].end(); ++itor) {
			//ofs << "itor: " << (*itor)["name"].asString() << std::endl;
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString());
		}
		//ofs.close();
		for (auto itor = root["reply_points"].begin(); itor != root["reply_points"].end(); ++itor) {
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString());
		}
		std::cout << "done" << endl;
	



}

void DialogueConfig::set_conv_point(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string topic, std::string temp, std::string name)
{

	//std::cout << tex_file << "Not in Table /////////////////////////////" << endl;
	gameplay_func->add_conv_point(topic, temp, name);
	tBuffer->run();
	std::ofstream ofs;
	ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	ofs <<  "name: " << Containers::conv_point_table[name] << std::endl;
	ofs.close();
	Containers::conv_point_table[name]->set_topic(topic);
	Containers::conv_point_table[name]->set_name(name);
	Containers::conv_point_table[name]->set_temp(temp);
	Containers::conv_point_table[name]->dpoint.push_back(topic);
	Containers::conv_point_table[name]->dpoint.push_back(temp);

	//set file takes up memory
	tBuffer->run();
	//Containers::conv_point_table[tex_file]->setFile("Assets/Sprites/" + tex_file + ".png", frame_num);


	//gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);

	//tBuffer->run();

	//Containers::worldObj_table[name]->setWidth(width);
	//Containers::worldObj_table[name]->setHeight(hight);
}