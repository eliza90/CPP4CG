# include "flappy_box/controller/paddle_logic.hpp"
# include <AL/alut.h>
# include <thread>
# include <GL/freeglut.h>

using namespace ::flappy_box::controller;

PaddleLogic::PaddleLogic(const std::shared_ptr< flappy_box::model::Paddle>& p)
: ::controller::Logic::ObjectLogic()
, _model( p )
{}

//TO DO: complete method
bool PaddleLogic::advance(::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev){		

	double timestep_sec = l.game_model()->timestep().count();//deltaT

	//Sondertasten gedrückt - was dann?
	
	//links
	if (ev.key == 'a' || GetAsyncKeyState(VK_LEFT) != 0){
		_model->setPlayerControl(-1);		
	}	
	//rechts
	else if (ev.key == 'd' || GetAsyncKeyState(VK_RIGHT) != 0){
		_model->setPlayerControl(1);
	}
	else{
		_model->setPlayerControl(0);
	}
				
	//Bewegungsberechnung
	vec3_type p_alt = _model->position();
	vec3_type v_alt = _model->velocity()*0.8;
	vec3_type a_neu = vec3_type(_model->getPlayerControl() * 1000, 0, 0);
	//dv = a_neu*dt
	vec3_type dv = a_neu * timestep_sec;
	//v_neu = v_alt + dv
	vec3_type v_neu = v_alt+ dv;
	if (v_neu[0] > 100) v_neu[0] = 100;
	//dp=v_neu*dt
	vec3_type dp = a_neu*timestep_sec;
	//pneu = palt + dp
	vec3_type p_neu = p_alt + dp;

	//überprüfen der position
	//Fall x
	if (abs(p_neu[0]) >= _model->maxPosition()[0]){
		if (p_neu[0] <= -(_model->maxPosition()[0])) {
			p_neu[0] = -_model->maxPosition()[0];
		}
		else{
			p_neu[0] = _model->maxPosition()[0];
		}
	}
	
	//neue Werte setzen
	_model->setVelocity(v_neu);
	_model->setPosition(p_neu);
	_model->setAcceleration(a_neu);

	return true;
}