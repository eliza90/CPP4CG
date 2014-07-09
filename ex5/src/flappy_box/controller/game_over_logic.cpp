# include "flappy_box/controller/game_over_logic.hpp"
# include <AL/alut.h>
# include <thread>
# include <GL/freeglut.h>

using namespace ::flappy_box::controller;

GameOverLogic::GameOverLogic(const std::shared_ptr< flappy_box::model::GameOver>& p)
: ::controller::Logic::ObjectLogic()
, _model( p )
{}

//TO DO: complete method
bool GameOverLogic::advance(::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev){		
	return false;
}