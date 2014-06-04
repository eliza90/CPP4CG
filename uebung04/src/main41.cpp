// main 4.1
//# include "controller/glut_engine.hpp"
//
//int main( int argc, char** argv )
//{
//  std::shared_ptr< ::controller::Engine > game_engine( new ::controller::GlutEngine );
//
//  game_engine->init( argc, argv );
//  game_engine->run();
//
//  return 0;
//}

# include "factory_map.hpp"
# include <iostream>
# include "controller/glut_engine.hpp"
# include "model/game.hpp"

int main(int argc, char** argv)
{
	// TODO 4.3: test factory and delegates here
	/*!!*///std::cerr << "main43: (PARTS ARE) UNIMPLEMENTED" << std::endl;
		
	//std::shared_ptr< ::model::Game > testgame(new ::model::Game());
	//testgame->addGameObject(std::shared_ptr<model::GameObject>(new model::TestGameObject(true, "TestGameObject")));
	
	std::shared_ptr< ::controller::Engine > game_engine(new ::controller::GlutEngine);
	
	game_engine->init( argc, argv );
	game_engine->run();
	return 0;
}


//main 4.4
//# include "flappy_box/controller/flappy_engine.hpp"
//
//int main(int argc, char** argv)
//{
//	std::shared_ptr< ::controller::Engine > game_engine(new ::flappy_box::controller::FlappyEngine);
//
//	game_engine->init(argc, argv);
//	game_engine->run();
//
//	return 0;
//}