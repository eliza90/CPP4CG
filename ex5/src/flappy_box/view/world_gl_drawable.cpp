# include "flappy_box/view/world_gl_drawable.hpp"

#include <GL/freeglut.h>

# include <algorithm>

using namespace ::flappy_box::view;


WorldGlDrawable::WorldGlDrawable(const std::shared_ptr< ::flappy_box::model::World >& b)
: _model( b )
{
	
	
	

}

WorldGlDrawable::~WorldGlDrawable()
{


}

void WorldGlDrawable::visualize(::view::GlRenderer& r, ::view::GlutWindow& w)
{
	


	// TODO: Replace old rendering code with new and improved rendering - Aufgabe 5.3

	//Tiefeneindruck/ Nebel
	glEnable(GL_FOG);

	float FogCol[3] = { 0.8f, 0.8f, 0.8f }; // Define a nice light grey
	glFogfv(GL_FOG_COLOR, FogCol);     // Set the fog color

	glFogi(GL_FOG_MODE, GL_LINEAR); // Note the 'i' after glFog - the GL_LINEAR constant is an integer.
	glFogf(GL_FOG_START, 0.f);
	glFogf(GL_FOG_END, 500.f);


	// Beleuchtung
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);*/

	//GLfloat light_pos[] = { 1.0, 1.0, 1.0, 1.0 };
	//float light_color[] = { 1.0, 1.0, 1.0, 1.0 };

	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);

	//glDisable(GL_LIGHTING);
	//glDisable(GL_LIGHT0);
	//glDisable(GL_COLOR_MATERIAL);
	//glDisable(GL_NORMALIZE);

	
	//Textausgabe
	// Ausgabe für die Punktanzahl
	char text_p[32];
	sprintf(text_p, "Punkte: %d", _model->getPlayerPoints());
	glColor3f(2, 0.5, 0.5);
	glRasterPos3f(-90, 20, 40);
	for (const char* c = text_p; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

	// Ausgabe für die Anzahl der Leben
	char text_l[32];
	sprintf(text_l, "Leben: %d", _model->_getRemainingLives());
	glColor3f(2, 0.5, 0.5);
	glRasterPos3f(-90, 20, 30);
	for (int i = 0; text_l[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text_l[i]);
}

