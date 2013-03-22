#include "scene.h"
#include "scene2.h"
#include "texttennis.h"

Scene2::Scene2(TextTennis &scene_manager) : model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(&controller);
  ofRegisterMouseEvents(&controller);
}

Scene2::~Scene2() {
  ofUnregisterKeyEvents(&controller);
  ofUnregisterMouseEvents(&controller);
}

Scene *Scene2::Create(TextTennis &scene_manager) {
  return new Scene2(scene_manager);
}

void Scene2::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("Scene 2", -half_court_length + 1.0, court_height - 1.0);
}

void Scene2::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene2::Update() {
  controller.Update();
}
