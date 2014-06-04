# include "controller/logic.hpp"

using namespace ::controller;

Logic::Logic( const std::shared_ptr< ::model::Game >& g ) : _model( g ) {
}

bool Logic::advance_model( const ::controller::InputEventHandler::keyboard_event& ev )
{
  // TODO 4.3: set current timestamp in model and call delegates
  /*!!*///std::cerr << "!! controller::Logic::advance_model: (PARTS ARE) UNIMPLEMENTED." << std::endl; 
	game_model()->setTimestamp(std::chrono::steady_clock::now()); //setTimestamp

	std::vector<std::shared_ptr<model::GameObject>> myObjects(game_model()->objects());//vektor mit den game objekten

	for (auto o : myObjects){
		
		auto logicDelegate(o->getData<controller::Logic::ObjectLogic>());
		
		if (logicDelegate == nullptr){
			o->registerData(_obj_logic_factory.create_for(o));//delegate aus der factorymap
		}
		logicDelegate->advance(*this, ev);	
	}
	
	return false;	
}
