#include "stdafx.h"
#include "TagConfig.h"
#include "Containers.h"


TagConfig::TagConfig()
{
}


TagConfig::~TagConfig()
{
}

void TagConfig::import_config(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{
	
	Json::Value root;
	Json::Reader reader;


	std::ifstream file("Tag_config.json");
	file >> root;
	/*int x = 1;
	std::string tempStr = "Tag_";
	std::string tmpTag = "topic_";
	std::vector<std::string> topicVec;
	for (auto itor = root["Tag"].begin(); itor != root["Tag"].end(); itor++){
		int y = 1;
		std::string tmpStr_1 = tempStr;
		int temp_x = x;
		std::string tmpStr_2 = std::to_string(temp_x);
		std::string tmpStr_3 = tmpStr_1 + tmpStr_2;
		for (auto it = root[tmpStr_3]["topics"].begin(); it != root[tmpStr_3]["topics"].end(); it++)
		{
			std::string tmpTag_1 = tmpTag;
			int temp_y = y;
			std::string tmpTag_2 = std::to_string(temp_y);
			std::string tmpTag_3 = tmpTag_1 + tmpTag_2;
			topicVec.push_back((*it)[tmpTag_3].asString());
			y++;
		}
		
	    set_tag(gameplay_func, tBuffer, (*itor)["name"].asString(), topicVec);
	    x++;
    }*/
	std::vector<std::string> conv_points;
	for (auto itor = root["Info_About_Other_Heroes"].begin(); itor != root["Info_About_Other_Heroes"].end(); ++itor) {
		conv_points.push_back((*itor)["topic_1"].asString());
		conv_points.push_back((*itor)["topic_2"].asString());
		conv_points.push_back((*itor)["topic_3"].asString());
		set_tag(gameplay_func, tBuffer, "Info_About_Other_Heroes",conv_points);
	}
	conv_points.clear();
	
	for (auto itor = root["Getting_To_Know_Each_Other"].begin(); itor != root["Getting_To_Know_Each_Other"].end(); ++itor) {
		conv_points.push_back((*itor)["topic_1"].asString());
		conv_points.push_back((*itor)["topic_2"].asString());
		conv_points.push_back((*itor)["topic_3"].asString());
		set_tag(gameplay_func, tBuffer, "Getting_To_Know_Each_Other", conv_points);
	}
	conv_points.clear();

	/*for (auto itor = root["Recent_Memories"].begin(); itor != root["Recent_Memories"].end(); ++itor) {
		conv_points.push_back((*itor)["topic_1"].asString());
		set_tag(gameplay_func, tBuffer, "Recent_Memories", conv_points);
	}
	conv_points.clear();*/

	/*for (auto itor = root["Talk_About_Event"].begin(); itor != root["Talk_About_Event"].end(); ++itor) {
		conv_points.push_back((*itor)["topic_1"].asString());
		set_tag(gameplay_func, tBuffer, "Talk_About_Event", conv_points);
	}
	conv_points.clear();*/

	for (auto itor = root["Ask_About_Alliance"].begin(); itor != root["Ask_About_Alliance"].end(); ++itor) {
		conv_points.push_back((*itor)["topic_1"].asString());
		set_tag(gameplay_func, tBuffer, "Ask_About_Alliance", conv_points);
	}
	conv_points.clear();

	for (auto itor = root["Talk_About_Affinity"].begin(); itor != root["Talk_About_Affinity"].end(); ++itor) {
		conv_points.push_back((*itor)["topic_4"].asString());
		conv_points.push_back((*itor)["topic_7"].asString());
		conv_points.push_back((*itor)["topic_10"].asString());
		conv_points.push_back((*itor)["topic_13"].asString());
		conv_points.push_back((*itor)["topic_16"].asString());
		conv_points.push_back((*itor)["topic_17"].asString());
		conv_points.push_back((*itor)["topic_18"].asString());
		conv_points.push_back((*itor)["topic_22"].asString());
		conv_points.push_back((*itor)["topic_23"].asString());
		set_tag(gameplay_func, tBuffer, "Talk_About_Affinity", conv_points);
	}
	conv_points.clear();

	for (auto itor = root["Talk_About_Notoriety"].begin(); itor != root["Talk_About_Notoriety"].end(); ++itor) {
		conv_points.push_back((*itor)["topic_4"].asString());
		conv_points.push_back((*itor)["topic_5"].asString());
		conv_points.push_back((*itor)["topic_8"].asString());
		conv_points.push_back((*itor)["topic_11"].asString());
		conv_points.push_back((*itor)["topic_14"].asString());
		conv_points.push_back((*itor)["topic_17"].asString());
		conv_points.push_back((*itor)["topic_21"].asString());
		conv_points.push_back((*itor)["topic_22"].asString());
		set_tag(gameplay_func, tBuffer, "Talk_About_Notoriety", conv_points);
	}
	conv_points.clear();

	for (auto itor = root["Talk_About_Strength"].begin(); itor != root["Talk_About_Strength"].end(); ++itor) {
		conv_points.push_back((*itor)["topic_4"].asString());
		conv_points.push_back((*itor)["topic_5"].asString());
		conv_points.push_back((*itor)["topic_6"].asString());
		conv_points.push_back((*itor)["topic_7"].asString());
		conv_points.push_back((*itor)["topic_8"].asString());
		conv_points.push_back((*itor)["topic_9"].asString());
		conv_points.push_back((*itor)["topic_10"].asString());
		conv_points.push_back((*itor)["topic_11"].asString());
		set_tag(gameplay_func, tBuffer, "Talk_About_Strength", conv_points);
	}
	conv_points.clear();

	for (auto itor = root["Talk_About_Action"].begin(); itor != root["Talk_About_Action"].end(); ++itor) {
		conv_points.push_back((*itor)["topic_1"].asString());
		conv_points.push_back((*itor)["topic_4"].asString());
		conv_points.push_back((*itor)["topic_7"].asString());
		conv_points.push_back((*itor)["topic_10"].asString());
		conv_points.push_back((*itor)["topic_13"].asString());
		conv_points.push_back((*itor)["topic_14"].asString());
		conv_points.push_back((*itor)["topic_15"].asString());
		conv_points.push_back((*itor)["topic_19"].asString());
		set_tag(gameplay_func, tBuffer, "Talk_About_Action", conv_points);
	}
	conv_points.clear();

}

void TagConfig::set_tag(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string name, std::vector<std::string> conv_points)
{


		gameplay_func->add_tag(name);

		//set file takes up memory
		tBuffer->run();
		Containers::tag_table[name]->set_name(name);
		for (int i = 0; i < conv_points.size(); ++i) {
			Containers::tag_table[name]->conversation_point_pointer_vec.push_back(Containers::conv_point_table[conv_points[i]]);
			Containers::conv_point_table[conv_points[i]]->tag_pointer_vec.push_back(Containers::tag_table[name]);
		}
		//Containers::texture_table[tex_file]->setFile("Assets/Sprites/" + tex_file + ".png", frame_num);
	/* For Spencer
	if (tex_file == "){
	gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	}
	*/

	//gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);

	//tBuffer->run();

	//Containers::worldObj_table[name]->setWidth(width);
	//Containers::worldObj_table[name]->setHeight(hight);

	//Containers::worldObj_table[name]->sprite.setTexture(Containers::texture_table[tex_file]);
	//Containers::worldObj_table[name]->setInteractable(false);

	//Containers::worldObj_table[name]->offsetBody(0, 0, 0, 0, 0);

	//recVec->push_back(Containers::worldObj_table[name]);
	tBuffer->run();

}