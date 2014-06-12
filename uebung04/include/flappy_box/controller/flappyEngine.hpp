# pragma once

# include "controller/glut_engine.hpp"
# include "view/glut_window.hpp"
# include "view/gl_renderer.hpp"
# include "view/al_renderer.hpp"
# include "flappy_box/model/box.hpp"
# include "flappy_box/view/boxDrawable.hpp"
# include "flappy_box/view/boxAudible.hpp"

namespace controller
{
	
  class FlappyEngine : public controller::GlutEngine{    

  public:
	  std::shared_ptr<view::GlRenderer> ptr_glRenderer;
	  std::shared_ptr<view::AlRenderer> ptr_AlRenderer;

	  virtual void init(int& argc, char** argv);
	  virtual void run();


  }; // FlappyEngine

} // model::
