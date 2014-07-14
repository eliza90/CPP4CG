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
	glDeleteBuffers(1, &ring_vbuf[1]);
	glDeleteBuffers(1, &ring_vbuf[2]);

	glDeleteBuffers(1, &rotor_vbuf[0]);
	glDeleteBuffers(1, &rotor_vbuf[1]);
	glDeleteBuffers(1, &rotor_vbuf[2]);
}

void PaddleGlDrawable::updateVBOs(){
	r0 = (_model->getSize()[0] + _model->getSize()[2])/2;
	r1 = _model->getSize()[1];	

	//vertices erzeugen
	double alpha = 0;
	double beta = 0;

	int n = 0;
		for (int j = 0; j < ring_seg1; j++){//großer Radius
			alpha = 2 * M_PI * (static_cast<double>(j) / static_cast<double>(ring_seg1));
			for (int i = 0; i < ring_seg2; i++){//großer Radius
				beta = 2 * M_PI * (static_cast<double>(i) / static_cast<double>(ring_seg2));
				
					vbo_vertices[n] = r0*cos(alpha) + r1*cos(beta)*cos(alpha);//x
					n++;

					vbo_vertices[n] = r0*sin(alpha) + r1*sin(alpha)*cos(beta);//y
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
	n = 0;			
	for (int k = 0; k < ring_seg1; k++){
		for (int j = 0; j < ring_seg2; j++){	

				int z = j + k*ring_seg2;//k*15 - "offset für nächsten Kreisring"
				if (k == (ring_seg1-1)){
					vbo_indices[n] = z;
					n++;
					//std::cout << z << '\n';
					vbo_indices[n] = j;
					n++;
					//std::cout << j << '\n';
					vbo_indices[n] = z+1;
					n++;	
					//std::cout << z+1 << '\n';

					vbo_indices[n] = z;
					n++;
					vbo_indices[n] = j;
					n++;
					vbo_indices[n] = j + 1;
					n++;
				}
				else{
					vbo_indices[n] = z;
					n++;
					//std::cout << z << '\n';
					vbo_indices[n] = z + ring_seg2;
					n++;
					//std::cout << z + ring_seg2 << '\n';
					vbo_indices[n] = z + 1;
					n++;
					//std::cout << z + 1 << '\n';						

					vbo_indices[n] = z + 1;
					n++;
					//std::cout << z+1 << '\n';
					vbo_indices[n] = z + ring_seg2;
					n++;
					//std::cout << z + ring_seg2 << '\n';
					vbo_indices[n] = z + ring_seg2 + 1;
					n++;
					//std::cout << z + ring_seg2+1<< '\n';
				}
			
		}
	}		
	//std::cout << n << '\n'; n = 3600 -> richtige Anzahl
	
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->ring_vbuf[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_vertices), vbo_vertices, GL_STATIC_DRAW);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->ring_vbuf[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_normals), vbo_normals, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ring_vbuf[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vbo_indices), vbo_indices, GL_STATIC_DRAW);
		
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	
	n = 0;
	double alpha1;
	double alpha2;
	//Rotors
	for (int i = 0; i < rotors; i++){//großer Radius		
		alpha1 = (static_cast<double>(i)-0.3) / static_cast<double>(rotors);
		alpha2 = (static_cast<double>(i)+0.3) / static_cast<double>(rotors);

		if (i%3 == 0){
			rotor_vertices[n] = 0;
			n++;
			rotor_vertices[n] = 0;
			n++;
			rotor_vertices[n] = 0;
			n++;
		}
		else if(i % 3 == 1){
			rotor_vertices[n] = (r0 - r1)*cos(alpha1);//x
			n++;
			rotor_vertices[n] = (r0 - r1)*sin(alpha1);//y
			n++;
			rotor_vertices[n] = r1;//z
			n++;
		}
		 else{
			 rotor_vertices[n] = (r0 - r1)*cos(alpha2);//x
			 n++;
			 rotor_vertices[n] = (r0 - r1)*sin(alpha2);//y
			 n++;
			 rotor_vertices[n] = r1*(-1);//z
			 n++;
		 }
	}

	n = 0;
	//Rotors
	for (int i = 0; i < rotors; i++){//großer Radius		
		alpha1 = (static_cast<double>(i)-0.3) / static_cast<double>(rotors);
		alpha2 = (static_cast<double>(i)+0.3) / static_cast<double>(rotors);

		vec3_type v0 = vec3_type(0,0,0);
		vec3_type v1 = vec3_type((r0 - r1)*cos(alpha1), 
								 (r0 - r1)*sin(alpha1),
								 r1);
		vec3_type v2 = vec3_type((r0 - r1)*cos(alpha2),
								(r0 - r1)*sin(alpha1),
								r1);

		vec3_type a = v2 - v0;
		vec3_type b = v1 - v0;

		rotor_normals[n] = abs(a[1] * b[2] - a[2] * b[1]);
		n++;
		rotor_normals[n] = abs(a[2] * b[0] - a[0] * b[2]);
		n++;
		rotor_normals[n] = abs(a[0] * b[1] - a[1] * b[0]);
		n++;
	}
	
	for (int i = 0; i < rotors * 3; i++){//großer Radius	
		rotor_indices[i] = i;	
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
	
}

void PaddleGlDrawable::visualize(::view::GlRenderer& r, ::view::GlutWindow& w){
	
	const vec3_type& pos = _model->position();
	glTranslated(pos[0], pos[1], pos[2]);

	glPushMatrix();
	{	

	::glColor3f(.6f, .9f, .7f);	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	
	GLfloat lightKd[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPos[] = { pos[0], pos[1]-r0*1.5, pos[2]+r1*3, 1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	::glEnableClientState(GL_VERTEX_ARRAY);
	::glEnableClientState(GL_NORMAL_ARRAY);
	::glEnable(GL_LIGHTING);
	::glEnable(GL_LIGHT0);
	
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

	::glDisableClientState(GL_VERTEX_ARRAY);
	::glDisableClientState(GL_NORMAL_ARRAY);
	::glDisable(GL_LIGHTING);
	::glDisable(GL_LIGHT0);
	::glDisable(GL_COLOR_MATERIAL);

	//glutSolidTorus(1,4,40,15);
	}
	glPopMatrix();
	

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