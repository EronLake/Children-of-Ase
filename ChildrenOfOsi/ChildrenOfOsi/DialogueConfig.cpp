#include "stdafx.h"
#include "DialogueConfig.h"
#include "ConversationPoint.h"
#include "Memory.h"


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
		std::vector<int> relationship_vals;
		std::string topic = "Shango"; //default topic for every conversation point
		for (auto itor = root["Question_Conversation_Points"].begin(); itor != root["Question_Conversation_Points"].end(); ++itor) {

			personality_mults.push_back((*itor)["honor"].asInt());
			personality_mults.push_back((*itor)["pride"].asInt());
			personality_mults.push_back((*itor)["aggression"].asInt());
			personality_mults.push_back((*itor)["kindness"].asInt());
			personality_mults.push_back((*itor)["extroversion"].asInt());
			personality_mults.push_back((*itor)["greed"].asInt());
			personality_mults.push_back((*itor)["recklessness"].asInt());

			relationship_vals.push_back((*itor)["affinity"].asInt());
			relationship_vals.push_back((*itor)["notoriety"].asInt());
			relationship_vals.push_back((*itor)["strength"].asInt());
			relationship_vals.push_back((*itor)["AffEstimate"].asInt());
			relationship_vals.push_back((*itor)["NotorEstimate"].asInt());
			relationship_vals.push_back((*itor)["StrEstimate"].asInt());

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic);
			personality_mults.clear();
			relationship_vals.clear();
		}
		personality_mults.clear();
		relationship_vals.clear();

		for (auto itor = root["Question_Reply_Points"].begin(); itor != root["Question_Reply_Points"].end(); ++itor) {
			personality_mults.push_back((*itor)["honor"].asInt());
			personality_mults.push_back((*itor)["pride"].asInt());
			personality_mults.push_back((*itor)["aggression"].asInt());
			personality_mults.push_back((*itor)["kindness"].asInt());
			personality_mults.push_back((*itor)["extroversion"].asInt());
			personality_mults.push_back((*itor)["greed"].asInt());
			personality_mults.push_back((*itor)["recklessness"].asInt());

			relationship_vals.push_back((*itor)["affinity"].asInt());
			relationship_vals.push_back((*itor)["notoriety"].asInt());
			relationship_vals.push_back((*itor)["strength"].asInt());
			relationship_vals.push_back((*itor)["AffEstimate"].asInt());
			relationship_vals.push_back((*itor)["NotorEstimate"].asInt());
			relationship_vals.push_back((*itor)["StrEstimate"].asInt());

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic);
			personality_mults.clear();
			relationship_vals.clear();
		}
		personality_mults.clear();
		relationship_vals.clear();

		for (auto itor = root["Affinity_Conversation_Points"].begin(); itor != root["Affinity_Conversation_Points"].end(); ++itor) {
			personality_mults.push_back((*itor)["honor"].asInt());
			personality_mults.push_back((*itor)["pride"].asInt());
			personality_mults.push_back((*itor)["aggression"].asInt());
			personality_mults.push_back((*itor)["kindness"].asInt());
			personality_mults.push_back((*itor)["extroversion"].asInt());
			personality_mults.push_back((*itor)["greed"].asInt());
			personality_mults.push_back((*itor)["recklessness"].asInt());

			relationship_vals.push_back((*itor)["affinity"].asInt());
			relationship_vals.push_back((*itor)["notoriety"].asInt());
			relationship_vals.push_back((*itor)["strength"].asInt());
			relationship_vals.push_back((*itor)["AffEstimate"].asInt());
			relationship_vals.push_back((*itor)["NotorEstimate"].asInt());
			relationship_vals.push_back((*itor)["StrEstimate"].asInt());

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic);
			personality_mults.clear();
			relationship_vals.clear();
		}
		personality_mults.clear();
		relationship_vals.clear();

		for (auto itor = root["Affinity_Reply_Points"].begin(); itor != root["Affinity_Reply_Points"].end(); ++itor) {
			personality_mults.push_back((*itor)["honor"].asInt());
			personality_mults.push_back((*itor)["pride"].asInt());
			personality_mults.push_back((*itor)["aggression"].asInt());
			personality_mults.push_back((*itor)["kindness"].asInt());
			personality_mults.push_back((*itor)["extroversion"].asInt());
			personality_mults.push_back((*itor)["greed"].asInt());
			personality_mults.push_back((*itor)["recklessness"].asInt());

			relationship_vals.push_back((*itor)["affinity"].asInt());
			relationship_vals.push_back((*itor)["notoriety"].asInt());
			relationship_vals.push_back((*itor)["strength"].asInt());
			relationship_vals.push_back((*itor)["AffEstimate"].asInt());
			relationship_vals.push_back((*itor)["NotorEstimate"].asInt());
			relationship_vals.push_back((*itor)["StrEstimate"].asInt());

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic);
			personality_mults.clear();
			relationship_vals.clear();
		}
		personality_mults.clear();
		relationship_vals.clear();

		for (auto itor = root["Strength_Conversation_Points"].begin(); itor != root["Strength_Conversation_Points"].end(); ++itor) {
			personality_mults.push_back((*itor)["honor"].asInt());
			personality_mults.push_back((*itor)["pride"].asInt());
			personality_mults.push_back((*itor)["aggression"].asInt());
			personality_mults.push_back((*itor)["kindness"].asInt());
			personality_mults.push_back((*itor)["extroversion"].asInt());
			personality_mults.push_back((*itor)["greed"].asInt());
			personality_mults.push_back((*itor)["recklessness"].asInt());

			relationship_vals.push_back((*itor)["affinity"].asInt());
			relationship_vals.push_back((*itor)["notoriety"].asInt());
			relationship_vals.push_back((*itor)["strength"].asInt());
			relationship_vals.push_back((*itor)["AffEstimate"].asInt());
			relationship_vals.push_back((*itor)["NotorEstimate"].asInt());
			relationship_vals.push_back((*itor)["StrEstimate"].asInt());

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic);
			personality_mults.clear();
			relationship_vals.clear();
		}
		personality_mults.clear();
		relationship_vals.clear();

		for (auto itor = root["Strength_Reply_Points"].begin(); itor != root["Strength_Reply_Points"].end(); ++itor) {
			personality_mults.push_back((*itor)["honor"].asInt());
			personality_mults.push_back((*itor)["pride"].asInt());
			personality_mults.push_back((*itor)["aggression"].asInt());
			personality_mults.push_back((*itor)["kindness"].asInt());
			personality_mults.push_back((*itor)["extroversion"].asInt());
			personality_mults.push_back((*itor)["greed"].asInt());
			personality_mults.push_back((*itor)["recklessness"].asInt());

			relationship_vals.push_back((*itor)["affinity"].asInt());
			relationship_vals.push_back((*itor)["notoriety"].asInt());
			relationship_vals.push_back((*itor)["strength"].asInt());
			relationship_vals.push_back((*itor)["AffEstimate"].asInt());
			relationship_vals.push_back((*itor)["NotorEstimate"].asInt());
			relationship_vals.push_back((*itor)["StrEstimate"].asInt());

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic);
			personality_mults.clear();
			relationship_vals.clear();
		}
		personality_mults.clear();
		relationship_vals.clear();

		for (auto itor = root["Notoriety_Conversation_Points"].begin(); itor != root["Notoriety_Conversation_Points"].end(); ++itor) {
			personality_mults.push_back((*itor)["honor"].asInt());
			personality_mults.push_back((*itor)["pride"].asInt());
			personality_mults.push_back((*itor)["aggression"].asInt());
			personality_mults.push_back((*itor)["kindness"].asInt());
			personality_mults.push_back((*itor)["extroversion"].asInt());
			personality_mults.push_back((*itor)["greed"].asInt());
			personality_mults.push_back((*itor)["recklessness"].asInt());

			relationship_vals.push_back((*itor)["affinity"].asInt());
			relationship_vals.push_back((*itor)["notoriety"].asInt());
			relationship_vals.push_back((*itor)["strength"].asInt());
			relationship_vals.push_back((*itor)["AffEstimate"].asInt());
			relationship_vals.push_back((*itor)["NotorEstimate"].asInt());
			relationship_vals.push_back((*itor)["StrEstimate"].asInt());

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic);
			personality_mults.clear();
			relationship_vals.clear();
		}
		personality_mults.clear();
		relationship_vals.clear();

		for (auto itor = root["Notoriety_Reply_Points"].begin(); itor != root["Notoriety_Reply_Points"].end(); ++itor) {
			personality_mults.push_back((*itor)["honor"].asInt());
			personality_mults.push_back((*itor)["pride"].asInt());
			personality_mults.push_back((*itor)["aggression"].asInt());
			personality_mults.push_back((*itor)["kindness"].asInt());
			personality_mults.push_back((*itor)["extroversion"].asInt());
			personality_mults.push_back((*itor)["greed"].asInt());
			personality_mults.push_back((*itor)["recklessness"].asInt());

			relationship_vals.push_back((*itor)["affinity"].asInt());
			relationship_vals.push_back((*itor)["notoriety"].asInt());
			relationship_vals.push_back((*itor)["strength"].asInt());
			relationship_vals.push_back((*itor)["AffEstimate"].asInt());
			relationship_vals.push_back((*itor)["NotorEstimate"].asInt());
			relationship_vals.push_back((*itor)["StrEstimate"].asInt());

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals,topic);
			personality_mults.clear();
			relationship_vals.clear();
		}
}

