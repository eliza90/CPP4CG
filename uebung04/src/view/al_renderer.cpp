# include "view/al_renderer.hpp"

# include "flappy_box/model/box.hpp"
# include "flappy_box/view/boxAudible.hpp"

using namespace ::view;

AlRenderer::AlRenderer( std::shared_ptr< model::Game const > const& g ) : _game_model( g ) {
	_audible_factory.register_module<model::Box>(//model::Box>(myBox_ptr
		[](const std::shared_ptr <model::Box>& _l){ return std::make_shared<view::BoxAudible>(_l); }
	);
}

std::shared_ptr< model::Game const > const& AlRenderer::game_model() const
{
  return _game_model;
}

AlRenderer::delegate_factory_type& AlRenderer::audible_factory()
{
  return _audible_factory;
}

AlRenderer::delegate_factory_type const& AlRenderer::audible_factory() const
{
  return _audible_factory;
}

void AlRenderer::auralize_model()
{
  // TODO 4.3: call delegates
  /*!!*///std::cerr << "!! view::AlRenderer::auralize_model: (PARTS ARE) UNIMPLEMENTED." << std::endl; 

	//43 Variante 1 Delegates jedes Mal erstellen
  /*struct AudioDelegate : public view::AlRenderer::Audible{
	  AudioDelegate(const std::shared_ptr<::model::TestGameObject> _l) : l(_l){}
	  virtual void auralize(AlRenderer&){
		  std::cout << "view::AlRenderer::auralize: Test Sound!" << std::endl;
	  }
	  std::shared_ptr<model::TestGameObject> l;
  };

	_audible_factory.register_module<model::TestGameObject>(
		[](const std::shared_ptr <model::TestGameObject>& _l){ return std::make_shared<AudioDelegate>(_l); }
  );

  std::vector<std::shared_ptr< model::GameObject>> myObjects(game_model()->objects());

  for (auto o : myObjects)
	  _audible_factory.create_for(o)->auralize(*this);*/

	//43 Flappy Box Variante 2(get/setData)
	std::vector<std::shared_ptr<model::GameObject>> myObjects(game_model()->objects());//vektor mit den game objekten

	for (auto o : myObjects){

		auto audioDelegate(o->getData<view::AlRenderer::Audible>());

		if (audioDelegate == nullptr){
			o->registerData(_audible_factory.create_for(o));//delegate aus der factorymap
		}
		auto audio(o->getData<view::AlRenderer::Audible>());
		audio->auralize(*this);
	}
}
