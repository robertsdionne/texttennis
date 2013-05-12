#include "scene.h"
#include "Scene4.h"
#include "texttennis.h"

Scene4::Scene4(TextTennis &scene_manager, ofPoint player_position)
: model(player_position), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(static_cast<Controller *>(&controller));
  ofRegisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene4::~Scene4() {
  ofUnregisterKeyEvents(static_cast<Controller *>(&controller));
  ofUnregisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene *Scene4::Create(TextTennis &scene_manager, ofPoint player_position) {
  return new Scene4(scene_manager, player_position);
}

void Scene4::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
}

void Scene4::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene4::Update() {
  controller.Update();
}
