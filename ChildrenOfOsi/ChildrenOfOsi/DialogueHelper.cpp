#include "stdafx.h"
#include "DialogueHelper.h"


DialogueHelper::DialogueHelper()
{

	possible_conv_pts.push_back(std::make_pair("what", "variable"));
	possible_conv_pts.push_back(std::make_pair("who", "variable"));
	possible_conv_pts.push_back(std::make_pair("where", "variable"));
	possible_conv_pts.push_back(std::make_pair("how", "variable"));
	possible_conv_pts.push_back(std::make_pair("why", "variable"));


	possible_replys.push_back(std::make_pair("what", "variable"));
	possible_replys.push_back(std::make_pair("who", "variable"));
	possible_replys.push_back(std::make_pair("where", "variable"));
	possible_replys.push_back(std::make_pair("how", "variable"));
	possible_replys.push_back(std::make_pair("why", "variable"));

}


DialogueHelper::~DialogueHelper()
{
}

//functions where heroes make dialogue choices
std::tuple<std::string, std::string> DialogueHelper::choose_conv_pt(std::string phrase_type, 
																	std::string variable)
{
	int conv_pt_index = rand() % possible_conv_pts.size();
	return possible_conv_pts[conv_pt_index];


}

std::tuple<std::string, std::string> DialogueHelper::choose_reply(std::string phrase_type, 
																	std::string variable)
{
	for (int i = 0; i < possible_replys.size(); i++)
	{
		if (std::get<0>(possible_replys[i]) == phrase_type)
		{
			return possible_replys[i];
		}
	}
	return std::make_pair("error","phrase_type not found");

}