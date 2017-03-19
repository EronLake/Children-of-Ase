#include "stdafx.h"
#include "TagConfig.h"


TagConfig::TagConfig()
{
}


TagConfig::~TagConfig()
{
}

void TagConfig::import_config(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{

	Json::Value root;
	Json::Reader reader;


	std::ifstream file("Dialogue_config.json");
	file >> root;
	for (auto itr = root.begin(); itr != root.end(); itr++)
	{
		set_tag(gameplay_func, tBuffer, (*itr)["name"].asString());
	}
	std::cout << "done" << endl;




}

void TagConfig::set_tag(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string name)
{

		//gameplay_func->add_tag(name);

		//set file takes up memory
		tBuffer->run();
		//Containers::texture_table[tex_file]->setFile("Assets/Sprites/" + tex_file + ".png", frame_num);


	/* For Spencer
	if (tex_file == "){
	gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	}
	*/

	//gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);

	tBuffer->run();

	//Containers::worldObj_table[name]->setWidth(width);
	//Containers::worldObj_table[name]->setHeight(hight);

	//Containers::worldObj_table[name]->sprite.setTexture(Containers::texture_table[tex_file]);
	Containers::worldObj_table[name]->setInteractable(false);

	//Containers::worldObj_table[name]->offsetBody(0, 0, 0, 0, 0);

	//recVec->push_back(Containers::worldObj_table[name]);


}