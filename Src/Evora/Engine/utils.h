#pragma once
#include "AI.h"

namespace utils
{
	int play_game(std::vector<std::unique_ptr<AI::AI>>& players, std::shared_ptr<control::game_controller> controller, int current_player);
}