void DialogueConfig::set_conv_point(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string icon, std::string temp, std::string name, std::vector<int> personality_vals,std::string corresponding_conv_point, std::vector<int> relationship_vals, std::string topic)
{
	gameplay_func->add_conv_point(icon, temp, name);
	tBuffer->run();
	/*std::ofstream ofs;
	ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	ofs <<  "name: " << Containers::conv_point_table[name] << std::endl;
	ofs.close();*/
	Containers::conv_point_table[name]->set_icon(icon);
	Containers::conv_point_table[name]->set_name(name);
	Containers::conv_point_table[name]->set_temp(temp);
	Containers::conv_point_table[name]->set_topic(topic);
	Containers::conv_point_table[name]->dpoint.push_back(icon);
	Containers::conv_point_table[name]->dpoint.push_back(temp);
	Containers::conv_point_table[name]->dpoint.push_back(corresponding_conv_point);
	if(name.find("Ask_About",0)!=string::npos || name.find("Move_To", 0) != string::npos)
	    Containers::conv_point_table[name]->dpoint.push_back(topic);
	else {
		Containers::conv_point_table[name]->dpoint.push_back("");
		Containers::conv_point_table[name]->set_topic("");
	}
	Containers::conv_point_table[name]->multipliers = new Personality();
	
	Containers::conv_point_table[name]->multipliers->setHonor(personality_vals[0]);
	Containers::conv_point_table[name]->multipliers->setPride(personality_vals[1]);
	Containers::conv_point_table[name]->multipliers->setAggression(personality_vals[2]);
	Containers::conv_point_table[name]->multipliers->setKindness(personality_vals[3]);
	Containers::conv_point_table[name]->multipliers->setExtroversion(personality_vals[4]);
	Containers::conv_point_table[name]->multipliers->setGreed(personality_vals[5]);
	Containers::conv_point_table[name]->multipliers->setRecklessness(personality_vals[6]);

	Containers::conv_point_table[name]->rel_multipliers = new Relationship();

	Containers::conv_point_table[name]->rel_multipliers->setAffinity(relationship_vals[0]);
	Containers::conv_point_table[name]->rel_multipliers->setNotoriety(relationship_vals[1]);
	Containers::conv_point_table[name]->rel_multipliers->setStrength(relationship_vals[2]);
	Containers::conv_point_table[name]->rel_multipliers->setAffEstimate(relationship_vals[3]);
	Containers::conv_point_table[name]->rel_multipliers->setNotorEstimate(relationship_vals[4]);
	Containers::conv_point_table[name]->rel_multipliers->setStrEstimate(relationship_vals[5]);

	tBuffer->run();
}