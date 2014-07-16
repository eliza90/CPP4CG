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
	glColor3f(2, 0.5, 0.5);
	glRasterPos3f(0, 20, 0);	
	for (const char* c = text_p; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	
	// Ausgabe für den Hinweis
	char text_r[32];
	sprintf(text_r, "To Restart Press 'R' ");
	glColor3f(2, 0.5, 0.5);
	glRasterPos3f(0, 0, 0);
	for (const char* c = text_r; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);	
}

