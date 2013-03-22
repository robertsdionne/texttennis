#include "scene.h"
#include "Scene5.h"
#include "texttennis.h"

Scene5::Scene5(TextTennis &scene_manager) : model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(&controller);
  ofRegisterMouseEvents(&controller);
}

Scene5::~Scene5() {
  ofUnregisterKeyEvents(&controller);
  ofUnregisterMouseEvents(&controller);
}

Scene *Scene5::Create(TextTennis &scene_manager) {
  return new Scene5(scene_manager);
}

void Scene5::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("Scene 5", -half_court_length + 1.0, court_height - 1.0);
}

void Scene5::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene5::Update() {
  controller.Update();
}
