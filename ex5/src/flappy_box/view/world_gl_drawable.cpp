# include "flappy_box/view/world_gl_drawable.hpp"

#include <GL/freeglut.h>

# include <algorithm>

using namespace ::flappy_box::view;


WorldGlDrawable::WorldGlDrawable(const std::shared_ptr< ::flappy_box::model::World >& b)
: _model( b )
{
	// allocate buffer
	wwidth = 128;
	wheight = 128;
	textureCoord = new unsigned char[(wwidth * wheight * 3)];

	//// open texture data
	//wFile = fopen("../../res/theheader.raw", "rb");
	//if (wFile == NULL){
	//	std::cout << "No Texture found!" << std::endl;
	//}
	//else {
	//	std::cout << "Texture found!" << std::endl;
	//	// read texture data
	//	fread(textureCoord, wwidth * wheight * 3, 1, wFile);
	//	fclose(wFile);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, wwidth, wheight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureCoord);
	//}

	//glGenTextures(1, &worldTexture); // allocate a texture name
	//glBindTexture(GL_TEXTURE_2D, worldTexture); // select our current texture
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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

	
	

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);


	glPopMatrix(); {
		//rechts
		glDisable(GL_DEPTH_TEST);
		//glEnable(GL_DEPTH_TEST);
		//Hintergrund
		//glEnable(GL_TEXTURE_2D); {
		//glBindTexture(GL_TEXTURE_2D, worldTexture);
		glColor3d(0.25, 0.25, 2.0);

		glBegin(GL_QUADS);
		glVertex3d(_model->getWorldHalfWidth(), -50, _model->getWorldHalfHeight());
		glColor3d(1.95, 0.25, 1.25);
		glVertex3d(_model->getWorldHalfWidth(), 300, _model->getWorldHalfHeight());
		glVertex3d(_model->getWorldHalfWidth(), 300, -_model->getWorldHalfHeight());
		glColor3d(0.25, 0.25, 2.0);
		glVertex3d(_model->getWorldHalfWidth(), -50, -_model->getWorldHalfHeight());
		glEnd();

		//links
		/*glColor3d(0.95, 0.25, 0.25);*/

		glBegin(GL_QUADS);
		glVertex3d(-_model->getWorldHalfWidth(), -50, _model->getWorldHalfHeight());
		glColor3d(1.95, 0.25, 1.25);
		glVertex3d(-_model->getWorldHalfWidth(), 300, _model->getWorldHalfHeight());
		glVertex3d(-_model->getWorldHalfWidth(), 300, -_model->getWorldHalfHeight());
		glColor3d(0.25, 0.25, 2.0);
		glVertex3d(-_model->getWorldHalfWidth(), -50, -_model->getWorldHalfHeight());
		glEnd();

		//hinten
		//glColor3d(0.95, 0.25, 0.25);
		glColor3d(1.95, 0.25, 1.25);
		glBegin(GL_QUADS);
		glVertex3d(-_model->getWorldHalfWidth(), 300, -_model->getWorldHalfHeight());
		glVertex3d(_model->getWorldHalfWidth(), 300, -_model->getWorldHalfHeight());
		glVertex3d(_model->getWorldHalfWidth(), 300, _model->getWorldHalfHeight());
		glVertex3d(-_model->getWorldHalfWidth(), 300, _model->getWorldHalfHeight());
		glEnd();
		glColor3d(0.25, 0.25, 2.0);
		//oben
		//glColor3d(0.95, 0.25, 0.25);
		glBegin(GL_QUADS);
		glVertex3d(-_model->getWorldHalfWidth(), -50, _model->getWorldHalfHeight());
		glVertex3d(_model->getWorldHalfWidth(), -50, _model->getWorldHalfHeight());
		glColor3d(1.95, 0.25, 1.25);
		glVertex3d(_model->getWorldHalfWidth(), 300, _model->getWorldHalfHeight());
		glVertex3d(-_model->getWorldHalfWidth(), 300, _model->getWorldHalfHeight());
		glEnd();

		//unten
		glColor3d(1.95, 0.25, 1.25);
		glBegin(GL_QUADS);
		glVertex3d(-_model->getWorldHalfWidth(), 300, -_model->getWorldHalfHeight());
		glVertex3d(_model->getWorldHalfWidth(), 300, -_model->getWorldHalfHeight());
		glColor3d(0.25, 0.25, 2.0);
		glVertex3d(_model->getWorldHalfWidth(), -50, -_model->getWorldHalfHeight());
		glVertex3d(-_model->getWorldHalfWidth(), -50, -_model->getWorldHalfHeight());
		glEnd();
		//}glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	}glPushMatrix();
	//Textausgabe
	// Ausgabe für die Punktanzahl
	glEnable(GL_DEPTH_TEST);
	char text_p[32];
	sprintf(text_p, "Punkte: %d", _model->getPlayerPoints());
	glColor3f(2, 0.5, 0.5);
	glRasterPos3f(-30, -50, -10);
	for (const char* c = text_p; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

	// Ausgabe für die Anzahl der Leben
	char text_l[32];
	sprintf(text_l, "Leben: %d", _model->_getRemainingLives());
	glColor3f(2, 0.5, 0.5);
	glRasterPos3f(-30, -50, -13);
	for (int i = 0; text_l[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text_l[i]);
}

