#include "constants.h"
#include "scene5controller.h"
#include "model.h"
#include "ofMain.h"
#include "scene5model.h"
#include "texttennis.h"

Scene5Controller::Scene5Controller(TextTennis &scene_manager, Scene5Model &model)
: Controller(scene_manager), model_(model) {}

void Scene5Controller::Setup() {
  scene_manager.GetMusic().TriggerTransition("scene5");
  model_.dialogue
      .Position("spot", ofPoint(100, 100))
      .Foreground(ofColor::white)
      .Background(ofColor(0, 0, 0, 0))
      .Speed(20.0)
      .Message(
               "She leaves, and she's back at her car, the 2-door. Hot inside. Hot outside.\nShe's happy living in Georgia. Her wife, her friends, God, everything,\na piece of perfection contained in cars, in children, in all the Saturday, Sunday, Monday.\nTime is trailing behind.\n\nDriving home, she's looking out at everything.\nPeople, computer stores, the structure of bush right outside the church.\nShe's aroused, taking in the world as a fragile and naive scene.\n\nShe's almost home, and she gets a text message:\n\"You want to play tennis?\"\n\nY/N", "spot");
}

void Scene5Controller::Update() {
  model_.dialogue.Update();
  if (keys['y'] && !previous_keys['y']) {
    scene_manager.NextScene();
    return;
  }
  if (keys['n'] && !previous_keys['n']) {
    exit(0);
    return;
  }
  Controller::Update();
}

Model &Scene5Controller::model() {
  return model_;
}
