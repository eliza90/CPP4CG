# include "view/gl_renderer.hpp"

# include "view/glut_window.hpp"

# include "GL/freeglut.h"

using namespace ::view;

GlRenderer::GlRenderer( std::shared_ptr< model::Game const > const& g )
: _game_model( g )
{}

std::shared_ptr< ::model::Game const > const& GlRenderer::game_model() const
{
  return _game_model;
}

GlRenderer::delegate_factory_type& GlRenderer::drawable_factory()
{
  return _drawable_factory;
}

GlRenderer::delegate_factory_type const& GlRenderer::drawable_factory() const
{
  return _drawable_factory;
}

void GlRenderer::visualize_model( GlutWindow& w )
{
  // TODO 4.3: initialize OpenGL context, call delegates and swap buffers
  /*!!*///std::cerr << "!! view::GlRenderer::visualize_model: (PARTS ARE) UNIMPLEMENTED." << std::endl; 
  glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); //Reset the camera
  gluPerspective(45., w.width() / double(w.height()), .5, 100.);

  struct VisualDelegate : public Drawable{
	  VisualDelegate(const std::shared_ptr<::model::TestGameObject> _l) : l(_l){}
	  virtual void visualize(GlRenderer&, GlutWindow&) {
		  std::cout << "view::GlRenderer::visualize: Test Image!\n" << std::endl;
	  }
	  std::shared_ptr<model::TestGameObject> l;
  };
  
  _drawable_factory.register_module<model::TestGameObject>(
	  [](const std::shared_ptr <model::TestGameObject>& _l){ return std::make_shared<VisualDelegate>(_l); }
  );

  std::vector<std::shared_ptr< model::GameObject>> myObjects(game_model()->objects());//vektor mit den game objekten
  
  for (auto o : myObjects)
	  _drawable_factory.create_for(o)->visualize(*this, w);

  glutSwapBuffers();
}

void GlRenderer::resize( GlutWindow& win ) 
{
  glViewport( 0,0, win.width(), win.height() );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity(); //Reset the camera
  gluPerspective( 45., win.width() / double( win.height() ), .5, 100. );
}
