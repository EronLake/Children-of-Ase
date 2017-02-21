#include "stdafx.h"
#include "DialogueHelper.h"
#include "Player.h"

Player* player;
WorldObj* other;
int state=0;
//States:
//0 is no conversation
//1 is waiting for player input
//2 is waiting for player response
//3 is npc conversation point
//4 is npc response
DialogueHelper dialogue;

DialogueHelper::DialogueHelper()
{
	//srand(time(0)); // seed the rand function
	//possible_conv_pts[0].push_back({ "placeholder","placeholder" });
	//possible_conv_pts[1].push_back({ "placeholder","placeholder" });
	//possible_conv_pts[2].push_back({ "placeholder","placeholder" });
	for (int i = 0; i < 5; i++) 
	{
		possible_conv_pts.push_back({});
	}
	for (int i = 0; i < 5; i++) 
	{
		possible_reply_pts.push_back({});
	}

	possible_conv_pts[3].push_back({ "name","question_name" });
	possible_conv_pts[3].push_back({ "reason","question_reason" });
	possible_conv_pts[3].push_back({ "origin","question_origin" });
	//possible_conv_pts[3].push_back({ "greeting","greeting" });

	possible_reply_pts[3].push_back({ "denied","question_denied" });
	possible_reply_pts[3].push_back({ "name","introduction" });
	possible_reply_pts[3].push_back({ "reason","response_reason" });
	possible_reply_pts[3].push_back({ "origin","response_origin" });

}


DialogueHelper::~DialogueHelper()
{
}

//functions where heroes make dialogue choices
dialogue_point DialogueHelper::choose_conv_pt(dialogue_point point, int optn_inx)
{
	int conv_pt_index = rand() % (possible_conv_pts[optn_inx].size());

	return possible_conv_pts[optn_inx][conv_pt_index];

}

dialogue_point DialogueHelper::choose_reply_pt(std::string point, int optn_inx)
{
	for (int i = 0; i < possible_reply_pts[optn_inx].size(); i++)
	{
		if (possible_reply_pts[optn_inx][i][0] == point)
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

std::vector<std::vector<dialogue_point>> DialogueHelper::get_possible_reply_pts()
{
	return possible_reply_pts;
}


std::string DialogueHelper::gen_dialog(dialogue_point diog_pt, Hero* hero)
{
	std::string name;
	std::cout << hero->name << std::endl;
	if (hero->name == SHANGO)
	{
		name = "Shango";
	}else if (hero->name == YEMOJA)
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
	std::cout << name << std::endl;
	std::string sentence = convert_to_sentence(get_dialog(name, diog_pt));

	std::cout << sentence << std::endl;
	return sentence;
}

//poientially don't need this function
std::string DialogueHelper::gen_reply(dialogue_point diog_pt, Hero* hero)
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

	std::string sentence = convert_to_sentence(get_dialog(name, diog_pt));

	std::cout << sentence << std::endl;
	return sentence;
}

dialogue_template DialogueHelper::get_template(dialogue_point diog_pt) {
	Json::Value root;
	Json::Reader reader;

	std::ifstream file("script_templates.json");
	file >> root;

	
	dialogue_template dtemp;

	std::cout << diog_pt[1] + "_templates" << std::endl;
	//get a random conversation template
	int j = rand() % root[diog_pt[1] + "_templates"].size() + 1;

	/*populate a dialogue template using the contents
	of the randomly obtained dialogue template*/
	for (int i = 1; i <= root[diog_pt[1] + "_templates"]
		[to_string(j)].size(); i++) {
		dtemp.push_back(root[diog_pt[1] + "_templates"][to_string(j)]
			[to_string(i)].asString());
	}
	for (int i = 0; i < dtemp.size(); i++)
	{
		std::cout << dtemp[i] << std::endl;
	}
	return dtemp;

}

dialogue_point DialogueHelper::get_dialog(std::string name, dialogue_point diog_pt) {

	dialogue_template dtemp = get_template(diog_pt);

	Json::Value root;
	Json::Reader reader;
	std::cout <<name + "_dialog.json" << std::endl;
	std::string dialogue_filename = name + "_dialog.json";

	std::ifstream file(dialogue_filename);
	file >> root;

	dialogue_point dpoint;
	

	/*look up appropriate random phrases using dialogue template
	if the string is punctuation then do not look it up and
	instead push the string right away*/
	int j = 0;
	std::string tmp = "";
	for (int i = 1; i <= dtemp.size(); i++ ) {
		tmp = dtemp[i - 1];
		if (tmp != "?" && tmp != "," && tmp != "." && 
			tmp != "!" && tmp != "_") {
			j = rand() % root[tmp].size() + 1;
			dpoint.push_back(root[tmp][to_string(j)]
				.asString());
		}
		else {
			dpoint.push_back(tmp);

		}

	}
	for (int i = 0; i < dpoint.size(); i++){
		std::cout << "dialogue point: "<< dpoint[i] << std::endl;
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

