#include "ad_ai.h"
#include "center_offer.h"
#include <memory>
#include "drop_center.h"
#include "factory_offer.h"
#include "drop_factory.h"
#include "utils.h"

using namespace model;

double evalPlayer(std::shared_ptr<control::game_controller>& controller, int player)
{
	double v = controller->get_score(player);
	board &board = controller->get_model()->get_board(player);
	wall wall = board.get_wall();  // local copy of the wall

	for (int y = 0 ; y < 5 ; ++y)
	{
		int count = board.get_pattern_line_tile_count(y);
		if (count > 0)
		{
			tile color = board.pattern_line_color(y);
			wall.add_tile(y, color);
			int row = ((int) color + y) % COLORS;
			int score = wall.score_tile(y, color) + wall.score_line(y) +
			            wall.score_row(row) + wall.score_color(color);
			double frac = 1.0 * count / (y + 1);
			v += frac * score;
		}
	}

	return v;
}

double ai::ad_ai::evaluate(std::shared_ptr<control::game_controller>& controller)
{
	return evalPlayer(controller, m_board_index) - evalPlayer(controller, 1 - m_board_index);
}

bool ai::ad_ai::update_scores(int player_index, double& best_score, double score, double &alpha, double &beta)
{
	if (player_index == m_board_index)
	{
		if (score > best_score)
		{
			best_score = score;
			if(score > alpha)
			{
				alpha = score;
			}
			return true;
		}
	}
	else
	{
		if (score < best_score)
		{
			best_score = score;
			if(score < beta)
			{
				beta = score;
			}
			return true;
		}
	}
	return false;
}

bool ai::ad_ai::alpha_beta_move(
	const std::shared_ptr<control::game_controller>& controller, std::unique_ptr<control::command> move,
    double& best_score, int depth, int player_index, double &alpha, double &beta)
{
	int next_player = controller->get_current_player();
	controller->add_command(move->clone());
	double score = minimax(next_player, depth + 1, controller, alpha, beta);
	controller->player_move_back();
	// printf("move %s: score = %.2f\n", move->to_string().c_str(), score);
	bool updated = update_scores(player_index, best_score, score, alpha, beta);
	if (depth == 0 && updated)
	{
		// printf("new best move: %s\n", move->to_string().c_str());
		m_best_move = std::move(move);
		return false;
	}
	if (alpha >= beta && updated)
	{
		return true;
	}
	return false;
}

double ai::ad_ai::minimax(int player_index, int depth, std::shared_ptr<control::game_controller> controller,
					      double alpha, double beta)
{
	if(depth!= 0)
	{
		controller->step();
	}
	std::shared_ptr<model::game> game = controller->get_model();
	if(depth == m_max_depth && !game->round_finished())
	{
		m_round_finished = false;
	}
	if(depth == m_max_depth || game->round_finished())
	{
		return evaluate(controller);
	}
	double best_score = player_index == m_board_index ?
		std::numeric_limits<double>::lowest() : std::numeric_limits<double>::max();
	int center_offers(0), factory_offers(0);
	std::vector<model::tile> center_colors = game->get_center_colors();
	// all center to pattern line moves
	for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
	{
		for (auto&& color : center_colors)
		{
			if (game->can_add_to_pattern_line(player_index, pattern_line_index, color))
			{
				auto&& move = std::make_unique<control::center_offer>(player_index, pattern_line_index, color);
				if (alpha_beta_move(controller, std::move(move), best_score, depth, player_index, alpha, beta))
				{
					return best_score;
				}
				center_offers++;
			}
		}
	}
	for (int factory_index = 0; factory_index < game->factory_count(); ++factory_index)
	{
		std::vector<model::tile> factory_colors = game->get_factory_colors(factory_index);
		//all factory to pattern line moves
		for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
		{
			for (auto&& color : factory_colors)
			{
				if (game->can_add_to_pattern_line(player_index, pattern_line_index, color))
				{
					auto&& move = std::make_unique<control::factory_offer>(factory_index, player_index, pattern_line_index, color);
					if (alpha_beta_move(controller, std::move(move), best_score, depth, player_index, alpha, beta))
					{
						return best_score;
					}
					factory_offers++;
				}
			}
		}
	}
	if (center_offers + factory_offers == 0)
	{
		// all factory to floor moves
		for (int factory_index = 0; factory_index < game->factory_count(); ++factory_index)
		{
			std::vector<model::tile> factory_colors = game->get_factory_colors(factory_index);
			for (auto&& color : factory_colors)
			{
				auto&& move = std::make_unique<control::drop_factory>(factory_index, player_index, color);
				if (alpha_beta_move(controller, std::move(move), best_score, depth, player_index, alpha, beta))
				{
					return best_score;
				}
			}
		}
		// all center to floor moves
		for (auto&& color : center_colors)
		{
			auto&& move = std::make_unique<control::drop_center>(player_index, color);
			if(alpha_beta_move(controller, std::move(move), best_score, depth, player_index, alpha, beta))
			{
				return best_score;
			}
		}
	}
	return best_score;
}

void ai::ad_ai::move()
{
    m_max_depth = 1;
	std::shared_ptr<control::game_controller> mockup = std::make_shared<control::game_controller>(*m_controller);
	minimax(m_board_index, 0, mockup, std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
	m_controller->add_command(std::move(m_best_move));
	m_controller->step();
}

const char* ai::ad_ai::get_name() const
{
	return "AD_AI";
}
