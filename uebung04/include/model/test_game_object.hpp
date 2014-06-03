# pragma once
# include "model/game_object.hpp"

namespace model{

	class TestGameObject : public GameObject{

	public:
		// @ true: dynamic flag can be used to mark object as static/dynamic in the game.
		TestGameObject(const bool dynamic_flag, const std::string& name) : GameObject(dynamic_flag, name){}

	};//TestGameObject

}//model