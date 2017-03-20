#include "stdafx.h"
#include "DialogueConfig.h"
#include "ConversationPoint.h"

int p_itor = 0;


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
		std::vector<int> personality_mults;
		//bool personality_loop_control = true;
		for (auto itor = root["conversation_points"].begin(); itor != root["conversation_points"].end(); ++itor) {
			/*if (personality_loop_control) {
				for (auto itor = root["conversation_points"].begin(); itor != root["conversation_points"].end(); ++itor) {

					personality_mults.push_back((*itor)["honor"].asInt());
					personality_mults.push_back((*itor)["pride"].asInt());
					personality_mults.push_back((*itor)["aggression"].asInt());
					personality_mults.push_back((*itor)["kindness"].asInt());
					personality_mults.push_back((*itor)["extroversion"].asInt());
					personality_mults.push_back((*itor)["greed"].asInt());
					personality_mults.push_back((*itor)["recklessness"].asInt());

				}
			}*/
			//personality_loop_control = false;
			//ofs << "itor: " << (*itor)["name"].asString() << std::endl;
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults);
		}
		//ofs.close();
		for (auto itor = root["reply_points"].begin(); itor != root["reply_points"].end(); ++itor) {
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults);
		}
		std::cout << "done" << endl;
		for (auto itor = root["affinity_conversation_points"].begin(); itor != root["affinity_conversation_points"].end(); ++itor) {
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults);
		}

		for (auto itor = root["affinity_reply_points"].begin(); itor != root["affinity_reply_points"].end(); ++itor) {
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults);
		}
		for (auto itor = root["strength_conversation_points"].begin(); itor != root["strength_conversation_points"].end(); ++itor) {
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults);
		}

		for (auto itor = root["strength_reply_points"].begin(); itor != root["strength_reply_points"].end(); ++itor) {
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults);
		}

	

		for (auto itor = root["notoriety_conversation_points"].begin(); itor != root["notoriety_conversation_points"].end(); ++itor) {
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults);
		}

		for (auto itor = root["notoriety_reply_points"].begin(); itor != root["notoriety_reply_points"].end(); ++itor) {
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults);
		}
	
		std::ofstream ofs;
		ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
		ofs << "conv_tab: " << Containers::conv_point_table.size() << std::endl;
		ofs.close();


}

void DialogueConfig::set_conv_point(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string topic, std::string temp, std::string name, std::vector<int> personality_vals)
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

	//std::ofstream ofs;
	//ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	//ofs << "psize: " << personality_vals.size() << std::endl;
	/*while (p_itor < 7) {
		ofs << "p_itor: " << p_itor<< std::endl;
		Containers::conv_point_table[name]->multipliers->setHonor(0);
		++p_itor;
		Containers::conv_point_table[name]->multipliers->setPride(personality_vals[p_itor]);
		++p_itor;
		Containers::conv_point_table[name]->multipliers->setAggression(personality_vals[p_itor]);
		++p_itor;
		Containers::conv_point_table[name]->multipliers->setKindness(personality_vals[p_itor]);
		++p_itor;
		Containers::conv_point_table[name]->multipliers->setAggression(personality_vals[p_itor]);
		++p_itor;
		Containers::conv_point_table[name]->multipliers->setExtroversion(personality_vals[p_itor]);
		++p_itor;
		Containers::conv_point_table[name]->multipliers->setGreed(personality_vals[p_itor]);
		++p_itor;
		Containers::conv_point_table[name]->multipliers->setRecklessness(personality_vals[p_itor]);

	}
	ofs.close();*/
	//set file takes up memory
	tBuffer->run();
	//Containers::conv_point_table[tex_file]->setFile("Assets/Sprites/" + tex_file + ".png", frame_num);


	//gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);

	//tBuffer->run();

	//Containers::worldObj_table[name]->setWidth(width);
	//Containers::worldObj_table[name]->setHeight(hight);
}