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

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic, (*itor)["hero_reply"].asString());
			personality_mults.clear();
			relationship_vals.clear();

			//this is where the helper func should be called
			import_conditions(itor, (*itor)["name"].asString());
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

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic, (*itor)["hero_reply"].asString());
			personality_mults.clear();
			relationship_vals.clear();

			import_conditions(itor, (*itor)["name"].asString());
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

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic, (*itor)["hero_reply"].asString());
			personality_mults.clear();
			relationship_vals.clear();

			import_conditions(itor, (*itor)["name"].asString());
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

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic, (*itor)["hero_reply"].asString());
			personality_mults.clear();
			relationship_vals.clear();

			import_conditions(itor, (*itor)["name"].asString());
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

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic, (*itor)["hero_reply"].asString());
			personality_mults.clear();
			relationship_vals.clear();

			import_conditions(itor, (*itor)["name"].asString());
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

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic, (*itor)["hero_reply"].asString());
			personality_mults.clear();
			relationship_vals.clear();

			import_conditions(itor, (*itor)["name"].asString());
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

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals, topic, (*itor)["hero_reply"].asString());
			personality_mults.clear();
			relationship_vals.clear();

			import_conditions(itor, (*itor)["name"].asString());
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

			set_conv_point(gameplay_func, tBuffer, (*itor)["icon"].asString(), (*itor)["template"].asString(), (*itor)["name"].asString(), personality_mults, (*itor)["corresponding_conv_point"].asString(), relationship_vals,topic, (*itor)["hero_reply"].asString());
			personality_mults.clear();
			relationship_vals.clear();

			import_conditions(itor, (*itor)["name"].asString());
		}
}

void DialogueConfig::set_conv_point(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string icon, 
	std::string temp, std::string name, std::vector<int> personality_vals,std::string corresponding_conv_point, std::vector<int> relationship_vals, std::string topic, std::string hero_reply)
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
	if(name.find("Ask About",0)!=string::npos || name.find("Advise To", 0) != string::npos)
	    Containers::conv_point_table[name]->dpoint.push_back(topic);
	else {
		Containers::conv_point_table[name]->dpoint.push_back("");
		Containers::conv_point_table[name]->set_topic("");
	}
	std::string is_selectable = "1";
	Containers::conv_point_table[name]->dpoint.push_back(is_selectable);
	Containers::conv_point_table[name]->set_is_selectable(is_selectable);

	Containers::conv_point_table[name]->dpoint.push_back(hero_reply);

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


void DialogueConfig::import_conditions(Json::Value::iterator itr, std::string name)
{

	for (auto it = (*itr)["req_preconds"].begin(); it != (*itr)["req_preconds"].end(); it++)
	{
		if ((*it)["general_type"].asInt() == 0)
		{
			RelPrecon* temp_prec = new RelPrecon((*it)["rel_type"].asInt(), (*it)["desired_rel_val"].asInt());

			Containers::conv_point_table[name]->req_preconds.push_back(std::make_shared<RelPrecon>(*temp_prec));
		}
		else if ((*it)["general_type"].asInt() == 1)
		{
			RelEstimPrerec* temp_prec = new RelEstimPrerec((*it)["rel_type"].asInt(), (*it)["desired_rel_val"].asInt());

			Containers::conv_point_table[name]->req_preconds.push_back(std::make_shared<RelEstimPrerec>(*temp_prec));
		}
		else if ((*it)["general_type"].asInt() == 2)
		{
			TimePrerec* temp_prec = new TimePrerec((*it)["time_rec"].asInt());

			Containers::conv_point_table[name]->req_preconds.push_back(std::make_shared<TimePrerec>(*temp_prec));
		}
		else if ((*it)["general_type"].asInt() == 3)
		{
			MemoryNumPrerec* temp_prec = new MemoryNumPrerec((*it)["rec_num_of_mem"].asInt());

			Containers::conv_point_table[name]->req_preconds.push_back(std::make_shared<MemoryNumPrerec>(*temp_prec));
		}
		else if ((*it)["general_type"].asInt() == 4)
		{
			MemPrerec* temp_prec = new MemPrerec((*it)["rec_mem"].asString());

			Containers::conv_point_table[name]->req_preconds.push_back(std::make_shared<MemPrerec>(*temp_prec));
		}
		else if ((*it)["general_type"].asInt() == 5)
		{
			StatePrerec* temp_prec = new StatePrerec((*it)["state_type"].asInt());

			Containers::conv_point_table[name]->req_preconds.push_back(std::make_shared<StatePrerec>(*temp_prec));
		}
	}

	import_post_conditions(itr, name, "doer_succ_postconds");
	import_post_conditions(itr, name, "doer_fail_postconds");
	import_post_conditions(itr, name, "receiver_succ_postconds");
	import_post_conditions(itr, name, "receiver_fail_postconds");

	/*
	Containers::action_table[name]->op_preconds.push_back();
	*/
}


//this is a helper function for import conditions
void DialogueConfig::import_post_conditions(Json::Value::iterator itr, std::string name, std::string which_post) {

	//assigns the postconditions to the appropieate map 
	vector<std::shared_ptr<Postcondition>>* postconds;
	if (which_post == "doer_succ_postconds")
	{
		postconds = &Containers::conv_point_table[name]->doer_succ_postconds;
	}
	else if (which_post == "doer_fail_postconds")
	{
		postconds = &Containers::conv_point_table[name]->doer_fail_postconds;
	}
	else if (which_post == "receiver_succ_postconds")
	{
		postconds = &Containers::conv_point_table[name]->receiver_succ_postconds;
	}
	else //if (which_post == "receiver_fail_postconds")
	{
		postconds = &Containers::conv_point_table[name]->receiver_fail_postconds;
	}


	for (auto it = (*itr)[which_post].begin(); it != (*itr)[which_post].end(); it++)
	{
		if ((*it)["general_type"].asInt() == 0)
		{
			RelPost* temp_post = new RelPost((*it)["rel_type"].asInt(), (*it)["utility"].asInt());

			postconds->push_back(std::make_shared<RelPost>(*temp_post));
		}
		else if ((*it)["general_type"].asInt() == 1)
		{
			RelEstimPost* temp_post = new RelEstimPost((*it)["rel_type"].asInt(), (*it)["utility"].asInt());

			postconds->push_back(std::make_shared<RelEstimPost>(*temp_post));
		}
		else if ((*it)["general_type"].asInt() == 5)
		{
			StatePost* temp_post = new StatePost((*it)["state_type"].asInt(),(*it)["utility"].asInt());

			postconds->push_back(std::make_shared<StatePost>(*temp_post));
		}
	}
}