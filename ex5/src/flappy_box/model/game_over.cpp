# include "flappy_box/model/game_over.hpp"

using namespace flappy_box::model;

GameOver::GameOver(const std::string& s, const int points)
	: GameObject(true, s)
	, _playerPoints(points)
{

}