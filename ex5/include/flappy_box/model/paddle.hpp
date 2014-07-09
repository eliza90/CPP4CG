# pragma once

# include "model/game_object.hpp"
# include "math.hpp"

namespace flappy_box
{

	namespace model
	{
		class Paddle : public ::model::GameObject
		{
		public:
			Paddle(const std::string& = "Paddle");
			
			const vec3_type& position() const { return _position; }
			void setPosition(const vec3_type& p) { _position = p; }

			const vec3_type& maxPosition() const { return _maxPosition; }
			void setMaxPosition(const vec3_type& p) { _maxPosition = p; }
			
			const vec3_type& velocity() const { return _velocity; }
			void setVelocity(const vec3_type& v) { _velocity = v; }

			const vec3_type& acceleration() const { return _acceleration; }
			void setAcceleration(const vec3_type& a) { _acceleration = a; }

			const vec3_type& getSize() const { return _size; }
			void size(const vec3_type& s) { _size = s; }

			const double& getPlayerControl() const { return _playerControl; }
			void setPlayerControl(const double& pc) { _playerControl = pc; }

		private:
			vec3_type  _position;
			vec3_type  _maxPosition;
			vec3_type  _velocity;
			vec3_type  _acceleration;
			vec3_type  _size;
			double     _playerControl;
		}; // Paddle

	} // model::
} // flappy_box::