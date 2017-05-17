#pragma once
#include "common.h"

enum class game_state {load_game,main_menu, pause_menu, in_game, victory_menu};

template <typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

class GameState {
	public:
		static void check_if_end_game(game_state* current_game_state);
};
