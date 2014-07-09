# include "flappy_box/view/paddle_gl_drawable.hpp"

#include <GL/freeglut.h>

# include <algorithm>

using namespace ::flappy_box::view;


PaddleGlDrawable::PaddleGlDrawable(const std::shared_ptr<::flappy_box::model::Paddle>& b)
: _model( b ){
	//glGenBuffers(1, &handleVBO);
}

PaddleGlDrawable::~PaddleGlDrawable(){
	//glDeleteBuffers;
}

void PaddleGlDrawable::visualize(::view::GlRenderer& r, ::view::GlutWindow& w){
	glPushMatrix();
	{
	  double angle = 0;
	  const double size =3;
	  glTranslated(_model->position()[0], _model->position()[1], _model->position()[2]);
	  glRotated( angle, 0., 0., 0. );
	  glScaled( size, size, size );

	  glColor3d( 0.25, 0.25, 0.25 );
	  ::glBegin(GL_LINES);

	  ::glVertex3d(-0.5, -0.5, -0.5);
	  ::glVertex3d(-0.5, -0.5,  0.5);
	  ::glVertex3d(-0.5,  0.5, -0.5);
	  ::glVertex3d(-0.5,  0.5,  0.5);
	  ::glVertex3d( 0.5, -0.5, -0.5);
	  ::glVertex3d( 0.5, -0.5,  0.5);
	  ::glVertex3d( 0.5,  0.5, -0.5);
	  ::glVertex3d( 0.5,  0.5,  0.5);

	  ::glVertex3d(-0.5, -0.5, -0.5);
	  ::glVertex3d(-0.5,  0.5, -0.5);
	  ::glVertex3d( 0.5, -0.5, -0.5);
	  ::glVertex3d( 0.5,  0.5, -0.5);
	  ::glVertex3d(-0.5, -0.5,  0.5);
	  ::glVertex3d(-0.5,  0.5,  0.5);
	  ::glVertex3d( 0.5, -0.5,  0.5);
	  ::glVertex3d( 0.5,  0.5,  0.5);

	  ::glVertex3d(-0.5, -0.5, -0.5);
	  ::glVertex3d( 0.5, -0.5, -0.5);
	  ::glVertex3d(-0.5, -0.5,  0.5);
	  ::glVertex3d( 0.5, -0.5,  0.5);
	  ::glVertex3d(-0.5,  0.5, -0.5);
	  ::glVertex3d( 0.5,  0.5, -0.5);
	  ::glVertex3d(-0.5,  0.5,  0.5);
	  ::glVertex3d( 0.5,  0.5,  0.5);

	  ::glEnd();

	}
	glPopMatrix();
}

void PaddleGlDrawable::updateVBOs(){

}
