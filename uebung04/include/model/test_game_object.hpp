# pragma once
# include "model/game_object.hpp"
# include "controller/logic.hpp"

namespace model{

	class TestGameObject : public GameObject{

	public:
		// @ true: dynamic flag can be used to mark object as static/dynamic in the game.
		TestGameObject(const bool dynamic_flag, const std::string& name) : GameObject(dynamic_flag, name){
			/*struct LogicDelegate : public controller::Logic::ObjectLogic{
				LogicDelegate(const std::shared_ptr<::model::TestGameObject> _l) : l(_l){}
				bool advance(Logic&, controller::InputEventHandler::keyboard_event const&){
					std::cout << "controller::Logic::advance: Test Thinking!\n" << std::endl;
					return true;
				}
				std::shared_ptr<model::TestGameObject> l;
			};

			Logic::logic_factory().register_module<this>(
				[](const std::shared_ptr <model::TestGameObject>& _l){ return std::make_shared<LogicDelegate>(_l); }
			);*/
		}
	};//TestGameObject

}//model