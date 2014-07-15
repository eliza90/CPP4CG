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

	

	// open texture data
	pFile = fopen("../../res/thehead.raw", "rb");
	//if (pFile == NULL) return 0;

	// allocate buffer
	width = 128;
	height = 128;
	textureCoord = new unsigned char[(width * height * 3)];

	// read texture data
	fread(textureCoord, width * height * 3, 1, pFile);
	fclose(pFile);

	// allocate a texture name
	glGenTextures(1, &boxTexture);

	// select our current texture
	glBindTexture(GL_TEXTURE_2D, boxTexture);

	// select modulate to mix texture with color for shading

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureCoord);

	glGenTextures(1, &boxTexture);
	glBindTexture(GL_TEXTURE_2D, boxTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureCoord);
}

BoxGlDrawable::~BoxGlDrawable(){
	glDeleteTextures(1, &boxTexture);
}

void BoxGlDrawable::visualize( ::view::GlRenderer& r, ::view::GlutWindow& w ){
		  
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
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_CULL_FACE);

	//set Pointer
	glNormalPointer(GL_FLOAT, 0, normals);
	glVertexPointer(3, GL_FLOAT, 0, vertices);


	double angle = _model->angle();
	const vec3_type& pos = _model->position();
	const double size = _model->getSize();

	glTranslated(pos[0], pos[1], pos[2]);
	glRotated(angle, 0., 1., 0.);
	glScaled(size, size, size);

	//Boxen
	glColor3f(1.5, 0.5, 0.5);
	glDrawArrays(GL_QUADS, 0, 24);

	//Wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);
	glColor3f(0.5, 0., 0.);
	glDrawArrays(GL_QUADS, 0, 24);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//backface culling	
	//glFrontFace(GL_CCW);//Polygone deren Punkte entgegen dem Uhrzeigersinn definiert wurden, werden als Vorderseite erkannt
	//glCullFace(GL_BACK);

	// Beleuchtung
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);


	//GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	//GLfloat mat_diffuse[] = { 0.4, 0.8, 0.4, 1.0 };
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	//GLfloat lightKa[] = { 1.0f, 1.0f, 1.0f };
	//GLfloat lightKd[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//GLfloat lightPos[] = { 0, 0, 0, 0 };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


	GLfloat light_pos[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_color[] = { 1.0, 1.0, 1.0, 1.0 };

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);

	

	
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
