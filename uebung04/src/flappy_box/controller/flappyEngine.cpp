# include "flappy_box/controller/flappyEngine.hpp"
# include "flappy_box/controller/boxObjectLogic.hpp"

using namespace controller;

void FlappyEngine::init(int& argc, char** argv){			
	//initialisierung der Basisklasse
	GlutEngine::init(argc, argv);

	// Init openAL
	alutInit(&argc, argv);

	std::shared_ptr<model::Box> box_ptr = std::make_shared<model::Box>(model::Box());
	//Komponenten MVC
	controller::BoxObjectLogic logic = controller::BoxObjectLogic(box_ptr);
	view::BoxDrawable drawable = view::BoxDrawable(box_ptr);
	view::BoxAudible audible = view::BoxAudible(box_ptr);
	//Spielobj erzeugen 
	std::shared_ptr<::model::GameObject> myBox_ptr = std::make_shared<model::GameObject>(box_ptr);
	
	//GL Renderer
	ptr_glRenderer = std::make_shared<view::GlRenderer>(view::GlRenderer(game_model()));
	//AL Renderer
	ptr_AlRenderer = std::make_shared<view::AlRenderer>(view::AlRenderer(game_model()));

	//und dem Model hinzufügen
	game_model()->addGameObject(box_ptr);

	game_logic()->logic_factory().register_module<model::Box>(
		[](const std::shared_ptr <model::Box>& _l){ return std::make_shared<controller::BoxObjectLogic>(_l); }
	);
	ptr_glRenderer->drawable_factory().register_module<model::Box>(
		[](const std::shared_ptr <model::Box>& _l){ return std::make_shared<view::BoxDrawable>(_l); }
	);
	ptr_AlRenderer->audible_factory().register_module<model::Box>(
		[](const std::shared_ptr <model::Box>& _l){ return std::make_shared<view::BoxAudible>(_l); }
	);
}

void FlappyEngine::run(){
	//create window		
	std::shared_ptr < ::controller::Engine > self = controller::FlappyEngine::shared_from_this();
	//std::shared_ptr< view::GlutWindow > window(new view::GlutWindow("Flappy Box", 500, 500, ptr_glRenderer, self));
	window = std::make_shared<view::GlutWindow>("Flappy Box", 500, 500, ptr_glRenderer, self);
	//window = new view::GlutWindow("Flappy Box", 500, 500, ptr_glRenderer, self);
	//base engine run
	GlutEngine::run();	
	alutExit();
}

void FlappyEngine::step(InputEventHandler::keyboard_event const& ev){
	game_logic()->advance_model(ev);
	ptr_AlRenderer->auralize_model();
	ptr_glRenderer->visualize_model(*window);
}

