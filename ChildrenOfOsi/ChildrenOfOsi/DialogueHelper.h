#pragma once
#include "common.h"

class DialogueHelper
{
private:
	std::vector<std::tuple<std::string, std::string>> possible_conv_pts;
	std::vector<std::tuple<std::string, std::string>> possible_replys;



public:
	DialogueHelper();
	~DialogueHelper();

	//functions where heroes make dialogue choices
	std::tuple<std::string,std::string> choose_conv_pt(std::string phrase_type,std::string variable);
	std::tuple<std::string,std::string> choose_reply(std::string phrase_type, std::string variable);
};

