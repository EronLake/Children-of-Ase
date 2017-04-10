#include "stdafx.h"
#include "Tag.h"

/*There should be 7 instances of the tag class. The 7 tags that were agreed upon
are as follows: info_about_other_heroes, 
                getting_to_know_each_other, 
                recent_memories, 
                specific_event, 
                gossip_news, 
                talk_about_relationship_field, 
                strategy_possible_actions
Each of these tags will have a conversation_point_pointer_vec field that will contain 
pointers to every conversation point that fits under them. For example, a 
conversation point about asking someone's name will have it's pointer placed in the 
conversation_point_pointer_vec for the getting_to_know_each_other tag.*/

Tag::Tag()
{
	multipliers = nullptr;
}

Tag::Tag(std::vector<std::string> topicVec, std::string _name)
{
	name = _name;
	Containers::tag_table[name]->name;
	std::ofstream ofs;
	ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	for (auto itor = Containers::conv_point_table.begin(); itor != Containers::conv_point_table.end(); itor++){
		for (auto itor_1 = topicVec.begin(); itor_1 != topicVec.end(); itor_1++){
			std::string temp = *itor_1;
			if ((itor->second->get_topic().compare(temp) == 0)){
				Containers::tag_table[name]->set_tags_helper(itor->second);
			}
		}
	}
	for (int i = 0; i < topicVec.size(); i++) {
		ofs << "TopicVec[" << i << "]: " << topicVec[i] << std::endl;
	}
	ofs << "TagTableSize: " << Containers::tag_table.size() << std::endl;
	ofs.close();
}


Tag::~Tag()
{
	delete (multipliers);
}

void Tag::set_tags_helper(ConversationPoint* conPoint){
	conversation_point_pointer_vec.push_back(conPoint);
}


void Tag::set_name(std::string val) {
	name = val;
}
std::string Tag::get_name() {
	return name;
}
