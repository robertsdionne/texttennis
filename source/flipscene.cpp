#include "scene.h"
#include "flipscene.h"
#include "texttennis.h"

FlipScene::FlipScene(TextTennis &scene_manager) : model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(static_cast<Controller *>(&controller));
  ofRegisterMouseEvents(static_cast<Controller *>(&controller));
}

FlipScene::~FlipScene() {
  ofUnregisterKeyEvents(static_cast<Controller *>(&controller));
  ofUnregisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene *FlipScene::Create(TextTennis &scene_manager) {
  return new FlipScene(scene_manager);
}

void FlipScene::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("FlipScene", 100, 100);
}

void FlipScene::Setup() {
  view.Setup();
  controller.Setup();
}

void FlipScene::Update() {
  controller.Update();
}
