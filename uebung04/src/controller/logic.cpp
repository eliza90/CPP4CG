# include "controller/logic.hpp"
# include "flappy_box/model/box.hpp"
# include "flappy_box/controller/boxObjectLogic.hpp"

using namespace ::controller;

Logic::Logic( const std::shared_ptr< ::model::Game >& g ) : _model( g ) {
	logic_factory().register_module<model::Box>(
		[](const std::shared_ptr <model::Box>& _l){ return std::make_shared<controller::BoxObjectLogic>(_l); }
	);
}

bool Logic::advance_model( const ::controller::InputEventHandler::keyboard_event& ev )
{	
  // TODO 4.3: set current timestamp in model and call delegates
  /*!!*///std::cerr << "!! controller::Logic::advance_model: (PARTS ARE) UNIMPLEMENTED." << std::endl; 
	game_model()->setTimestamp(std::chrono::steady_clock::now()); //setTimestamp
	//43 Variante 1 Delegates jedes Mal erstellen
	/*struct LogicDelegate : public controller::Logic::ObjectLogic{
		LogicDelegate(const std::shared_ptr<::model::TestGameObject> _l) : l(_l){}
		virtual bool advance(Logic&, InputEventHandler::keyboard_event const&){
			std::cout << "controller::ObjectLogic::advance: Test Thinking!" << std::endl;
			return true;
		}
		std::shared_ptr<model::TestGameObject> l;
	};
	
	_obj_logic_factory.register_module<model::TestGameObject>(
		[](const std::shared_ptr <model::TestGameObject>& _l){ return std::make_shared<LogicDelegate>(_l); }
	);

	std::vector<std::shared_ptr< model::GameObject>> myObjects(game_model()->objects());

	for (auto o : myObjects)
		_obj_logic_factory.create_for(o)->advance(*this, ev);*/

	//43 Flappy Box Variante 2(get/setData)
	std::vector<std::shared_ptr<model::GameObject>> myObjects(game_model()->objects());//vektor mit den game objekten

	for (auto o : myObjects){
		
		auto logicDelegate(o->getData<controller::Logic::ObjectLogic>());
		
		if (logicDelegate == nullptr){
			o->registerData(logic_factory().create_for(o));//delegate aus der factorymap
		}
		auto logic(o->getData<controller::Logic::ObjectLogic>());
		logic->advance(*this, ev);
	}

	return false;	
}
