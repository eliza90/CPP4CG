# pragma once

# include "controller/logic.hpp"
# include "flappy_box/model/box.hpp"
# include "flappy_box/model/paddle.hpp"
# include "flappy_box/model/world.hpp"
# include "flappy_box/model/game_over.hpp"
#include <chrono>

namespace flappy_box
{
  namespace controller
  {

	  class WorldLogic : public ::controller::Logic::ObjectLogic
    {
      public:
		  WorldLogic() = delete;
		  WorldLogic(const std::shared_ptr< model::World >&);

        virtual bool advance( ::controller::Logic&, ::controller::InputEventHandler::keyboard_event const & ) override;

      private:
        std::shared_ptr< model::World > _model;
		bool _shallRestartTheGame;
		int _timeframe_count;
		std::chrono::steady_clock::time_point clock_begin;

		void addBoxToGame(::controller::Logic& l);
		void setForce(std::shared_ptr< flappy_box::model::Box > & box, std::shared_ptr< flappy_box::model::Paddle > & paddle);
		void restartGame(::controller::Logic& l);
    };

  }

} // audiophile