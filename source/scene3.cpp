#include "scene.h"
#include "Scene3.h"
#include "texttennis.h"

Scene3::Scene3(TextTennis &scene_manager) : model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(static_cast<Controller *>(&controller));
  ofRegisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene3::~Scene3() {
  ofUnregisterKeyEvents(static_cast<Controller *>(&controller));
  ofUnregisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene *Scene3::Create(TextTennis &scene_manager) {
  return new Scene3(scene_manager);
}

void Scene3::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("Scene 3\nFace-off.\n\n\nA - left\nD - right\nW - hit high\nS - hit low", 100, 100);
}

void Scene3::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene3::Update() {
  controller.Update();
}
