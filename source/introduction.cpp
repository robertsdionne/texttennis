#include "introduction.h"
#include "scene.h"
#include "texttennis.h"

Introduction::Introduction(TextTennis &scene_manager)
: model(), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(static_cast<Controller *>(&controller));
  ofRegisterMouseEvents(static_cast<Controller *>(&controller));
}

Introduction::~Introduction() {
  ofUnregisterKeyEvents(static_cast<Controller *>(&controller));
  ofUnregisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene *Introduction::Create(TextTennis &scene_manager, ofPoint player_position) {
  return new Introduction(scene_manager);
}

void Introduction::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("Introduction\nClick a box.\n\n", 100, 100);
}

void Introduction::Setup() {
  view.Setup();
  controller.Setup();
}

void Introduction::Update() {
  controller.Update();
}
