# include "flappy_box/view/boxDrawable.hpp"

using namespace view;

void BoxDrawable::visualize(GlRenderer& r, GlutWindow& w){
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Projektionsmatrix einstellen
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(angle, w/h ,near clipping, far clipping)
	gluPerspective(30.0, static_cast<double>(w.width()) / static_cast<double>(w.height()), 2.0, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, -7.0, 0.0, /* hier stehe ich */
		0.0, 0.0, 0.0,  /* hier schaue ich hin */
		0.0, 0.0, 0.1);  /* dieser Vektor zeigt senkrecht nach oben */

	vec3_type position = l->getPosition();
	double degree = l->getDegree();

	// Animation StartZeit = Konstruktor-Aufruf (Erstellung Klasse)
	glRotated(//multiplies the current matrix by a rotation matrix.
		std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now().time_since_epoch()).count()* 72.0,//angle of rotation in degrees
		0.0, 0.0, position[2]);//x,y,z coordinate of a vector

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
