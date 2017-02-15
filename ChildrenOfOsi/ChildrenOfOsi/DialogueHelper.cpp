#include "stdafx.h"
#include "DialogueHelper.h"


DialogueHelper::DialogueHelper()
{

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

dialogue_point DialogueHelper::choose_reply(dialogue_point point)
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
/*
std::vector<dialogue_point> DialogueHelper::get_possible_conv_pts()
{
	return possible_conv_pts;
}

std::vector<dialogue_point> DialogueHelper::get_possible_reply_pts()
{
	return possible_conv_pts;
}
*/