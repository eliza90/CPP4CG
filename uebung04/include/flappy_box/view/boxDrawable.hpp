# pragma once
# include "view/gl_renderer.hpp"
# include "flappy_box/model/box.hpp"
# include "view/glut_window.hpp"
# include "view/gl_renderer.hpp"
# include "GL/freeglut.h"
#include <chrono>

namespace view {

	class BoxDrawable : public view::GlRenderer::Drawable{

	public:
		BoxDrawable(const std::shared_ptr<::model::Box> _l) : l(_l){
			start = std::chrono::steady_clock::now();
		}
		virtual void visualize(GlRenderer&, GlutWindow&);
		std::shared_ptr<::model::Box> l;
	private:
		std::chrono::steady_clock::time_point start;
  }; // BoxDrawable

} // model::
