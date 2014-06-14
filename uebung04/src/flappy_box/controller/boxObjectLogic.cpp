# include "flappy_box/controller/boxObjectLogic.hpp"

using namespace controller;

bool BoxObjectLogic::advance(Logic& logic, controller::InputEventHandler::keyboard_event const& key_event){
	//Dazu müssen wir die im Spielobjekt gespeicherte Position und Geschwindigkeit entsprechend
	//	der Newtonschen Bewegungsgleichung (f=ma) aktualisieren.
	//Die Masse des Spielobjektes kann 1[kg] gleichgesetzt werden.
	//Verfahren um die Bewegungsgleichung zu integrieren -Euler Verfahren
	//Nutzten sie bei der Umsetzung den von model::Game::timestep bereitgestellten Zeitschritt.
	
	vec3_type a = l->getAcceleration();
	vec3_type v = l->getVelocity();
	vec3_type position = l->getPosition();
	
	double deltaT = logic.game_model()->timestep().count();

	//exponentieller Zerfall der Beschleunigung	
	double constantDecay = 0.8;
	constantDecay = exp(deltaT);
	a = a * constantDecay;
		
	double aIn = 0;
	if (key_event.key == 'w'){
		aIn = 20;
	}

	//gewicht gar nicht berücksichtigt?!
	//a = konst Gravitationskomponente (in negativer Richtung auf der z - Achse) + benutzerdefinierten Beschleunigung
	a[2] = -9.81 + aIn;

	//muss das komponentenweise addieren für vec3_type noch definiert werden oder ist das dabei?
	l->setVelocity(v + a * deltaT);

	v = v + a * deltaT/2;
	position = position + v*deltaT;
	l->setPosition(position);

	return true;
}

