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

		GLuint vbo_vertices;
		GLfloat* vertices = new GLfloat[600];

		GLuint vbo_normals;
		GLfloat* normals = new GLfloat[600];
    }; // PaddleGlDrawable
  }
}
