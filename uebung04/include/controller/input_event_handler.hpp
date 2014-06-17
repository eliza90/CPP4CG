# pragma once

namespace controller 
{

  class InputEventHandler
  {  
    public:

      struct keyboard_event // TO DO: define struct keyboard_event
      {
		  keyboard_event(){}
		  char key;
		  enum modifier_mask { SHIFT_ACTIVE = 1, CTRL_ACTIVE = 2, ALT_ACTIVE = 4 };
		  /*constexpr modifier_mask operator | (modifier_mask m1, modifier_mask m2) {
			   return modifier_mask(int(m1) | int(m2));
		  }*/
		  double mouse_pos[2];
      };
	      
	  virtual bool handle(keyboard_event const&) = 0;

  }; // InputEventHandler

} // controller::
