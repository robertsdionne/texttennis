#include <Box2D/Box2D.h>

#include "constants.h"
#include "introduction.h"
#include "scene.h"
#include "scene1.h"
#include "texttennis.h"

/**
 * Public method definitions.
 */
TextTennis::TextTennis()
: scene_factory_functions(), scene_index(0), current_scene(nullptr) {
  scene_factory_functions.push_back(Introduction::Create);
  scene_factory_functions.push_back(Scene1::Create);
}

void TextTennis::setup() {
  CreateScene();
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
