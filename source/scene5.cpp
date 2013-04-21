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
  ofSetColor(ofColor::white);
  ofDrawBitmapString("She leaves, and she's back at her car, the 2-door. Hot inside. Hot outside.\nShe's happy living in Georgia. Her wife, her friends, God, everything,\na piece of perfection contained in cars, in children, in all the Saturday, Sunday, Monday.\nTime is trailing behind.\n\nDriving home, she's looking out at everything.\nPeople, computer stores, the structure of bush right outside the church.\nShe's aroused, taking in the world as a fragile and naive scene.\n\nShe's almost home, and she gets a text message:\n\"You want to play text tennis?\"\n\nY/N", 100, 100);
}

void Scene5::Setup() {
  view.Setup();
  controller.Setup();
}

void Scene5::Update() {
  controller.Update();
}
