# include "flappy_box/model/box.hpp"

using namespace model;

Box::Box() : GameObject(true, "Box"){
	this->position = vec3_type(NULL, NULL, NULL);
	this->velocity = vec3_type(NULL, NULL, NULL);
	this->acceleration = vec3_type(NULL, NULL, NULL);
	this->degree = NULL;
}

void Box::setPosition(vec3_type pos){
	position = pos;
}

void Box::setPosition(double x, double y, double z){
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void Box::setVelocity(double vx, double vy, double vz){
	velocity[0] = vx; 
	velocity[1] = vy;
	velocity[2] = vz;
}

void Box::setAcceleration(double ax, double ay, double az){
	acceleration[0] = ax;
	acceleration[1] = ay;
	acceleration[2] = az;
}

void Box::setDegree(double d){
	degree = d; 
}
