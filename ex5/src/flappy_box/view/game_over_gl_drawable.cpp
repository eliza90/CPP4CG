# include "flappy_box/view/game_over_gl_drawable.hpp"

#include <GL/freeglut.h>

# include <algorithm>

using namespace ::flappy_box::view;


GameOverGlDrawable::GameOverGlDrawable(const std::shared_ptr< ::flappy_box::model::GameOver >& b)
: _model( b )
{
  
}

GameOverGlDrawable::~GameOverGlDrawable()
{


}

void GameOverGlDrawable::visualize(::view::GlRenderer& r, ::view::GlutWindow& w)
{
	//Textausgabe
	// Ausgabe für die erreichte Punkzahl
	char text_p[64];
	sprintf(text_p, "GAME OVER - Erreichte Punkte: %d", _model->getPlayerPoints());
	glColor3f(0, 0, 0);
	glRasterPos3f(-20, 0, 0);	
	for (const char* c = text_p; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	
	// Ausgabe für den Hinweis
	char text_r[32];
	sprintf(text_r, "To Restart Press 'R' ");
	glColor3f(0, 0, 0);
	glRasterPos3f(-20, 0, -10);
	for (const char* c = text_r; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);


	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	
	glPopMatrix(); {
		//rechts
		glEnable(GL_DEPTH_TEST);
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
	}glPushMatrix();

}

