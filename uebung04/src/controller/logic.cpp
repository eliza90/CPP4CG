# include "controller/logic.hpp"

using namespace ::controller;

Logic::Logic( const std::shared_ptr< ::model::Game >& g ) : _model( g ) {
}

bool Logic::advance_model( const ::controller::InputEventHandler::keyboard_event& ev )
{
  // TODO 4.3: set current timestamp in model and call delegates
  /*!!*///std::cerr << "!! controller::Logic::advance_model: (PARTS ARE) UNIMPLEMENTED." << std::endl; 
	//game model = shared Pointer game
	game_model()->setTimestamp(std::chrono::steady_clock::now()); //setTimestamp
	
	struct DelegateExtractor : public controller::Logic::ObjectLogic {
		virtual std::string test_delegate() = 0;
	};
	struct TestDelegate : public DelegateExtractor{
		TestDelegate(const std::shared_ptr<model::TestGameObject> _l) : l(_l){}
		bool advance(Logic&, controller::InputEventHandler::keyboard_event const&){ return true; }
		virtual std::string test_delegate(){ return "test advance"; }
		std::shared_ptr<model::TestGameObject> l;
	};

	factory_map< model::GameObject, DelegateExtractor> extractor_toolbox;

	extractor_toolbox.register_module<model::TestGameObject>(
		[](const std::shared_ptr <model::TestGameObject>& _l){ return std::make_shared<TestDelegate>(_l); }
	);

	std::vector<std::shared_ptr< model::GameObject>> myObjects(game_model()->objects());//vektor mit den game objekten

	for (auto o : myObjects)
		std::cout << extractor_toolbox.create_for(o)->test_delegate() << std::endl;


	return false;
		
	//struct TestGameObj : public model::GameObject{};
	//
	//struct DelegateExtractor : public controller::Logic::ObjectLogic {
	//	virtual std::string test_delegate() = 0;
	//};
	//struct TestDelegate : public DelegateExtractor{
	//	TestDelegate(const std::shared_ptr<TestGameObj> _l): l(_l){}
	//	bool advance(Logic&, controller::InputEventHandler::keyboard_event const&){ return true; }
	//	virtual std::string test_delegate(){ return "test advance"; }
	//	std::shared_ptr<TestGameObj> l;
	//};

	//factory_map< model::GameObject, DelegateExtractor> extractor_toolbox;

	//extractor_toolbox.register_module<TestGameObj>(
	//	[](const std::shared_ptr <TestGameObj>& _l){ return std::make_shared<TestDelegate>(_l); }
	//);

	//std::vector<std::shared_ptr< model::GameObject>> myObjects(game_model()->objects());//vektor mit den game objekten

	//for (auto o : myObjects)
	//	std::cout << extractor_toolbox.create_for(o)->test_delegate() << std::endl;
	//

 // return false;
}
