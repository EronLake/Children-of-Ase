#include "GameState.h"
#include "Village.h"
#include "Alliance.h"
#include "Hero.h"


//Eron: needs to be moved to separate file
void GameState::check_if_end_game(game_state* current_game_state) {
	Village* player_vil = dynamic_cast<Player*>(Containers::hero_table["Shango"])->getVillage();
	Village* yemoja_vil = Containers::hero_table["Shango"]->getVillage();
	Village* oya_vil = Containers::hero_table["Shango"]->getVillage();

	vector<Village*>  player_allies = player_vil->get_alliance()->get_alligned_villages();
	//checks if there is only one alliance left end the game (everyone is alligned)

	//bool temp = std::find(player_allies.begin(), player_allies.end(), yemoja_vil) != player_allies.end();
	//bool temp2 = std::find(player_allies.begin(), player_allies.end(), oya_vil) != player_allies.end();

	if (Alliance::get_num_alliances() == 1)
		/*
		std::find(player_allies.begin(), player_allies.end(), yemoja_vil) != player_allies.end() && 
		std::find(player_allies.begin(), player_allies.end(), oya_vil) != player_allies.end())
		*/
	{
		*current_game_state = game_state::victory_menu;
	}
	//checks if both heroes are conquered (the player conqured the world)
	else if (yemoja_vil->get_conquerer() == player_vil && oya_vil->get_conquerer() == player_vil)
	{
		*current_game_state = game_state::victory_menu;
	}
	//checks if the hero is alligned with the conqurer (the player teamed up and conqurred the yemoja)
	else if (player_vil->get_alliance()->get_alligned_villages()[0] == oya_vil &&
		(yemoja_vil->get_conquerer() == player_vil || yemoja_vil->get_conquerer() == oya_vil))
	{
		*current_game_state = game_state::victory_menu;
	}
	//checks if the hero is alligned with the conqurer (the player teamed up and conqurred the oya)
	else if (player_vil->get_alliance()->get_alligned_villages()[0] == yemoja_vil &&
		(oya_vil->get_conquerer() == player_vil || oya_vil->get_conquerer() == yemoja_vil))
	{
		*current_game_state = game_state::victory_menu;
	}
}