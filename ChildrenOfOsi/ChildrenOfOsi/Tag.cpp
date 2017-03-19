#include "stdafx.h"
#include "Tag.h"


Tag::Tag()
{
	multipliers = nullptr;
}

Tag::Tag(std::vector<std::string> topicVec, std::string _name)
{
	name = _name;
	Containers::tag_table[name]->name;

	for (auto itor = Containers::conv_point_table.begin(); itor != Containers::conv_point_table.end(); itor++){
		for (auto itor_1 = topicVec.begin(); itor_1 != topicVec.end(); itor_1++){
			std::string temp = *itor_1;
			if ((itor->second->get_topic().compare(temp) == 0)){
				Containers::tag_table[name]->set_tags_helper(itor->second);
			}
		}
	}
}


Tag::~Tag()
{
	delete (multipliers);
}

void Tag::set_tags_helper(ConversationPoint* conPoint){
	pointVec.push_back(conPoint);
}


void Tag::set_name(std::string val) {
	name = val;
}
std::string Tag::get_name() {
	return name;
}
