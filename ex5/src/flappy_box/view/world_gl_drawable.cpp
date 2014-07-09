# include "flappy_box/view/world_gl_drawable.hpp"

#include <GL/freeglut.h>

# include <algorithm>

using namespace ::flappy_box::view;


WorldGlDrawable::WorldGlDrawable(const std::shared_ptr< ::flappy_box::model::World >& b)
: _model( b )
{
  
}

WorldGlDrawable::~WorldGlDrawable()
{

}

void WorldGlDrawable::visualize(::view::GlRenderer& r, ::view::GlutWindow& w)
{

    // TODO: Replace old rendering code with new and improved rendering - Aufgabe 5.3

}
