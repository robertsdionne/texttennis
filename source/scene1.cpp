#include "scene1.h"

Scene1::Scene1() : model(), view(), controller(model) {
  ofRegisterKeyEvents(&controller);
  ofRegisterMouseEvents(&controller);
}

Scene1::~Scene1() {
  ofUnregisterKeyEvents(&controller);
  ofUnregisterMouseEvents(&controller);
}

void Scene1::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("Scene 1", -param_half_court_length + 1.0, param_court_height - 1.0);
}

void Scene1::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene1::Update() {
  controller.Update();
}
