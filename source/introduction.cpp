#include "introduction.h"
#include "scene.h"
#include "texttennis.h"

Introduction::Introduction(TextTennis &scene_manager)
: model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(&controller);
  ofRegisterMouseEvents(&controller);
}

Introduction::~Introduction() {
  ofUnregisterKeyEvents(&controller);
  ofUnregisterMouseEvents(&controller);
}

Scene *Introduction::Create(TextTennis &scene_manager) {
  return new Introduction(scene_manager);
}

void Introduction::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("Introduction", 100, 100);
}

void Introduction::Setup() {
  view.Setup();
  controller.Setup();
}

void Introduction::Update() {
  controller.Update();
}
