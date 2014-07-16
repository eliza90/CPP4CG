# pragma once

# include "view/gl_renderer.hpp"

# include "flappy_box/model/world.hpp"

namespace flappy_box
{
	namespace view
	{
		class WorldGlDrawable : public ::view::GlRenderer::Drawable
		{
		public:

			WorldGlDrawable(const std::shared_ptr< model::World>&);
			virtual ~WorldGlDrawable();
			virtual void visualize(::view::GlRenderer&, ::view::GlutWindow&) override;

		private:
			std::shared_ptr< model::World const > _model;

			//GLuint worldTexture;
			//unsigned char textureCoord[3][128][128];
			unsigned char* textureCoord;
			int wwidth, wheight;
			FILE * wFile;

		}; // BoxGlDrawable
	}
}
