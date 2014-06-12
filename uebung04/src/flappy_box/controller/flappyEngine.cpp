# include "flappy_box/controller/flappyEngine.hpp"
# include "flappy_box/controller/boxObjectLogic.hpp"

using namespace controller;

void FlappyEngine::init(int& argc, char** argv){	
	//initialisierung der Basisklasse
	GlutEngine::init(argc,argv);
	
	//alutInit -> soundbibliothek initialisieren
	model::Box myBox = model::Box();
	//Spielobj erzeugen 
	std::shared_ptr<::model::GameObject> myBox_ptr = std::make_shared<model::GameObject>(myBox);

	std::shared_ptr<model::Box> box_ptr = std::make_shared<model::Box>(myBox);
	controller::BoxObjectLogic logic = controller::BoxObjectLogic(box_ptr);
	view::BoxDrawable drawable = view::BoxDrawable(box_ptr);
	view::BoxAudible audible = view::BoxAudible(box_ptr);

	//und dem Model hinzufügen
	game_model()->addGameObject(myBox_ptr);

	//controller::BoxObjectLogic logic = controller::BoxObjectLogic(myBox_ptr);

	//Delegierten der Komponenten bei den Factories registrieren
	//logikObject?
	//controller::Logic::logic_factory().register_module<myBox_ptr>(//model::Box>(
	//	[](const std::shared_ptr <model::Box>& _l){ return std::make_shared<controller::BoxObjectLogic>(_l);}
	//);

	//view::GlRenderer::drawable_factory().register_module<myBox_ptr>(
	//	[](const std::shared_ptr <model::Box>& _l){ return std::make_shared<view::BoxDrawable>(_l); }
	//);

	//view::AlRenderer::audible_factory().register_module<myBox_ptr>(
	//	[](const std::shared_ptr <model::TestGameObject>& _l){ return std::make_shared<view::BoxAudible>(_l); }
	//);
}

void FlappyEngine::run(){
	//create window
	//std::shared_ptr< view::GlutWindow > window(new view::GlutWindow("Flappy Box", 500, 500, ptr_glRenderer, controller::InputEventHandler::keyboard_event()));
	//base engine run
	GlutEngine::run();
	//alutExit();
}

