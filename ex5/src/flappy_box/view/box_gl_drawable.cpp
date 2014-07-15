# include "flappy_box/view/box_gl_drawable.hpp"

# include <algorithm>

using namespace ::flappy_box::view;


BoxGlDrawable::BoxGlDrawable(const std::shared_ptr< ::flappy_box::model::Box >& b)
	: _model(b){
	

	glGenTextures(1, &boxTexture); // allocate a texture name
	glBindTexture(GL_TEXTURE_2D, boxTexture); // select our current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	

	// allocate buffer
	width = 128;
	height = 128;
	textureCoord = new unsigned char[(width * height * 3)];

	// open texture data
	pFile = fopen("../../res/thehead.raw", "rb");
	if (pFile == NULL){
		std::cout << "No Texture found!" << std::endl;
	}
	else {

		// read texture data
		fread(textureCoord, width * height * 3, 1, pFile);
		fclose(pFile);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureCoord);
	}

}

BoxGlDrawable::~BoxGlDrawable(){
	glDeleteTextures(1, &boxTexture);
}

void BoxGlDrawable::visualize(::view::GlRenderer& r, ::view::GlutWindow& w){

	GLfloat vertices[] = {
		0.5, -0.5, -0.5,
		0.5, -0.5, 0.5,
		-0.5, -0.5, 0.5,
		-0.5, -0.5, -0.5,

		0.5, 0.5, -0.5,
		0.5, 0.5, 0.5,
		0.5, -0.5, 0.5,
		0.5, -0.5, -0.5,

		0.5, 0.5, -0.5,
		0.5, -0.5, -0.5,
		-0.5, -0.5, -0.5,
		-0.5, 0.5, -0.5,

		-0.5, -0.5, -0.5,
		-0.5, -0.5, 0.5,
		-0.5, 0.5, 0.5,
		-0.5, 0.5, -0.5,

		0.5, 0.5, 0.5,
		-0.5, 0.5, 0.5,
		-0.5, -0.5, 0.5,
		0.5, -0.5, 0.5,

		0.5, 0.5, -0.5,
		-0.5, 0.5, -0.5,
		-0.5, 0.5, 0.5,
		0.5, 0.5, 0.5
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

	GLfloat texcoords[] = {
		0, 0, 0,
		1, 1, 1,
		1, 0, 0,
		0, 0, 1,

		1, 1, 1,
		0, 0, 0,
		0, 1, 1,
		1, 1, 0,

		0, 0, 0,
		1, 1, 1,
		1, 0, 0,
		0, 0, 1,

		1, 1, 1,
		0, 0, 0,
		0, 1, 1,
		1, 1, 0,


	};


	//set Pointer
	glNormalPointer(GL_FLOAT, 0, normals);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, boxTexture);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	double angle = _model->angle();
	const vec3_type& pos = _model->position();
	const double size = _model->getSize();

	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);
	glRotated(angle, 0., 1., 0.);
	//glRotated(angle *3 , 0.5, 1.2, 0.);
	glScaled(size, size, size);

	//Box
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, boxTexture);
	glDrawArrays(GL_QUADS, 0, 24);
	/*glDisableClientState(GL_TEXTURE_COORD_ARRAY);*/
	glDisable(GL_TEXTURE_2D);

	//Wireframe
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.5, 0.5, 0.5);
	glDrawArrays(GL_QUADS, 0, 24);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
	
	GLfloat light_pos[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_color[] = { 1.0, 1.0, 1.0, 1.0 };

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisable(GL_CULL_FACE);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_NORMALIZE);

			

//glPushMatrix();
//  {
//    double angle = _model->angle();
//    const vec3_type& pos = _model->position();
//    const double size = _model->getSize();
//    glTranslated( pos[0], pos[1], pos[2] );   
//    glRotated( angle, 0., 1., 0. );
//    glScaled( size, size, size );
//
//    glColor3d( 0.25, 0.25, 0.25 );
//
//    ::glBegin(GL_LINES);
//
//    ::glVertex3d(-0.5, -0.5, -0.5);
//    ::glVertex3d(-0.5, -0.5,  0.5);
//    ::glVertex3d(-0.5,  0.5, -0.5);
//    ::glVertex3d(-0.5,  0.5,  0.5);
//    ::glVertex3d( 0.5, -0.5, -0.5);
//    ::glVertex3d( 0.5, -0.5,  0.5);
//    ::glVertex3d( 0.5,  0.5, -0.5);
//    ::glVertex3d( 0.5,  0.5,  0.5);
//
//    ::glVertex3d(-0.5, -0.5, -0.5);
//    ::glVertex3d(-0.5,  0.5, -0.5);
//    ::glVertex3d( 0.5, -0.5, -0.5);
//    ::glVertex3d( 0.5,  0.5, -0.5);
//    ::glVertex3d(-0.5, -0.5,  0.5);
//    ::glVertex3d(-0.5,  0.5,  0.5);
//    ::glVertex3d( 0.5, -0.5,  0.5);
//    ::glVertex3d( 0.5,  0.5,  0.5);
//
//    ::glVertex3d(-0.5, -0.5, -0.5);
//    ::glVertex3d( 0.5, -0.5, -0.5);
//    ::glVertex3d(-0.5, -0.5,  0.5);
//    ::glVertex3d( 0.5, -0.5,  0.5);
//    ::glVertex3d(-0.5,  0.5, -0.5);
//    ::glVertex3d( 0.5,  0.5, -0.5);
//    ::glVertex3d(-0.5,  0.5,  0.5);
//    ::glVertex3d( 0.5,  0.5,  0.5);
//
//    ::glEnd();
//
//  }
//  glPopMatrix();

}
