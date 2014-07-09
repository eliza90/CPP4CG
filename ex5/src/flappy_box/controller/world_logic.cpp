# include "flappy_box/controller/world_logic.hpp"
# include <AL/alut.h>
# include <thread>
# include <GL/freeglut.h>
#include<random>

using namespace ::flappy_box::controller;

WorldLogic::WorldLogic(const std::shared_ptr< flappy_box::model::World >& b)
: ::controller::Logic::ObjectLogic()
, _model( b )
, _shallRestartTheGame(true)
, _timeframe_count(0){
}

//TO DO: complete method
bool WorldLogic::advance(::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev){

	if (_shallRestartTheGame){
		restartGame(l);
		_shallRestartTheGame = false;
	}

	//jede Sekunde eine Box hinzufügen
	static double timeframe = 3;
	if (_timeframe_count == 0){
		clock_begin = std::chrono::steady_clock::now();
		_timeframe_count = 1;
	}
	else{
		std::chrono::steady_clock::time_point clock_end = std::chrono::steady_clock::now();
		std::chrono::steady_clock::duration time_span = clock_end - clock_begin;
		double nseconds = double(time_span.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;

		if (nseconds >= timeframe){
			addBoxToGame(l);
			_timeframe_count = 0;
		}
	}

	//Spielerpunktelogik

	//Punkte inkrementieren
	int newPoints = _model->getPlayerPoints() + 1;
	_model->setPlayerPoints(newPoints);

	if (_model->_getRemainingLives() == 0){
		_model->setAlive(false);
		l.game_model()->addGameObject(std::shared_ptr<::model::GameObject>(new ::flappy_box::model::GameOver("GameOverObject", _model->getPlayerPoints())));
	}

	std::vector<std::shared_ptr<::model::GameObject>> myObjects(l.game_model()->objects());

	std::shared_ptr<::flappy_box::model::Paddle> _mypaddle;
	std::shared_ptr<::flappy_box::model::Box> _mybox;
	
	for (auto o : myObjects){
		std::vector<std::shared_ptr<::model::GameObject>>::iterator paddle = std::find_if(myObjects.begin(), myObjects.end(), [](std::shared_ptr<::model::GameObject> o)->bool{return o->name() == "Paddle"; });
		if (paddle != myObjects.end()) {
			// found it
			std::shared_ptr<::model::GameObject> obj = std::make_shared<::model::GameObject>(*paddle);
			_mypaddle = std::dynamic_pointer_cast<::flappy_box::model::Paddle>(*paddle);
		}
		else {
			//std::cout << "myObjects does not contain: Paddle " << '\n';// doesn't exist
		}

		//Interaktionslogik
		if (_mypaddle != nullptr && _mybox != nullptr){
			setForce(_mybox, _mypaddle);
			if (_mybox->position()[2] <= _mypaddle->position()[2]){
				/*std::cout << "box" << _mybox->position()[2] << '\n';
				std::cout << _mypaddle->position()[2] << '\n';*/
				_mybox->setAlive(false);
				int lives = _model->_getRemainingLives() - 1;
				_model->setRemainingLives(lives);
			}
		}

		std::vector<std::shared_ptr<::model::GameObject>>::iterator box = std::find_if(myObjects.begin(), myObjects.end(), [](std::shared_ptr<::model::GameObject> o)->bool{return o->name() == "Box"; });
		if (box != myObjects.end()) {
			// found it
			_mybox = std::dynamic_pointer_cast<::flappy_box::model::Box>(*box);
			//Kollisionstests
			for (auto o : myObjects){
				std::shared_ptr<::flappy_box::model::Box> _secondbox;
				std::vector<std::shared_ptr<::model::GameObject>>::iterator secondbox = std::find_if(box, myObjects.end(), [](std::shared_ptr<::model::GameObject> o)->bool{return o->name() == "Box"; });
				_secondbox = std::dynamic_pointer_cast<::flappy_box::model::Box>(*secondbox);
				
				while (secondbox != myObjects.end()){

				if (!_mybox->equals(*_secondbox)){//in Box definiert - gleiches Objekt -> gleiche Position
					if (_mybox->isAlive() && _secondbox->isAlive()){
						//kollision über umhüllende Kugeln							
						double positionZ = _mybox->position()[2] - _secondbox->position()[2];
						double positionX = _mybox->position()[0] - _secondbox->position()[0];
						//(pos1-pos2)^2 < (r1+r2)^2
						if (positionX < (_mybox->getSize() + _secondbox->getSize())*(_mybox->getSize() + _secondbox->getSize()) && positionZ < (_mybox->getSize() + _secondbox->getSize())*(_mybox->getSize() + _secondbox->getSize())){
							std::cout << "collision" << '\n';
						}
					}
				}
				++secondbox;//iterator inkrementieren - begin ändern
				secondbox = std::find_if(secondbox, myObjects.end(), [](std::shared_ptr<::model::GameObject> o)->bool{return o->name() == "Box"; });
				}
			}
		}
		else{
			//std::cout << no box << '\n';
		}
	}
	
  return true;
}

//Hilfsmethoden
void WorldLogic::addBoxToGame(::controller::Logic& l){
	auto seed = ::std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 engine(seed); // MersennetwisterMT19937
	std::normal_distribution<double> dist1(-_model->getWorldHalfWidth(), _model->getWorldHalfWidth());
	double x = dist1(engine); 
	//std::cout << x << '\n';
	std::normal_distribution<double> dist2(1.0, _model->getWorldHalfWidth() / 14);
	double size = abs(dist2(engine));	
	//std::cout << size  << '\n'; 
	
	std::shared_ptr< flappy_box::model::Box > b = std::make_shared< flappy_box::model::Box >("Box");
	b->setPosition(vec3_type(x, 0, _model->getWorldHalfHeight() / 2));
	b->setSize(size);
	b->setMaxPosition(vec3_type(_model->getWorldHalfWidth() - size* 0.5, 0, _model->getWorldHalfHeight()));	
	l.game_model()->addGameObject(b);
}

void WorldLogic::setForce(std::shared_ptr< flappy_box::model::Box > & box, std::shared_ptr< flappy_box::model::Paddle > & paddle){
	//Fall1 - Box oberhalb des Paddles
	if ((box->position()[0] > (paddle->position()[0] - paddle->getSize()[0] * (-0.5))) && (box->position()[0] < (paddle->position()[0] + paddle->getSize()[0] * (0.5)))){
		//skalierungsterm
		double s = 10* box->getSize() * box->getSize();
		box->setExternalForce(vec3_type(0,0,s));
	}
	//Fall2 -Box  oberhalb des Paddles, nicht mehr über der Fläche - links bzw. rechts davon
	else{
		//linke Paddle Ecke
		if (box->position()[0] < paddle->position()[0]){//linke Ecke
			vec3_type pe = vec3_type(paddle->position()[0] - (paddle->getSize()[0] * 0.5),
									 paddle->position()[1], 
									 paddle->position()[2] + (paddle->getSize()[2] * 0.5));
			//vektor Kiste - Ecke 
			vec3_type f = pe - box->position();
			//normalisieren
			f = f / (sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]));
			//skalar f paddle normale (0,0,-1)
			double scalar = -f[2];
			double s = 10 * box->getSize() * box->getSize();
			//box->setExternalForce(vec3_type(0, 0, s));

		}
		else{//rechte Ecke
			vec3_type pe = vec3_type(paddle->position()[0] + (paddle->getSize()[0] * 0.5),
									 paddle->position()[1],
									 paddle->position()[2] + (paddle->getSize()[2] * (0.5)));
		}		
	}
}

void WorldLogic::restartGame(::controller::Logic& l){
	// invalidate all game objects
	for (auto o : l.game_model()->objects()){
		o->setAlive(false);
	}
	// reject invalidation for world object
	_model->setAlive(true);
	_model->setPlayerPoints(0);
	_model->setRemainingLives(5);
	// create and configure new paddle object
	std::shared_ptr< flappy_box::model::Paddle > user_paddle = std::make_shared< flappy_box::model::Paddle >("Paddle");
	user_paddle->size(vec3_type(10.0, 1.0, 2.5));
	user_paddle->setPosition(vec3_type(0.0, 0.0, -_model->getWorldHalfHeight() + user_paddle->getSize()[2] * 2.0));
	user_paddle->setMaxPosition(vec3_type(_model->getWorldHalfWidth() - user_paddle->getSize()[0] * 0.5, 0.0, _model->getWorldHalfHeight()));
	// add paddle object
	l.game_model()->addGameObject(user_paddle);
	// unset restart flag
	_shallRestartTheGame = false;
}