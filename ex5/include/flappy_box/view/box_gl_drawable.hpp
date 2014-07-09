# pragma once
#include <GL/freeglut.h>

# include "view/gl_renderer.hpp"

# include "flappy_box/model/box.hpp"

namespace flappy_box
{
  namespace view
  {
    class BoxGlDrawable : public ::view::GlRenderer::Drawable
    {
      public:

        BoxGlDrawable( const std::shared_ptr< model::Box >& );
        virtual ~BoxGlDrawable();
        virtual void visualize( ::view::GlRenderer&, ::view::GlutWindow& ) override;

      private:
		  std::shared_ptr< model::Box const > _model;
		  GLuint boxTexture;
		  //unsigned char textureCoord[3][128][128];
		  unsigned char textureCoord[49152];
	}; // BoxGlDrawable
  }
}
