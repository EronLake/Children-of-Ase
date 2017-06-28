#include "stdafx.h"
#include "GameState.h"
#include "Village.h"
#include "Alliance.h"
#include "Hero.h"

const extern int OVERLORD_END = 1;
const extern int ALLIANCE_END = 2;
const extern int WORLDPEACE_END = 3;

//Eron: needs to be moved to separate file
void GameState::check_if_end_game(game_state* current_game_state) {

	bool game_over = false;
	//int free_alliance_count = 0;
	std::vector<Alliance*> free_alliances;
	int end_game_type = 0;

	//goes through each alliances
	for (int i = 0; i < Alliance::get_alliances().size(); i++) 
	{
		std::vector<Village*> alligned_vils = Alliance::get_alliances()[i]->get_alligned_villages();
		int conquer_count = 0;
		//goes through each village in the alliance
		for (int j = 0; j < alligned_vils.size(); j++) {
			if (alligned_vils[j]->get_conquerer())
			{
				conquer_count++;
			}
		}
		/*
		if any village in the alliance is conquered then this is not a free alliance
		but if none of the villages in the alliance are conquered then it is a free alliance
		*/
		if (conquer_count == 0) {
			//free_alliance_count++;
			free_alliances.push_back(Alliance::get_alliances()[i]);
		}
	}

	//if only one free alliance then the game is over with that alliance being the winner
	if (free_alliances.size() == 1) {

		if (free_alliances[0]->get_alligned_villages().size() == 1) 
		{
			end_game_type = OVERLORD_END;
		}
		else if (free_alliances[0]->get_alligned_villages().size() > 1 &&
				free_alliances[0]->get_alligned_villages().size() < Containers::hero_table.size())
		{
			end_game_type = ALLIANCE_END;
		}
		else if (free_alliances[0]->get_alligned_villages().size() == Containers::hero_table.size())
		{
			end_game_type = WORLDPEACE_END;
		}

		*current_game_state = game_state::victory_menu;
	}

	


	/*
	Village* player_vil = dynamic_cast<Player*>(Containers::hero_table["Shango"])->getVillage();
	Village* yemoja_vil = Containers::hero_table["Yemoja"]->getVillage();
	Village* oya_vil = Containers::hero_table["Oya"]->getVillage();

	vector<Village*>  player_allies = player_vil->get_alliance()->get_alligned_villages();
	//checks if there is only one alliance left end the game (everyone is alligned)

	//bool temp = std::find(player_allies.begin(), player_allies.end(), oya_vil) != player_allies.end();

	//bool temp2 = (yemoja_vil->get_conquerer() == player_vil || yemoja_vil->get_conquerer() == oya_vil);

	
	if (Alliance::get_num_alliances() == 1) // the world is alligned!
		/*
		std::find(player_allies.begin(), player_allies.end(), yemoja_vil) != player_allies.end() && 
		std::find(player_allies.begin(), player_allies.end(), oya_vil) != player_allies.end())
		
	{
		*current_game_state = game_state::victory_menu;
	}
	//checks if both heroes are conquered (the player conqured the world)
	else if (yemoja_vil->get_conquerer() == player_vil && oya_vil->get_conquerer() == player_vil)
	{
		*current_game_state = game_state::victory_menu;
	}
	//checks if the hero is alligned with the conqurer (the player teamed up and conqurred the yemoja)
	else if (std::find(player_allies.begin(), player_allies.end(), oya_vil) != player_allies.end() &&
		(yemoja_vil->get_conquerer() == player_vil || yemoja_vil->get_conquerer() == oya_vil))
	{
		*current_game_state = game_state::victory_menu;
	}
	//checks if the hero is alligned with the conqurer (the player teamed up and conqurred the oya)
	else if (std::find(player_allies.begin(), player_allies.end(), yemoja_vil) != player_allies.end() &&
		(oya_vil->get_conquerer() == player_vil || oya_vil->get_conquerer() == yemoja_vil))
	{
		*current_game_state = game_state::victory_menu;
	}
	*/

	

}

void GameState::reset_game(game_state* current_game_state) {
	/*(HeroConfig::import_config(movVec_ptr, &ObjConfig::textureMap, gameplay_functions, tBuffer);
	SoldierConfig::import_config(movVec_ptr, &ObjConfig::textureMap, gameplay_functions, tBuffer);
	VillagerConfig::import_config(recVec_ptr, &ObjConfig::textureMap, gameplay_functions, tBuffer);
	BabalawoConfig::import_config(recVec_ptr, &ObjConfig::textureMap, gameplay_functions, tBuffer);
	ShrineConfig::import_config(recVec_ptr, &ObjConfig::textureMap, gameplay_functions, tBuffer);
	Village::init_villages();
	AIController::init_plans();*/
}