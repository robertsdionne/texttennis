#include "constants.h"
#include "scene5controller.h"
#include "model.h"
#include "ofMain.h"
#include "scene5model.h"
#include "texttennis.h"

Scene5Controller::Scene5Controller(TextTennis &scene_manager, Scene5Model &model)
: Controller(scene_manager), model_(model) {}

void Scene5Controller::Setup() {}

void Scene5Controller::Update() {
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
