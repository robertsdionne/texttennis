#include "scene.h"
#include "scene1.h"
#include "texttennis.h"

Scene1::Scene1(TextTennis &scene_manager) : model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(&controller);
  ofRegisterMouseEvents(&controller);
}

Scene1::~Scene1() {
  ofUnregisterKeyEvents(&controller);
  ofUnregisterMouseEvents(&controller);
}

Scene *Scene1::Create(TextTennis &scene_manager) {
  return new Scene1(scene_manager);
}

void Scene1::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("Scene 1", -half_court_length + 1.0, court_height - 1.0);
}

void Scene1::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene1::Update() {
  controller.Update();
}
