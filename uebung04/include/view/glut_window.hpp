# pragma once

# include "view/gl_renderer.hpp"
# include "controller/input_event_handler.hpp"

# include <string>

namespace view
{

  class GlutWindow
  {
    public:

      // TODO 4.1: change constructor prototype so it takes
      //           additional pointers to a renderer and a event-handler. 
		GlutWindow(const std::string& name, size_t width, size_t height,
					const std::shared_ptr<GlRenderer>& pointer_Renderer,
					const std::shared_ptr<controller::InputEventHandler>& pointer_EventHandler);
		
      ~GlutWindow();

      unsigned int width() const;
      unsigned int height() const;	  

	  // TODO 4.1: add member variables for references to event handler and renderer
	  std::shared_ptr<GlRenderer> shrPointer_glRenderer;
	  std::shared_ptr<controller::InputEventHandler> shrPointer_EventHandler;

     // TODO 4.1: declare getters for event handler and renderer
	  std::shared_ptr<GlRenderer>& getRenderer() { return shrPointer_glRenderer; }
	  std::shared_ptr<controller::InputEventHandler>& getEventHandler(){ return shrPointer_EventHandler;}

      // Request window redisplay.
      void invalidate();

      // Indicates if window was already closed.
      bool is_closed() const;
      // Allows to manually close the window before the destructor is called.
      void close();

    private:
      // make sure this Window is the current GLUT Window.
      void ensureCurrent() const;

      static void glutDisplay(); 
      static void glutReshape( int width, int height );
      static void glutKeyboard( unsigned char glut_key, int mouse_x, int mouse_y );
      static void glutClose();

      std::string _name;
      size_t      _width;
      size_t      _height;
      int         _glut_win_id;
	        
  }; // GlutWindow

} // view::

