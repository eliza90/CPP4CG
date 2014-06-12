# pragma once
# include "view/al_renderer.hpp"
# include "flappy_box/model/box.hpp"
# include "view/glut_window.hpp"
# include "view/gl_renderer.hpp"
# include "GL/freeglut.h"

#include <AL/alut.h>

namespace view{

	class BoxAudible: public view::AlRenderer::Audible{ 
		ALuint _al_box_source[1];
	public:
		BoxAudible(const std::shared_ptr<::model::Box> _l);
		virtual void auralize(AlRenderer&);
		std::shared_ptr<::model::Box> l;	

		double const base_frequency = 400;//hz
		double const target_frequency = 100;

		
  }; // BoxAudible

} // model::
