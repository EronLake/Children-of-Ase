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
		std::vector<int> personality_mults;
		for (auto itor = root["conversation_points"].begin(); itor != root["conversation_points"].end(); ++itor) {
				for (auto itor = root["conversation_points"].begin(); itor != root["conversation_points"].end(); ++itor) {

					personality_mults.push_back((*itor)["honor"].asInt());
					personality_mults.push_back((*itor)["pride"].asInt());
					personality_mults.push_back((*itor)["aggression"].asInt());
					personality_mults.push_back((*itor)["kindness"].asInt());
					personality_mults.push_back((*itor)["extroversion"].asInt());
					personality_mults.push_back((*itor)["greed"].asInt());
					personality_mults.push_back((*itor)["recklessness"].asInt());

				}
			set_conv_point(gameplay_func, tBuffer, (*itor)["topic"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults);
		}
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
}

void DialogueConfig::set_conv_point(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string topic, std::string temp, std::string name, std::vector<int> personality_vals)
{
	gameplay_func->add_conv_point(topic, temp, name);
	tBuffer->run();
	/*std::ofstream ofs;
	ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	ofs <<  "name: " << Containers::conv_point_table[name] << std::endl;
	ofs.close();*/
	Containers::conv_point_table[name]->set_topic(topic);
	Containers::conv_point_table[name]->set_name(name);
	Containers::conv_point_table[name]->set_temp(temp);
	Containers::conv_point_table[name]->dpoint.push_back(topic);
	Containers::conv_point_table[name]->dpoint.push_back(temp);

	tBuffer->run();
}