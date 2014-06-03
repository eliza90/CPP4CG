# include "controller/engine.hpp"

using namespace ::controller;

Engine::Engine( const std::shared_ptr< Logic >& l )
: _model( l->game_model() )
, _logic( l )
{}

std::shared_ptr< ::model::Game >& Engine::game_model()
{
  return _model;
}

std::shared_ptr< ::model::Game const > const Engine::game_model() const
{
  return _model;
}

std::shared_ptr< Logic >& Engine::game_logic()
{
  return _logic;
}

std::shared_ptr< Logic const > const Engine::game_logic() const
{
  return _logic;
}

void Engine::step( InputEventHandler::keyboard_event const& ev )
{
  game_logic()->advance_model( ev );
}

// Implements abstract class InputEventHandler. Simply calls function step providing the keyboard_event ev as an argument.
// Input events should be provided by some input-event-provider (e.g. GlutWindow).
// Override this function to change event distribution and processing.
bool Engine::handle(const keyboard_event& k){	
	try{
		step(k);
		return true;//erfolgreich
	}
	catch (std::exception _e){
		std::cerr << "!! controller::Engine::handle: some kind of error." << std::endl;
	}
	return false;
}
