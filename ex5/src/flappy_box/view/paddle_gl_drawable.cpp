# include "flappy_box/view/paddle_gl_drawable.hpp"

# include <algorithm>

using namespace ::flappy_box::view;


PaddleGlDrawable::PaddleGlDrawable(const std::shared_ptr<::flappy_box::model::Paddle>& b)
: _model( b ){
	// generate a new VBO and get the associated ID
	glGenBuffers(3, &ring_vbuf[0]);	
	glGenBuffers(3, &rotor_vbuf[0]);

	updateVBOs();
}

PaddleGlDrawable::~PaddleGlDrawable(){
	glDeleteBuffers(1, &ring_vbuf[0]);
	glDeleteBuffers(2, &ring_vbuf[1]);
	glDeleteBuffers(3, &ring_vbuf[2]);

	glDeleteBuffers(1, &rotor_vbuf[0]);
	glDeleteBuffers(2, &rotor_vbuf[1]);
	glDeleteBuffers(3, &rotor_vbuf[2]);
}

void PaddleGlDrawable::updateVBOs(){
	//r0 = (_model->getSize()[0] + _model->getSize()[2])/2;
	//r1 = _model->getSize()[1];	
	r0 = std::max(_model->getSize()[0], _model->getSize()[2]) / 2;
	r1 = std::min((static_cast<unsigned int>(_model->getSize()[1] / 2)), r0);

	//vertices erzeugen
	double alpha = 0;
	double beta = 0;

	unsigned int n = 0;
	for (int j = 0; j < ring_seg1; j++){//großer Radius
		alpha = 2 * M_PI * (static_cast<double>(j) / static_cast<double>(ring_seg1));

		for (int i = 0; i < ring_seg2; i++){//kleiner Radius
			beta = 2 * M_PI * (static_cast<double>(i) / static_cast<double>(ring_seg2));

			vbo_vertices[n] = r0*cos(alpha) + r1*cos(beta)*cos(alpha);//x
			n++;

			vbo_vertices[n] = r0*sin(alpha) + r1*cos(beta)*sin(alpha);//y
			n++;

			vbo_vertices[n] = r1*sin(beta);//z
			n++;
		}
	}

	n = 0;
	for (int j = 0; j < ring_seg1; j++){//großer Radius
		alpha = 2 * M_PI * static_cast<double>(j) / static_cast<double>(ring_seg1);
		for (int i = 0; i < ring_seg2; i++){//großer Radius
			beta = 2 * M_PI * static_cast<double>(i) / static_cast<double>(ring_seg2);

			vbo_normals[n] = cos(beta)*cos(alpha);
			n++;

			vbo_normals[n] = cos(beta)*sin(alpha);
			n++;

			vbo_normals[n] = sin(beta);
			n++;
		}
	}

	//calculating the index array	
	
	for (std::size_t k = 0; k < ring_seg1; ++k) {
		for (std::size_t j = 0; j < ring_seg2; ++j) {
			n = (j + k*ring_seg2)+j*5;

			if (j == (ring_seg2-1)){//letztes Dreieck
				vbo_indices[n] = static_cast<int>(j + k*ring_seg2); // zB 14 + 0*40          ->   14
				vbo_indices[n+1] = static_cast<int>(j + k*ring_seg2 + ring_seg2); //14+15  ->   29
				vbo_indices[n+2] = static_cast<int>((j + k*ring_seg2) - j);//    14 - 14     ->   0
								
				vbo_indices[n+3] = static_cast<int>(j + k*ring_seg2 - (ring_seg2 - 1)); // zB 14 + 0*40 -14 ->  0
				vbo_indices[n+4] = static_cast<int>(j + k*ring_seg2 + ring_seg2); //14+15   ->   29
				vbo_indices[n+5] = static_cast<int>(j + k*ring_seg2 + 1);//    14 + 1        ->   15
				
			}
			else if (k == (ring_seg1 -1)){//letzer Ring
				vbo_indices[n] = static_cast<int>(j + k*ring_seg2); // zB 0 + 39*15          ->   585
				vbo_indices[n+1] = static_cast<int>(j);                //       0          ->   0
				vbo_indices[n+2] = static_cast<int>(j + k*ring_seg2 + 1);//    585 + 1     ->   586

				vbo_indices[n+3] = static_cast<int>(j + k*ring_seg2 + 1); // zB 0 + 39*15 +1 -> 586
				vbo_indices[n+4] = static_cast<int>(j);                                //0   -> 0
				vbo_indices[n+5] = static_cast<int>(j + 1);                 //    0  + 1       -> 1
			}
			else{
				vbo_indices[n] = static_cast<int>(j + k*ring_seg2); // zB 0 + 0*40           ->   0
				vbo_indices[n+1] = static_cast<int>(j + k*ring_seg2 + ring_seg2); //0+15   ->   15
				vbo_indices[n+2] = static_cast<int>(j + k*ring_seg2 + 1);//    0 + 1       ->   1

				vbo_indices[n+3] = static_cast<int>(j + k*ring_seg2 + 1); // zB 0 + 0*40 +1 -> 1
				vbo_indices[n+4] = static_cast<int>(j + k*ring_seg2 + ring_seg2); //0+15    -> 15
				vbo_indices[n+5] = static_cast<int>(j + k*ring_seg2 + ring_seg2 + 1);//    14 + 1       -> 15
			}
		}
	}
	std::cout << n << '\n';//=3599 für indices korrekt
	

//alpha = 0;
//beta = 0;
//for (int i = 0; i < ring_seg1; i++){
//	alpha = 2.0f * M_PI * static_cast<double>(i) / static_cast<double>(ring_seg2);
//
//	int r = ring_seg2 * i;
//
//	for (int j = 0; j < ring_seg2; j++)	{
//		beta = 2.0f * M_PI * static_cast<double>(j) / static_cast<double>(ring_seg1);
//				
//		int n = ring_seg2 * i * 6;
//
//		vbo_indices[n] = (j + r);
//		vbo_indices[n+1] = (j + 15 + r) % 600;
//		vbo_indices[n+2] = ((j + 1) % 15) + r;
//		vbo_indices[n+3] = ((j + 1) % 15) + r;
//		vbo_indices[n+4] = (j + 15 + r) % 600;
//		vbo_indices[n+5] = (((j + 1) % 15) + 15 + r) % 600;
//	}
//}		

	//Rotors
	for (int i = 0; i < rotors; i++){
		double alpha1 = static_cast<double>((i - 0.3)) / static_cast<double>(rotors);
		double alpha2 = static_cast<double>((i + 0.3)) / static_cast<double>(rotors);

		int n = i*9;
		//Vertices
			//vo
				rotor_vertices[n] = 0;
				rotor_vertices[n+1] = 0;
				rotor_vertices[n+2] = 0;
			//v1
				rotor_vertices[n+3] = (r0 - r1)*cos(alpha1);//x
				rotor_vertices[n+4] = (r0 - r1)*sin(alpha1);//y
				rotor_vertices[n+5] = r1;//z				
			//v2
				 rotor_vertices[n+6] = (r0 - r1)*cos(alpha2);//x
				 rotor_vertices[n+7] = (r0 - r1)*sin(alpha2);//y n++;
				 rotor_vertices[n+8] = r1*(-1);//z
				 
	for (int k = 0; k < 3; k++){
		//Indices
				 n = i*3+k*3;
				 rotor_indices[n] = i*9;
				 rotor_indices[n+1] = i*9 + 3;
				 rotor_indices[n+2] = i*9 + 6;

		//Normals
				 vec3_type v0 = vec3_type(0, 0, 0);
				 vec3_type v1 = vec3_type((r0 - r1)*cos(alpha1), 
				 							 (r0 - r1)*sin(alpha1),
				 							 r1);
				 vec3_type v2 = vec3_type((r0 - r1)*cos(alpha2),
				 							(r0 - r1)*sin(alpha1),
				 							r1);

				 vec3_type a = v2 - v0;
				 vec3_type b = v1 - v0;

				 n = i * 3 + k * 3;
				 	rotor_normals[n] = abs(a[1] * b[2] - a[2] * b[1]);
				 	rotor_normals[n+1] = abs(a[2] * b[0] - a[0] * b[2]);
				 	rotor_normals[n+2] = abs(a[0] * b[1] - a[1] * b[0]);
	 }

	}
						
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->rotor_vbuf[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rotor_vertices), rotor_vertices, GL_STATIC_DRAW);
	
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->rotor_vbuf[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rotor_normals), rotor_normals, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rotor_vbuf[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rotor_indices), rotor_indices, GL_STATIC_DRAW);

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ARRAY_BUFFER);
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->ring_vbuf[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_vertices), vbo_vertices, GL_STATIC_DRAW);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->ring_vbuf[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_normals), vbo_normals, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ring_vbuf[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vbo_indices), vbo_indices, GL_STATIC_DRAW);

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		
}

