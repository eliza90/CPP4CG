# pragma once

#include "math.hpp"
# include "model/game_object.hpp"

namespace model {

	class Box: public GameObject{

	  vec3_type position;//Vektor für Position[m]
	  vec3_type velocity;//Geschwindigkeit [m / s] 
	  vec3_type acceleration;//Beschleunigung[m / s²] 
	  double degree;// Winkel[deg] 
  public:
	  Box();
	  //inline getter
	  vec3_type getPosition(){ return position; }
	  vec3_type getVelocity(){ return velocity; }
	  vec3_type getAcceleration(){ return acceleration; }
	  double getDegree(){ return degree; }

	  //setter
	  void setPosition(vec3_type pos);
	  void setPosition(double x, double y, double z);
	  void setVelocity(double vx, double vy, double vz);
	  void setAcceleration(double ax, double ay, double az);
	  void setDegree(double d);

  }; // Box

} // model::
