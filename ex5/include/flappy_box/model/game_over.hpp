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

		private:

			const int _playerPoints;

		}; // World

	} // model::
} // flappy_box::