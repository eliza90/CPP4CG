# pragma once

# include "view/gl_renderer.hpp"

# include "flappy_box/model/world.hpp"

namespace flappy_box
{
  namespace view
  {
	  class GameOverGlDrawable : public ::view::GlRenderer::Drawable
    {
      public:

		  GameOverGlDrawable(const std::shared_ptr< model::World>&);
		  virtual ~GameOverGlDrawable();
        virtual void visualize( ::view::GlRenderer&, ::view::GlutWindow& ) override;
		
      private:
        std::shared_ptr< model::World const > _model;

    }; // BoxGlDrawable
  }
}
