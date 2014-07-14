# pragma once

# include "view/gl_renderer.hpp"


# include "flappy_box/model/paddle.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>

namespace flappy_box
{
  namespace view
  {
	  class PaddleGlDrawable : public ::view::GlRenderer::Drawable
    {
      public:

		PaddleGlDrawable(const std::shared_ptr< model::Paddle>&);
		virtual ~PaddleGlDrawable();
        virtual void visualize( ::view::GlRenderer&, ::view::GlutWindow& ) override;

      private:
        std::shared_ptr< model::Paddle const > _model;
		void updateVBOs();

		unsigned int r0;
		unsigned int r1;

		static const int ring_seg1 = 40;
		static const int ring_seg2 = 15;

		GLuint ring_vbuf[3];
		GLfloat vbo_vertices[ring_seg1*ring_seg2];
		GLfloat vbo_normals[ring_seg1*ring_seg2];
		unsigned int vbo_indices[ring_seg1*ring_seg2*3*2];

		static const int rotors = 9;
		GLuint rotor_vbuf[3];
		GLfloat rotor_vertices[rotors*3];
		GLfloat rotor_normals[rotors*3];
		unsigned int rotor_indices[rotors*3];
    }; // PaddleGlDrawable
  }
}
