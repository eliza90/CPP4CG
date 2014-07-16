# pragma once

# include "model/game_object.hpp"
# include "math.hpp"

namespace flappy_box
{

	namespace model
	{
		class GameOver : public ::model::GameObject
		{
		public:

			GameOver(const std::string& s, const int points);

			const int& getPlayerPoints() const { return _playerPoints; }

			double getWorldHalfHeight() const { return 30.0; } /* gibt die halbe Ausdehnung der Spielwelt in z-Richtung zurück */
			double getWorldHalfWidth() const { return 42.0; } /* gibt die halbe Ausdehnung der Spielwelt in x-Richtung zurück */

		private:

			const int _playerPoints;

		}; // World

	} // model::
} // flappy_box::