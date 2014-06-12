# pragma once
# include "controller/logic.hpp"
# include "flappy_box/model/box.hpp"

namespace controller
{

	class BoxObjectLogic: public controller::Logic::ObjectLogic{			
    
  public:
	  BoxObjectLogic(const std::shared_ptr<::model::Box> _l) : l(_l){}
	  bool advance(Logic&, controller::InputEventHandler::keyboard_event const&);
	  std::shared_ptr<model::Box> l;

  }; // BoxObjectLogic

} // model::
