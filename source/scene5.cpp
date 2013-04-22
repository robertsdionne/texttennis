#include "scene.h"
#include "Scene5.h"
#include "texttennis.h"

Scene5::Scene5(TextTennis &scene_manager) : model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(static_cast<Controller *>(&controller));
  ofRegisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene5::~Scene5() {
  ofUnregisterKeyEvents(static_cast<Controller *>(&controller));
  ofUnregisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene *Scene5::Create(TextTennis &scene_manager, ofPoint player_position) {
  return new Scene5(scene_manager);
}

void Scene5::Draw() {
  view.Draw(model);
}

void Scene5::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene5::Update() {
  controller.Update();
}
