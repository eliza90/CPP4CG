# include "flappy_box/controller/box_object_logic.hpp"
# include <AL/alut.h>
# include <thread>


# include <GL/freeglut.h>

using namespace ::flappy_box::controller;

BoxObjectLogic::BoxObjectLogic(const std::shared_ptr< flappy_box::model::Box >& b )
: ::controller::Logic::ObjectLogic()
, _model( b )
{}

//TO DO: complete method
bool BoxObjectLogic::advance( ::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev )
{
  double timestep_sec = l.game_model()->timestep().count();//deltaT

  vec3_type a_alt = _model->acceleration();  
  vec3_type v_alt = _model->velocity();
  vec3_type p_alt = _model->position();
  vec3_type f_ext = _model->externalForce();
  vec3_type a_grav(0, 0, -1.5);  

  //überprüfen der position
  //Fall x
  if (abs(p_alt[0]) >= _model->maxPosition()[0]){
	  if (p_alt[0] <= -_model->maxPosition()[0])  {
		  p_alt[0] = -_model->maxPosition()[0];
	  }
	  else{
		  p_alt[0] = _model->maxPosition()[0];
	  }
	  v_alt[0] = -v_alt[0];
	  //a_alt[0] = -a_alt[0] * 5;
  }
  //Fall z
  if (abs(p_alt[2]) >= _model->maxPosition()[2]){
	  if (p_alt[2] <= -_model->maxPosition()[2])  {
		  p_alt[2] = -_model->maxPosition()[2];
	  }
	  else{
		  p_alt[2] = _model->maxPosition()[2];
	  }
	  v_alt[2] = -v_alt[2];
	  //a_alt[2] = -a_alt[2];
  }

  double d(0.8);//dämpfung
  //masse des Würfels = Volumen der Box (Kantenlänge^3)
  //a_ext = f_ext/m  
  vec3_type a_ext = f_ext / (_model->getSize()*_model->getSize()*_model->getSize());
  //a_neu = a_alt*d + a_ext + a_grav
  vec3_type a_neu = a_alt*d + a_grav + a_ext;
  //dv=a_neu*dt
  vec3_type dv = a_neu*timestep_sec;
  //vneu = valt + dv
  vec3_type v_neu = v_alt + dv;
  //dp=v_neu*dt
  vec3_type dp = a_neu*timestep_sec;
  //pneu = palt + dp
  vec3_type p_neu = p_alt + dp;

  //überprüfen der position
  //Fall x
  if (abs(p_neu[0]) >= _model->maxPosition()[0]){
	  if (p_neu[0] <= -_model->maxPosition()[0])  {
		  p_neu[0] = -_model->maxPosition()[0];
	  }
	  else{
		  p_neu[0] = _model->maxPosition()[0];
	  }
	  v_neu[0] = -v_neu[0];
	  //a_alt[0] = -a_alt[0] * 5;
  }
  //Fall z
  if (abs(p_neu[2]) >= _model->maxPosition()[2]){
	  if (p_neu[2] <= -_model->maxPosition()[2])  {
		  p_neu[2] = -_model->maxPosition()[2];
	  }
	  else{
		  p_neu[2] = _model->maxPosition()[2];
	  }
	  v_neu[2] = -v_neu[2];
	  //a_alt[2] = -a_alt[2];
  }
   p_neu[1] = 0;
  
  //neue Werte setzen
  _model->setVelocity(v_neu);
  _model->setPosition(p_neu);
  _model->setAcceleration(a_neu);

  return true;
}