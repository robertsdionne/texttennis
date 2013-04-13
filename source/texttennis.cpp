#include <Box2D/Box2D.h>

#include "constants.h"
#include "introduction.h"
#include "parameter.h"
#include "scene.h"
#include "scene1.h"
#include "scene2.h"
#include "scene3.h"
#include "scene4.h"
#include "scene5.h"
#include "slider.h"
#include "texttennis.h"

/**
 * Public method definitions.
 */
TextTennis::TextTennis()
: scene_factory_functions(), scene_index(0), current_scene(nullptr),
  show_sliders(false), float_panel(), int_panel() {
  scene_factory_functions.push_back(Introduction::Create);
  scene_factory_functions.push_back(Scene1::Create);
  scene_factory_functions.push_back(Scene2::Create);
  scene_factory_functions.push_back(Scene3::Create);
  scene_factory_functions.push_back(Scene4::Create);
  scene_factory_functions.push_back(Scene5::Create);
}

TextTennis::~TextTennis() {
  for (int i = 0; i < float_panel.getNumControls(); ++i) {
    delete float_panel.getControl(i);
  }
  float_panel.clear();
  for (int i = 0; i < int_panel.getNumControls(); ++i) {
    delete int_panel.getControl(i);
  }
  int_panel.clear();
}

void TextTennis::setup() {
  CreateScene();
  float_panel.setup("float parameters");
  for (auto parameter : Parameter<float>::GetParameters()) {
    float_panel.add(new Slider<float>(parameter));
  }
  int_panel.setup("int parameters", "settings.xml",
                  float_panel.getPosition().x + float_panel.getWidth() + 1);
  for (auto parameter : Parameter<int>::GetParameters()) {
    int_panel.add(new Slider<int>(parameter));
  }
}

void TextTennis::update() {
  if (current_scene) {
    current_scene->Update();
  }
}

void TextTennis::draw() {
  if (current_scene) {
    current_scene->Draw();
  }
  if (show_sliders) {
    ofSetRectMode(OF_RECTMODE_CORNER);
    float_panel.draw();
    int_panel.draw();
  }
}

void TextTennis::NextScene() {
  scene_index = (scene_index + 1) % scene_factory_functions.size();
  CreateScene();
}

void TextTennis::PreviousScene() {
  scene_index = (scene_index + scene_factory_functions.size() - 1) % scene_factory_functions.size();
  CreateScene();
}

void TextTennis::RestartScene() {
  CreateScene();
}

void TextTennis::ToggleSettings() {
  show_sliders = !show_sliders;
}

void TextTennis::CreateScene() {
  DeleteCurrentScene();
  current_scene = scene_factory_functions[scene_index](*this);
  current_scene->Setup();
}

void TextTennis::DeleteCurrentScene() {
  if (current_scene) {
    delete current_scene;
    current_scene = nullptr;
  }
}
