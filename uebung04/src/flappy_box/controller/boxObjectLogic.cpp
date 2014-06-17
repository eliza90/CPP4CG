# include "flappy_box/controller/boxObjectLogic.hpp"

using namespace controller;

bool BoxObjectLogic::advance(Logic& logic, controller::InputEventHandler::keyboard_event const& key_event){
	//Dazu müssen wir die im Spielobjekt gespeicherte Position und Geschwindigkeit entsprechend
	//	der Newtonschen Bewegungsgleichung (f=ma) aktualisieren.
	//Die Masse des Spielobjektes kann 1[kg] gleichgesetzt werden.
	//Verfahren um die Bewegungsgleichung zu integrieren -Euler Verfahren
	//Nutzten sie bei der Umsetzung den von model::Game::timestep bereitgestellten Zeitschritt.
	//std::cout << "!! controller::Logic::advance_model: Test Thinking." << std::endl;

	std::cout << "Test Thinking " << std::endl;

	vec3_type a = l->getAcceleration();
	vec3_type v = l->getVelocity();
	vec3_type position = l->getPosition();
	
	//printlns
	//std::cout << "a: " << a[0] << "  " << a[1] << "  " << a[2] << std::endl;
	//std::cout << "v: " << v[0] << "  " << v[1] << "  " << v[2] << std::endl;
	//std::cout << "position: " << position[0] << "  " << position[1] << "  " << position[2] << std::endl;
	
	double deltaT = logic.game_model()->timestep().count();
	//std::cout << "DeltaT: " << deltaT << std::endl;

	//exponentieller Zerfall der Beschleunigung	
	double constantDecay = 0.08*exp(deltaT);
	a = a * constantDecay;
	//std::cout << "a: " << a[0] << "  " << a[1] << "  " << a[2] << std::endl;
		
	double aIn = a[2];
	//std::cout << "a[2]" << a[2] << std::endl;
	if (key_event.key == 'w'){
		aIn = 20;
	}
	a[2] = aIn;

	//gewicht gar nicht berücksichtigt?!
	//a = konst Gravitationskomponente (in negativer Richtung auf der z - Achse) + benutzerdefinierten Beschleunigung
    l->setAcceleration(0.0, 0.0, a[2] - 9.81);
	//vneu = valt + a *deltaT
	l->setVelocity(0.0, 0.0, v[2] + aIn * deltaT);

	position[2] = position[2] + v[2] *deltaT;

	l->setPosition(position);
	return true;
}

