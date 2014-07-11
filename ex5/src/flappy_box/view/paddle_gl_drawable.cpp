# include "flappy_box/view/paddle_gl_drawable.hpp"

# include <algorithm>

using namespace ::flappy_box::view;


PaddleGlDrawable::PaddleGlDrawable(const std::shared_ptr<::flappy_box::model::Paddle>& b)
: _model( b ){
	// generate a new VBO and get the associated ID
	glGenBuffers(1, &vbo_vertices);
	glGenBuffers(1, &vbo_normals);

	// bind VBO in order to use
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_vertices); 
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_normals);

	updateVBOs();
}

PaddleGlDrawable::~PaddleGlDrawable(){
	glDeleteBuffers(1, &vbo_vertices);
}

void PaddleGlDrawable::updateVBOs(){
	r0 = _model->position()[0];
	r1 = _model->position()[2];
	//vertices erzeugen
	double alpha = 0;
	double beta = 0;

	int outer_step = 2 * M_PI / 40;
	int inner_step = 2 * M_PI / 15;

	for (int k = 0; k < sizeof(vertices); k++){
		for (int j = 0; j < 40; j++){//großer Radius
			//alpha = 2 * M_PI * static_cast<double>(j) / static_cast<double>(40);
			alpha = alpha + outer_step;
			for (int i = 0; i < 15; i++){//großer Radius
				//beta = 2 * M_PI * static_cast<double>(i) / static_cast<double>(15);
				beta = beta + inner_step;
				if (k % 3 == 0){//z
					vertices[k] = r1*sin(beta);
				}
				else if ((k % 2 == 0) && !(k % 3 == 0)){//y
					vertices[k] = r0*sin(alpha)+ r1*(cos(beta)*sin(alpha));
				}
				else{//x
					vertices[k] = r0*cos(alpha) + r1*(cos(beta)*cos(alpha));
				}				
			}
		}
	}
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_vertices);

	for (int k = 0; k < sizeof(normals); k++){
		for (int j = 0; j < 40; j++){//großer Radius
			alpha = 2 * M_PI * static_cast<double>(j) / static_cast<double>(40);
			for (int i = 0; i < 15; i++){//großer Radius
				beta = 2 * M_PI * static_cast<double>(i) / static_cast<double>(15);
				if (k % 3 == 0){//z
					normals[k] = sin(beta);
				}
				else if ((k % 2 == 0) && !(k % 3 == 0)){//y
					normals[k] = cos(beta)*sin(alpha);
				}
				else{//x
					normals[k] = cos(beta)*cos(alpha);
				}
			}
		}
	}
	
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_normals);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ARRAY_BUFFER);

}

void PaddleGlDrawable::visualize(::view::GlRenderer& r, ::view::GlutWindow& w){
	::glEnableClientState(GL_VERTEX_ARRAY); 
	::glEnableClientState(GL_NORMAL_ARRAY); 
	::glColor3f(.6f, .9f, .7f); 
	::glBindBuffer(GL_ARRAY_BUFFER, this->vertices[0]);
	::glVertexPointer(3, GL_FLOAT, 0, NULL); 
	::glBindBuffer(GL_ARRAY_BUFFER, this->normals[0]);
	::glNormalPointer(GL_FLOAT, 0, NULL); 
	//::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, this->ring_vbuf[2]); 
	//::glDrawElements(GL_TRIANGLES, ring_seg1 * ring_seg2 * 6, GL_UNSIGNED_INT, NULL);
}