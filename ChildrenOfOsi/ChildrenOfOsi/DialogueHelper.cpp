#include "stdafx.h"
#include "DialogueHelper.h"
#include "Player.h"
#include "Tag.h"


Player* player;
WorldObj* other;
int state = 0;
//States:
//0 is no conversation
//1 is waiting for player input
//2 is waiting for player response
//3 is npc conversation point
//4 is npc response
DialogueHelper dialogue;

DialogueHelper::DialogueHelper()
{
	srand(time(0)); //ensure good variation of random numbers when using rand()
}


DialogueHelper::~DialogueHelper()
{
}

//functions where heroes make dialogue choices
dialogue_point DialogueHelper::choose_conv_pt(std::vector<ConversationLogObj*> conversation_log_obj_pointer_vec, int optn_inx)
{	
	std::vector<ConversationPoint*> temp;
	int conv_pt_index;
	
	

	for (auto i = conversation_log_obj_pointer_vec.begin(); i != conversation_log_obj_pointer_vec.end(); ++i) {
		//auto it = std::find(temp.begin(), temp.end(), (*i)->get_conv_point());
		//if (it != temp.end()) {
		//	temp.erase(std::remove(temp.begin(), temp.end(), *it), temp.end());
		//}
		//else {

		// }
		for (auto j : (*i)->get_conv_point()->tag_pointer_vec) {
			for (auto k : j->conversation_point_pointer_vec) {
				if (std::find(temp.begin(), temp.end(), k) != temp.end()) {
				}
				else {
				temp.push_back(k);
				}
			
			
		      }


	    }
		
	}
	for (auto i = conversation_log_obj_pointer_vec.begin(); i != conversation_log_obj_pointer_vec.end(); ++i) {
		auto it = std::find(temp.begin(), temp.end(), (*i)->get_conv_point());
		if (it != temp.end() && (*i)->get_who() == 2) {
			temp.erase(std::remove(temp.begin(), temp.end(), *it), temp.end());
		}
		else {

		}
	}
	//relationship filtering
	std::ofstream ofs;
	ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::trunc);
	for (auto itor = temp.begin(); itor != temp.end(); itor++) {
	
	ofs << "Conversation Point Name: " << (*itor)->get_name() << " Tag Name: " << std::endl;

	}
	ofs.close();
	//choose based on personality
	if (temp.size() > 0)
		conv_pt_index = rand() % (temp.size());
	else
		return {"No_More_Phrases","No_More_Phrases"}; //gets json that npc says when they fail to find an appropriate thing to say
	return temp[conv_pt_index]->dpoint;
}

dialogue_point DialogueHelper::choose_reply_pt(std::string point, int optn_inx)
{
	for (int i = 0; i < possible_reply_pts[optn_inx].size(); i++)
	{
		//if (possible_reply_pts[optn_inx][i][1].find(point, 0) != std::string::npos)
		//{
		//	return possible_reply_pts[optn_inx][i];
		//}
		if (possible_reply_pts[optn_inx][i][2] == point)
		{
			return possible_reply_pts[optn_inx][i];
		}
	}
	return{ "error phrase_type not found" };

}

std::vector<std::vector<dialogue_point>> DialogueHelper::get_possible_conv_pts()
{
	return possible_conv_pts;
}

std::vector<dialogue_point> DialogueHelper::get_possible_reply_pts(std::string point, int opts_inx)
{
	std::vector<dialogue_point> reply;
	for (int i = 0; i < possible_reply_pts[opts_inx].size(); i++) {
		if (possible_reply_pts[opts_inx][i][2].compare("Decline_To_Answer") == 0 || possible_reply_pts[opts_inx][i][2].compare(point) == 0) {
			reply.push_back({ possible_reply_pts[opts_inx][i] });
		}
	}
	return reply;
}

std::string DialogueHelper::gen_dialog(dialogue_point diog_pt, Hero* hero, int relationship_phrase_picker, int relationship_phrase_picker_shango)
{
	std::string name = "";
	//std::ofstream ofs;
	//ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	//ofs << "type name: " << typeid(hero).name() << std::endl;
	//ofs.close();
	if (hero != nullptr) {
		if (hero->name == SHANGO)
		{
			name = "Shango";
		}
		else if (hero->name == YEMOJA)
		{
			name = "Yemoja";
		}
		else if (hero->name == OSHOSI)
		{
			name = "Oshosi";
		}
		else if (hero->name == OYA)
		{
			name = "Oya";
		}
		else if (hero->name == OGUN)
		{
			name = "Ogun";
		}
	}
	else {
		name = "SilverSoldier";
	}
	std::string sentence = convert_to_sentence(get_dialog(name, diog_pt, relationship_phrase_picker, relationship_phrase_picker_shango));

	return sentence;
}

//poientially don't need this function
std::string DialogueHelper::gen_reply(dialogue_point diog_pt, Hero* hero, int relationship_phrase_picker, int relationship_phrase_picker_shango)
{
	std::string name;
	if (hero->name == SHANGO)
	{
		name = "Shango";
	}
	else if (hero->name == YEMOJA)
	{
		name = "Yemoja";
	}
	else if (hero->name == OSHOSI)
	{
		name = "Oshosi";
	}
	else if (hero->name == OYA)
	{
		name = "Oya";
	}
	else if (hero->name == OGUN)
	{
		name = "Ogun";
	}

	std::string sentence = convert_to_sentence(get_dialog(name, diog_pt, relationship_phrase_picker, relationship_phrase_picker_shango));

	return sentence;
}

