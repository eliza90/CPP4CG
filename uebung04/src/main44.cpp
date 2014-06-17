//# include "factory_map.hpp"
//# include <iostream>
//# include "controller/glut_engine.hpp"
//# include "model/game.hpp"
//
//int main(int argc, char** argv)
//{
//	// TODO 4.3: test factory and delegates here
//	/*!!*///std::cerr << "main43: (PARTS ARE) UNIMPLEMENTED" << std::endl;	
//	std::shared_ptr< ::controller::Engine > game_engine(new ::controller::GlutEngine);
//
//	game_engine->init(argc, argv);
//	game_engine->run();
//	return 0;
//}

#include <memory>
#include "flappy_box/controller/flappyEngine.hpp"

int main( int argc, char** argv ){
  std::shared_ptr< ::controller::Engine > game_engine( new controller::FlappyEngine );

  game_engine->init( argc, argv );
  game_engine->run();

  return 0;
}
