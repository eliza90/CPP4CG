# include "view/glut_window.hpp"

# include <GL/freeglut.h>

# include <iostream>

using namespace ::view;

GlutWindow::GlutWindow(const std::string& name, size_t width, size_t height,
						const std::shared_ptr<GlRenderer>& pointer_Renderer,
						const std::shared_ptr<controller::InputEventHandler>& pointer_EventHandler)
: _name( name )
, _width( width )
, _height( height )
{
  // TODO 4.1: assign input event handler and renderer
  //std::cerr << "!! view::GlutWindow::GlutWindow: (PARTS ARE) UNIMPLEMENTED." << std::endl; 
  const std::shared_ptr<GlRenderer> shrPointer_glRenderer(pointer_Renderer);
  const std::shared_ptr<controller::InputEventHandler> shrPointer_EventHandler(pointer_EventHandler);

  // GLUT GlutWindow Initialization:
  glutInitWindowSize( width, height );
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );

  _glut_win_id = glutCreateWindow( name.c_str() );
  if( is_closed() ) 
    throw std::logic_error( "::view::GlutWindow::GlutWindow: Could not create GLUT window." );

  glutSetWindowData( this );

  // setup callbacks
  glutDisplayFunc( glutDisplay );
  glutReshapeFunc( glutReshape );
  glutKeyboardFunc( glutKeyboard );
  glutCloseFunc( glutClose );
}

GlutWindow::~GlutWindow()
{
  close();
}

void GlutWindow::invalidate()
{
  if( is_closed() )
  {
    std::clog << "view::GlutWindow::ensureCurrent: Window was already closed." << std::endl;
    return;
  }
  ensureCurrent();
  glutPostRedisplay();
}

void GlutWindow::ensureCurrent() const
{
  if( is_closed() )
  {
    std::clog << "view::GlutWindow::ensureCurrent: Window was already closed." << std::endl;
    return;
  }
  if( _glut_win_id != glutGetWindow() ) 
  {
    std::clog << "view::GlutWindow::ensureCurrent: Switching to window " << _name << " with id " << _glut_win_id << "…" << std::endl;
    glutSetWindow( _glut_win_id );
  }
}

unsigned int GlutWindow::width() const
{
  return _width;
}

unsigned int GlutWindow::height() const
{
  return _height;
}

bool GlutWindow::is_closed() const
{
  return _glut_win_id <= 0;
}

void GlutWindow::close()
{
  if( is_closed() )
  {
    std::clog << "view::GlutWindow::close: Window was already closed." << std::endl;
    return;
  }
  glutDestroyWindow( _glut_win_id );
  _glut_win_id = -1;
}

void GlutWindow::glutDisplay() 
{
  GlutWindow* win = reinterpret_cast< GlutWindow* >( glutGetWindowData() );
  if (!win){
	  throw std::out_of_range("view::GlutWindow::glutDisplay: Could not get pointer to GlutWindow.");
  }

  // TODO 4.1: use renderer to draw the model
  /*!!*///std::cerr << "!! view::GlutWindow::glutDisplay: (PARTS ARE) UNIMPLEMENTED." << std::endl; 
  std::shared_ptr<GlRenderer>& r = win->getRenderer();
  r->visualize_model(*win);
}

void GlutWindow::glutReshape( int width, int height )
{
  GlutWindow* win = reinterpret_cast< GlutWindow* >( glutGetWindowData() );
  if( ! win ) 
    throw std::out_of_range( "view::GlutWindow::glutReshape: Could not get pointer to GlutWindow." );

  win->_width = width;
  win->_height= height;

  // TODO 4.1: use renderer to resize the view
  /*!!*///std::cerr << "!! view::GlutWindow::glutReshape: (PARTS ARE) UNIMPLEMENTED." << std::endl; 
  std::shared_ptr<GlRenderer>& r = win->getRenderer();
  r->resize(*win);
}

void GlutWindow::glutKeyboard( unsigned char glut_key, int mouse_x, int mouse_y )
{
  GlutWindow* win = reinterpret_cast< GlutWindow* >( glutGetWindowData() );
  if( ! win )
    throw std::out_of_range( "view::GlutWindow::glutKeyboard: Could not get pointer to GlutWindow." );

  std::shared_ptr<controller::InputEventHandler>& keyboard = win->getEventHandler();

  /*TODO 4.1: input event handler is valid*/
  if (keyboard != nullptr){
	   // TODO 4.1:  create keyboard-event data structure and forward it to the event handler
	  //std::cerr << "!! view::GlutWindow::glutKeyboard: (PARTS ARE) UNIMPLEMENTED." << std::endl;

	  struct controller::InputEventHandler::keyboard_event k_event;
	  k_event.key = glut_key;
	  k_event.mouse_pos[0] = mouse_x;
	  k_event.mouse_pos[1] = mouse_y;	  
	  //1 = "activated"	   
	  if (GetKeyState(VK_SHIFT) == 1) { k_event.SHIFT_ACTIVE; }
	  if (GetKeyState(VK_CONTROL) == 1) { k_event.CTRL_ACTIVE; }
	  if (GetKeyState(VK_MENU) == 1) { k_event.ALT_ACTIVE; }
	  keyboard->handle(k_event);
  }
  else{
	  std::clog << "view::GlutWindow::glutKeyboard: no InputEventHandler attached (which could handle the event)." << std::endl;
  }
}

void GlutWindow::glutClose() 
{ 
  GlutWindow* win = reinterpret_cast< GlutWindow* >( glutGetWindowData() );
  if( ! win )
    throw std::out_of_range( "view::GlutWindow::glutClose: Could not get pointer to GlutWindow." );

  if( win->is_closed() )
  {
    std::clog << "view::GlutWindow::glutClose: Window was already closed." << std::endl;
    return;
  }

  win->_glut_win_id = -1;
}