dialogue_template DialogueHelper::get_template(dialogue_point diog_pt) {
	Json::Value root;
	Json::Reader reader;

	std::ifstream file("script_templates.json");
	file >> root;


	dialogue_template dtemp;

	//get a random conversation template
	int j = 0;
	if (root[diog_pt[1] + "_Templates"].size() > 1)
		j = rand() % root[diog_pt[1] + "_Templates"].size() + 1;
	else
		j = 1;
	/*populate a dialogue template using the contents
	of the randomly obtained dialogue template*/
	for (int i = 1; i <= root[diog_pt[1] + "_Templates"]
		[to_string(j)].size(); i++) {
		dtemp.push_back(root[diog_pt[1] + "_Templates"][to_string(j)]
			[to_string(i)].asString());
	}

	return dtemp;

}

dialogue_point DialogueHelper::get_dialog(std::string name, dialogue_point diog_pt, int relationship_phrase_picker, int shango_phrase_picker) {
	//std::ofstream ofs;
	//ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	dialogue_template dtemp = get_template(diog_pt);

	std::string my_name = name;
	if (name != "Yemoja" && name != "Shango" && name != "Oshosi" && name != "Ogun" && name != "Oya")
		my_name = "SilverSoldier";
	//////////////////////////////////
	/*add several else if statements here as more NPCs are added to the game in
	order to handle different json files for every NPC. json files are opened on a
	name basis*/
	//////////////////////////////////

	Json::Value root;

	std::string dialogue_filename = my_name + "_dialog.json";

	std::ifstream file(dialogue_filename);
	file >> root;

	dialogue_point dpoint;
	
	/*look up appropriate random phrases using dialogue template
	if the string is punctuation then do not look it up and
	instead push the string right away*/

	///////////////////////////////////
	/*Do not use randomness to determine the dialogue_point if the name passed 
	into this function is Shango. Make what appears on upper GUI window be what 
	the player selected to say.*/
	///////////////////////////////////
	int j = 1;
	if (name != "Shango") {
		j = relationship_phrase_picker;
		std::string tmp = "";
		for (int i = 1; i <= dtemp.size(); i++) {
			tmp = dtemp[i - 1];
			if (tmp != "?" && tmp != "," && tmp != "." &&
				tmp != "!" && tmp != "_") {
				//if (root[tmp].size() > 1)
					//j = rand() % root[tmp].size() + 1;
				//else
					//j = 1;
				dpoint.push_back(root[tmp][to_string(j)]
					.asString());
				//ofs << "dp: " << root[tmp][to_string(j)]
					//.asString() << std::endl;
			}
			else {
				dpoint.push_back(tmp);

			}

		}
	}
	else {
		j = shango_phrase_picker;
		dpoint.push_back(root[diog_pt[1]][to_string(j)]
			.asString());
	}

	return dpoint;

}

std::string DialogueHelper::convert_to_sentence(dialogue_point dialog_pt)
{
	string sentence;
	for (auto i = dialog_pt.begin(); i != dialog_pt.end(); ++i) {
		std::string tmp = "";
		for (auto j = (*i).begin(); j != (*i).end(); ++j) {
			tmp += *j;
		}
		sentence += tmp;
	}
	return sentence;
}

void DialogueHelper::fill_conversations() {
	for (int i = 0; i < Containers::conv_point_table.size(); i++)
	{
		possible_conv_pts.push_back({});
	}
	for (int i = 0; i < Containers::conv_point_table.size(); i++)
	{
		possible_reply_pts.push_back({});
	}
	for (auto itor = Containers::conv_point_table.begin(); itor != Containers::conv_point_table.end(); ++itor) {
		if (itor->second->get_topic() == "qcp") {
			possible_conv_pts[3].push_back(itor->second->dpoint);//itor->second->dpoint);
		}
		else if (itor->second->get_topic() == "qrp") {
			possible_reply_pts[3].push_back(itor->second->dpoint);
			possible_reply_pts[0].push_back(itor->second->dpoint);
			possible_reply_pts[1].push_back(itor->second->dpoint);
			possible_reply_pts[2].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_topic() == "d") {
			
				possible_reply_pts[3].push_back(itor->second->dpoint);
				possible_reply_pts[0].push_back(itor->second->dpoint);
				possible_reply_pts[1].push_back(itor->second->dpoint);
				possible_reply_pts[2].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_topic() == "scp") {
			possible_conv_pts[0].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_topic() == "srp") {
			possible_reply_pts[3].push_back(itor->second->dpoint);
			possible_reply_pts[0].push_back(itor->second->dpoint);
			possible_reply_pts[1].push_back(itor->second->dpoint);
			possible_reply_pts[2].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_topic() == "acp") {
			possible_conv_pts[1].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_topic() == "arp" || itor->second->get_topic() == "nmp") {
			possible_reply_pts[3].push_back(itor->second->dpoint);
			possible_reply_pts[0].push_back(itor->second->dpoint);
			possible_reply_pts[1].push_back(itor->second->dpoint);
			possible_reply_pts[2].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_topic() == "ncp") {
			possible_conv_pts[2].push_back(itor->second->dpoint);
		}
		else {
			possible_reply_pts[3].push_back(itor->second->dpoint);
			possible_reply_pts[0].push_back(itor->second->dpoint);
			possible_reply_pts[1].push_back(itor->second->dpoint);
			possible_reply_pts[2].push_back(itor->second->dpoint);
		}
	}
}
