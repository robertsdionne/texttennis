#include "scene.h"
#include "scene1.h"
#include "texttennis.h"

Scene1::Scene1(TextTennis &scene_manager) : model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(static_cast<Controller *>(&controller));
  ofRegisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene1::~Scene1() {
  ofUnregisterKeyEvents(static_cast<Controller *>(&controller));
  ofUnregisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene *Scene1::Create(TextTennis &scene_manager, ofPoint player_position) {
  return new Scene1(scene_manager);
}

void Scene1::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
}

void Scene1::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene1::Update() {
  controller.Update();
}
