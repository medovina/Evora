﻿#pragma once
#include "AI.h"
#include <random>

namespace AI
{
	class RandomAI :public AI
	{
		 std::mt19937 m_rng;
	public:
		void move() override;
		RandomAI(std::shared_ptr<control::game_controller> controller);
		const char* get_name() const override;
	};
}