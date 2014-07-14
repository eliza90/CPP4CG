# include "flappy_box/view/box_gl_drawable.hpp"

# include <algorithm>

using namespace ::flappy_box::view;


BoxGlDrawable::BoxGlDrawable(const std::shared_ptr< ::flappy_box::model::Box >& b )
: _model( b ){
	//FILE * pFile;

	//pFile = fopen("../../res/thehead.raw", "rb");//rb - read binary
	//
	//// allocate memory:
	//memset(textureCoord, 0, sizeof(textureCoord));

	////long lSize = ftell(pFile);
	//size_t success = fread(textureCoord, sizeof(textureCoord), 1, pFile);//lSize, pFile);
	//
	//// terminate
	//fclose(pFile);

	/*for (int d = 0; d < 3; d++){
		for (int i = 0; i < 128; i++){
			for (int j = 0; i < 128; i++){
				if (d == 2)
					textureCoord[d][i][j] = 1;
				else
					textureCoord[d][i][j] = 0;
			}
		}
	}*/
/*	glGenTextures(1, &boxTexture);
	glBindTexture(GL_TEXTURE_2D, boxTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, textureCoord);*/		
}

BoxGlDrawable::~BoxGlDrawable(){
	glDeleteTextures(1, &boxTexture);
}

void BoxGlDrawable::visualize( ::view::GlRenderer& r, ::view::GlutWindow& w ){

	double angle = _model->angle();
	const vec3_type& pos = _model->position();
	const double size = _model->getSize();
		
		  
	GLfloat vertices[] = {   
							0.5, -0.5, -0.5,
							0.5, -0.5,  0.5,
							-0.5,  -0.5,  0.5,
							-0.5,  -0.5,  -0.5,

							 0.5,   0.5, -0.5,
							 0.5,   0.5,  0.5,
							 0.5,  -0.5,  0.5,
							 0.5,  -0.5, -0.5,

							0.5, 0.5, -0.5,
							0.5,  -0.5, -0.5,   
							-0.5, -0.5, -0.5,   
							-0.5,  0.5, -0.5,

							-0.5, -0.5,  -0.5,
							-0.5,  -0.5,  0.5,
							-0.5, 0.5,  0.5,
							-0.5,  0.5,  -0.5,

	    0.5,  0.5,  0.5,
       -0.5,  0.5,  0.5,
	   -0.5, -0.5,  0.5,
        0.5, -0.5,  0.5,

        0.5,   0.5, -0.5,
	   -0.5,   0.5, -0.5,
       -0.5,   0.5,  0.5,
    	0.5,   0.5,  0.5
	};
	
	GLfloat normals[] = {
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,

		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,

		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,

		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,

		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,

		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
	};
		
	//set Pointer
	glNormalPointer(GL_FLOAT, 0, normals);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glTranslated(pos[0], pos[1], pos[2]);
	glRotated(angle, 0., 1., 0.);
	glScaled(size, size, size);
			
	//backface culling	
	glFrontFace(GL_CCW);//Polygone deren Punkte entgegen dem Uhrzeigersinn definiert wurden, werden als Vorderseite erkannt
	glCullFace(GL_BACK);

	glColor3d(1, 1, 1);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);	
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat mat_diffuse[] = { 0.4, 0.8, 0.4, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	GLfloat lightKa[] = { 1.0f, 1.0f, 1.0f };
	GLfloat lightKd[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPos[] = { 0, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	////glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	////size,type,stride,_pointer
	////glTexCoordPointer(3, GL_FLOAT, 3, 0);
	////glEnable(GL_TEXTURE_2D);
	////glBindTexture(GL_TEXTURE_2D, boxTexture);
	//			
	// draw cube	
	glDrawArrays(GL_QUADS, 0, 24);

	//draw wireframe
	//glDisable(GL_TEXTURE_2D);
	glColor3f(1, 0, 0);
	glLineWidth(3.0f);
	glPolygonMode(GL_FRONT, GL_LINE);
	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
	
	glLineWidth(1.0f);

	glPolygonMode(GL_FRONT, GL_FILL);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  //glPushMatrix();
  //{
  //  double angle = _model->angle();
  //  const vec3_type& pos = _model->position();
  //  const double size = _model->getSize();
  //  glTranslated( pos[0], pos[1], pos[2] );   
  //  glRotated( angle, 0., 1., 0. );
  //  glScaled( size, size, size );

  //  glColor3d( 0.25, 0.25, 0.25 );

  //  ::glBegin(GL_LINES);

  //  ::glVertex3d(-0.5, -0.5, -0.5);
  //  ::glVertex3d(-0.5, -0.5,  0.5);
  //  ::glVertex3d(-0.5,  0.5, -0.5);
  //  ::glVertex3d(-0.5,  0.5,  0.5);
  //  ::glVertex3d( 0.5, -0.5, -0.5);
  //  ::glVertex3d( 0.5, -0.5,  0.5);
  //  ::glVertex3d( 0.5,  0.5, -0.5);
  //  ::glVertex3d( 0.5,  0.5,  0.5);

  //  ::glVertex3d(-0.5, -0.5, -0.5);
  //  ::glVertex3d(-0.5,  0.5, -0.5);
  //  ::glVertex3d( 0.5, -0.5, -0.5);
  //  ::glVertex3d( 0.5,  0.5, -0.5);
  //  ::glVertex3d(-0.5, -0.5,  0.5);
  //  ::glVertex3d(-0.5,  0.5,  0.5);
  //  ::glVertex3d( 0.5, -0.5,  0.5);
  //  ::glVertex3d( 0.5,  0.5,  0.5);

  //  ::glVertex3d(-0.5, -0.5, -0.5);
  //  ::glVertex3d( 0.5, -0.5, -0.5);
  //  ::glVertex3d(-0.5, -0.5,  0.5);
  //  ::glVertex3d( 0.5, -0.5,  0.5);
  //  ::glVertex3d(-0.5,  0.5, -0.5);
  //  ::glVertex3d( 0.5,  0.5, -0.5);
  //  ::glVertex3d(-0.5,  0.5,  0.5);
  //  ::glVertex3d( 0.5,  0.5,  0.5);

  //  ::glEnd();

  //}
  //glPopMatrix();
}
