﻿#include "AIFactory.h"
#include "RandomAI.h"

using namespace AI;


std::map<const char*, std::unique_ptr<AIFactory>, RawPointerComparison> AIFactory::get_factories()
{
	std::map < const char*, std::unique_ptr<AIFactory>, RawPointerComparison> res;
	res.insert({ "RandomAI", std::move(std::make_unique<RandomAIFactory>()) });
	return res;
}

std::unique_ptr<::AI::AI> RandomAIFactory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<RandomAI>(controller, board_index));
}
