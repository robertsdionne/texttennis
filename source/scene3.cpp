#include "scene.h"
#include "Scene3.h"
#include "texttennis.h"

Scene3::Scene3(TextTennis &scene_manager) : model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(&controller);
  ofRegisterMouseEvents(&controller);
}

Scene3::~Scene3() {
  ofUnregisterKeyEvents(&controller);
  ofUnregisterMouseEvents(&controller);
}

Scene *Scene3::Create(TextTennis &scene_manager) {
  return new Scene3(scene_manager);
}

void Scene3::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("Scene 3", -half_court_length + 1.0, court_height - 1.0);
}

void Scene3::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene3::Update() {
  controller.Update();
}
