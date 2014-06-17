# include "flappy_box/view/boxDrawable.hpp"

using namespace view;

void BoxDrawable::visualize(GlRenderer& r, GlutWindow& w){

	//std::cout << "Test Image." << std::endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, -7.0, 0.0, /* hier stehe ich */
		0.0, 0.0, 0.0,  /* hier schaue ich hin */
		0.0, 0.0, 0.1);  /* dieser Vektor zeigt senkrecht nach oben */
		
	vec3_type position = l->getPosition();	

	//// Animation StartZeit = Konstruktor-Aufruf (Erstellung Klasse)
	glRotated(//multiplies the current matrix by a rotation matrix.
		l->getDegree(),
		0.0, 0.0, 1.0);//x,y,z coordinate of a vector

	l->setDegree(std::chrono::duration_cast<std::chrono::duration<double>>(r.game_model()->timestamp() - start).count() * 72);//neuer Winkel
	
	glTranslated(0.0, 0.0, position[2]);
	
	glBegin(GL_LINES);                                  // Draw A Quad 
	glColor3f(0.75f, 0.75f, 0.75f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();	
}
