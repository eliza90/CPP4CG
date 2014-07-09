# pragma once

# include "model/game_object.hpp"
# include "math.hpp"

// ATTENTION: NEW CODE!

namespace flappy_box
{

	namespace model
	{
		class World : public ::model::GameObject
		{
		public:

			World(const std::string& = "World");

			const int& getPlayerPoints() const { return _playerPoints; }
			void setPlayerPoints(int p) { _playerPoints = p; }

			const int& _getRemainingLives() const { return _remainingLives; }
			void setRemainingLives(int rl) { _remainingLives = rl; }

			double getWorldHalfHeight() const { return 30.0; } /* gibt die halbe Ausdehnung der Spielwelt in z-Richtung zurück */
			double getWorldHalfWidth() const {  return 42.0; } /* gibt die halbe Ausdehnung der Spielwelt in x-Richtung zurück */

		private:

			int               _playerPoints;
			int               _remainingLives;

		}; // World

	} // model::
} // flappy_box::