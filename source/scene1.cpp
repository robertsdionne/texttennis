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
}

void Scene1::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene1::Update() {
  controller.Update();
}
