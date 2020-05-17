#pragma once
#include "command.h"

namespace control
{
	class score_wall_tile :public command
	{
	public:
		score_wall_tile(int player_index, int line_index, model::tile color)
			: m_player_index(player_index),
			  m_line(line_index),
			  m_color(color)
		{}

		void Execute(std::shared_ptr<model::game> game) override;
		void Unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool IsMove() override;
	private:
		int m_player_index;
		int m_line;
		model::tile m_color = model::tile::empty;
		int m_score = 0;
	};
}

