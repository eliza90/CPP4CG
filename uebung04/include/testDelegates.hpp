//# pragma once
//# include "model/game.hpp"
//# include "model/test_game_object.hpp"
//# include "controller/logic.hpp"
//# include "view/al_renderer.hpp"
//# include "view/gl_renderer.hpp"
//
//namespace controller {
//
//	struct LogicDelegate : public controller::Logic::ObjectLogic{
//		LogicDelegate(const std::shared_ptr<::model::TestGameObject> _l) : l(_l){}
//		bool advance(Logic&, controller::InputEventHandler::keyboard_event const&){
//			std::cout << "controller::Logic::advance: Test Thinking!\n" << std::endl;
//			return true;
//		}
//		std::shared_ptr<model::TestGameObject> l;
//	}; // LogicDelegate
//} // controller

//namespace view {
//
//	struct VisualDelegate : public view::GlRenderer::Drawable{
//		VisualDelegate(const std::shared_ptr<::model::TestGameObject> _l) : l(_l){}
//		virtual void visualize(GlRenderer&, GlutWindow&) {
//			std::cout << "view::GlRenderer::visualize: Test Image!\n" << std::endl;
//		}
//		std::shared_ptr<model::TestGameObject> l;
//	};//VisualDelegate
//
//	struct AudioDelegate : public view::AlRenderer::Audible{
//		AudioDelegate(const std::shared_ptr<::model::TestGameObject> _l) : l(_l){}
//		virtual void auralize(AlRenderer&){
//			std::cout << "view::AlRenderer::auralize: Test Sound!" << std::endl;
//		}
//		std::shared_ptr<model::TestGameObject> l;
//	};//AudioDelegate
//
//}//view