# include "flappy_box/model/box.hpp"

using namespace flappy_box::model;

Box::Box( const std::string& n )
: GameObject( true, n )
,           _angle( 0.0 )
,            _size( 0.5 )
,        _position( 0.0, 0.0, 0.0 )
,     _maxPosition( 42, 1.0, 30 )
,        _velocity( 0.0, 0.0, 0.0 )
,    _acceleration( 0.0, 0.0, 0.0 )
,   _externalForce( 0, 0.0, -9.81 )//(x_air, y, gravitation)
, _rotAcceleration( 0.0 )
,     _rotVelocity( 0.0 )
{

}