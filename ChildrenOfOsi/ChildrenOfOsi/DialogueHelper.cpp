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
	srand(time(0)); // seed the rand function
	possible_conv_pts.push_back({ "what", "variable" });
	possible_conv_pts.push_back({ "who", "variable" });
	possible_conv_pts.push_back({ "where", "variable" });
	possible_conv_pts.push_back({ "how", "variable" });
	possible_conv_pts.push_back({ "why", "variable" });


	possible_reply_pts.push_back({ "what", "variable" });
	possible_reply_pts.push_back({ "who", "variable" });
	possible_reply_pts.push_back({ "where", "variable" });
	possible_reply_pts.push_back({ "how", "variable" });
	possible_reply_pts.push_back({ "why", "variable" });

}


DialogueHelper::~DialogueHelper()
{
}

//functions where heroes make dialogue choices
dialogue_point DialogueHelper::choose_conv_pt(dialogue_point)
{
	int conv_pt_index = rand() % possible_conv_pts.size();
	return possible_conv_pts[conv_pt_index];


}

dialogue_point DialogueHelper::choose_reply_pt(dialogue_point point)
{
	for (int i = 0; i < possible_reply_pts.size(); i++)
	{
		if (possible_reply_pts[i][0] == point[0])
		{
			return possible_reply_pts[i];
		}
	}
	return{ "error phrase_type not found" };

}

std::vector<dialogue_point> DialogueHelper::get_possible_conv_pts()
{
	return possible_conv_pts;
}

std::vector<dialogue_point> DialogueHelper::get_possible_reply_pts()
{
	return possible_conv_pts;
}

dialogue_template DialogueHelper::get_template() {
	Json::Value root;
	Json::Reader reader;

	std::ifstream file("script_templates.json");
	file >> root;

	
	dialogue_template dtemp;

	//get a random conversation template
	int j = rand() % root["conversation_templates"].size() + 1;

	/*populate a dialogue template using the contents
	of the randomly obtained dialogue template*/
	for (int i = 1; i <= root["conversation_templates"]
		[to_string(j)].size(); i++) {
		dtemp.push_back(root["conversation_templates"][to_string(j)]
			[to_string(i)].asString());
	}

	return dtemp;

}

dialogue_point DialogueHelper::get_dialog(std::string name) {

	dialogue_template dtemp = get_template();

	Json::Value root;
	Json::Reader reader;

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