void PaddleGlDrawable::visualize(::view::GlRenderer& r, ::view::GlutWindow& w){
	
	const vec3_type& pos = _model->position();
	glTranslated(pos[0], pos[1], pos[2]);

	::glEnableClientState(GL_VERTEX_ARRAY);
	::glEnableClientState(GL_NORMAL_ARRAY);
	::glEnable(GL_LIGHTING);
	::glEnable(GL_LIGHT0);
	::glEnable(GL_COLOR_MATERIAL);

	GLfloat light_pos[] = { pos[0], pos[1] - r0*1.5, pos[2] + r1 * 3, 1 };
	float light_color[] = { 0.2, 0.2, 0.2, 0.2 };

	::glColor3f(.6f, .9f, .7f);
	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	
	glPushMatrix();
	{						
	::glBindBuffer(GL_ARRAY_BUFFER, this->ring_vbuf[0]);
	::glVertexPointer(3, GL_FLOAT, 0, NULL); 
	::glBindBuffer(GL_ARRAY_BUFFER, this->ring_vbuf[1]);
	::glNormalPointer(GL_FLOAT, 0, NULL); 
	::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, this->ring_vbuf[2]);
	::glDrawElements(GL_TRIANGLES, ring_seg1*ring_seg2*6, GL_UNSIGNED_INT, NULL);
		
	::glBindBuffer(GL_ARRAY_BUFFER, this->rotor_vbuf[0]);
	::glVertexPointer(3, GL_FLOAT, 0, NULL);
	::glBindBuffer(GL_ARRAY_BUFFER, this->rotor_vbuf[1]);
	::glNormalPointer(GL_FLOAT, 0, NULL);
	::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, this->rotor_vbuf[2]);
	::glDrawElements(GL_TRIANGLES, rotors*3, GL_UNSIGNED_INT, NULL);
	}
	glPopMatrix();

	::glDisableClientState(GL_VERTEX_ARRAY);
	::glDisableClientState(GL_NORMAL_ARRAY);
	::glDisable(GL_LIGHTING);
	::glDisable(GL_LIGHT0);
	::glDisable(GL_COLOR_MATERIAL);
	
	
	//glPushMatrix();
	//{
	//  double angle = 0;
	//  const vec3_type& pos = _model->position();
	//  const double size = 2;
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