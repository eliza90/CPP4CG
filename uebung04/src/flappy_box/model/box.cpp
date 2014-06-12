# include "flappy_box/model/box.hpp"

using namespace model;

Box::Box() : GameObject(true, "Box"){
	this->position = vec3_type(NULL,NULL,NULL);
	this->velocity = vec3_type(NULL, NULL, NULL);
	this->acceleration = vec3_type(NULL, NULL, NULL);
	this->degree = NULL;
}
