#include "scene.h"
#include "Scene4.h"
#include "texttennis.h"

Scene4::Scene4(TextTennis &scene_manager) : model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(&controller);
  ofRegisterMouseEvents(&controller);
}

Scene4::~Scene4() {
  ofUnregisterKeyEvents(&controller);
  ofUnregisterMouseEvents(&controller);
}

Scene *Scene4::Create(TextTennis &scene_manager) {
  return new Scene4(scene_manager);
}

void Scene4::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("Scene 4", -half_court_length + 1.0, court_height - 1.0);
}

void Scene4::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene4::Update() {
  controller.Update();
}
