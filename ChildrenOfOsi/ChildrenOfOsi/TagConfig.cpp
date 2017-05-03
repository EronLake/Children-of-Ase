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

	std::vector<std::string> conv_points;
	for (auto itor = root["Info_About_Other_Heroes"].begin(); itor != root["Info_About_Other_Heroes"].end(); ++itor) {
		conv_points.push_back((*itor)["conv_pt_1"].asString());
		conv_points.push_back((*itor)["conv_pt_2"].asString());
		conv_points.push_back((*itor)["conv_pt_3"].asString());
		set_tag(gameplay_func, tBuffer, "Info_About_Other_Heroes",conv_points);
	}
	conv_points.clear();
	
	for (auto itor = root["Getting_To_Know_Each_Other"].begin(); itor != root["Getting_To_Know_Each_Other"].end(); ++itor) {
		conv_points.push_back((*itor)["conv_pt_1"].asString());
		conv_points.push_back((*itor)["conv_pt_2"].asString());
		conv_points.push_back((*itor)["conv_pt_3"].asString());
		set_tag(gameplay_func, tBuffer, "Getting_To_Know_Each_Other", conv_points);
	}
	conv_points.clear();

	for (auto itor = root["Ask_About_Alliance"].begin(); itor != root["Ask_About_Alliance"].end(); ++itor) {
		conv_points.push_back((*itor)["conv_pt_1"].asString());
		set_tag(gameplay_func, tBuffer, "Ask_About_Alliance", conv_points);
	}
	conv_points.clear();

	for (auto itor = root["Talk_About_Affinity"].begin(); itor != root["Talk_About_Affinity"].end(); ++itor) {
		//conv_points.push_back((*itor)["conv_pt_1"].asString());
		//conv_points.push_back((*itor)["conv_pt_2"].asString());
		//conv_points.push_back((*itor)["conv_pt_3"].asString());
		//conv_points.push_back((*itor)["conv_pt_4"].asString());
		conv_points.push_back((*itor)["conv_pt_5"].asString());
		conv_points.push_back((*itor)["conv_pt_6"].asString());
		conv_points.push_back((*itor)["conv_pt_7"].asString());
		//conv_points.push_back((*itor)["conv_pt_8"].asString());
		conv_points.push_back((*itor)["conv_pt_9"].asString());
		set_tag(gameplay_func, tBuffer, "Talk_About_Affinity", conv_points);
	}
	conv_points.clear();

	for (auto itor = root["Talk_About_Notoriety"].begin(); itor != root["Talk_About_Notoriety"].end(); ++itor) {
		conv_points.push_back((*itor)["conv_pt_1"].asString());
		//conv_points.push_back((*itor)["conv_pt_2"].asString());
		//conv_points.push_back((*itor)["conv_pt_3"].asString());
		//conv_points.push_back((*itor)["conv_pt_4"].asString());
		//conv_points.push_back((*itor)["conv_pt_5"].asString());
		//conv_points.push_back((*itor)["conv_pt_6"].asString());
		//conv_points.push_back((*itor)["conv_pt_7"].asString());
		//conv_points.push_back((*itor)["conv_pt_8"].asString());
		set_tag(gameplay_func, tBuffer, "Talk_About_Notoriety", conv_points);
	}
	conv_points.clear();

	for (auto itor = root["Talk_About_Strength"].begin(); itor != root["Talk_About_Strength"].end(); ++itor) {
		conv_points.push_back((*itor)["conv_pt_1"].asString());
		conv_points.push_back((*itor)["conv_pt_2"].asString());
		//conv_points.push_back((*itor)["conv_pt_3"].asString());
		//conv_points.push_back((*itor)["conv_pt_4"].asString());
		//conv_points.push_back((*itor)["conv_pt_5"].asString());
		//conv_points.push_back((*itor)["conv_pt_6"].asString());
		conv_points.push_back((*itor)["conv_pt_7"].asString());
		conv_points.push_back((*itor)["conv_pt_8"].asString());
		set_tag(gameplay_func, tBuffer, "Talk_About_Strength", conv_points);
	}
	conv_points.clear();

	for (auto itor = root["Talk_About_Action"].begin(); itor != root["Talk_About_Action"].end(); ++itor) {
		//conv_points.push_back((*itor)["conv_pt_1"].asString());
		//conv_points.push_back((*itor)["conv_pt_2"].asString());
		//conv_points.push_back((*itor)["conv_pt_3"].asString());
		//conv_points.push_back((*itor)["conv_pt_4"].asString());
		conv_points.push_back((*itor)["conv_pt_5"].asString());
		conv_points.push_back((*itor)["conv_pt_6"].asString());
		//conv_points.push_back((*itor)["conv_pt_7"].asString());
		//conv_points.push_back((*itor)["conv_pt_8"].asString());
		set_tag(gameplay_func, tBuffer, "Talk_About_Action", conv_points);
	}
	conv_points.clear();

}

void TagConfig::set_tag(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string name, std::vector<std::string> conv_points)
{
    gameplay_func->add_tag(name);

	tBuffer->run();

	Containers::tag_table[name]->set_name(name);
	for (int i = 0; i < conv_points.size(); ++i) {
		Containers::tag_table[name]->conversation_point.push_back(Containers::conv_point_table[conv_points[i]]);
		Containers::conv_point_table[conv_points[i]]->tag.push_back(Containers::tag_table[name]);
	}

	tBuffer->run();

}