#include "scene.h"
#include "scene2.h"
#include "texttennis.h"

Scene2::Scene2(TextTennis &scene_manager, ofPoint player_position)
: model(player_position), view(), controller(scene_manager, model) {
  ofRegisterKeyEvents(static_cast<Controller *>(&controller));
  ofRegisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene2::~Scene2() {
  ofUnregisterKeyEvents(static_cast<Controller *>(&controller));
  ofUnregisterMouseEvents(static_cast<Controller *>(&controller));
}

Scene *Scene2::Create(TextTennis &scene_manager, ofPoint player_position) {
  return new Scene2(scene_manager, player_position);
}

void Scene2::Draw() {
  view.Draw(model);
  ofSetColor(ofColor::black);
  ofDrawBitmapString("Scene 2\nPractice.\n\nLEFT - left\nRIGHT - right", 100, 100);
}

void Scene2::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene2::Update() {
  controller.Update();
}
