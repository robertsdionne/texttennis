#include "constants.h"
#include "flipscenecontroller.h"
#include "model.h"
#include "ofMain.h"
#include "flipscenemodel.h"
#include "texttennis.h"
#include "utilities.h"

FlipSceneController::FlipSceneController(TextTennis &scene_manager, FlipSceneModel &model)
: Controller(scene_manager), model_(model) {
}

FlipSceneController::~FlipSceneController() {
}

void FlipSceneController::Setup() {
}

void FlipSceneController::Update() {
  if (model_.angle < 180.0) {
    model_.angle += 180.0 / 1.0 / 60.0;
  }
  if (keys[' '] && !previous_keys[' ']) {
    model_.angle = 0.0;
    model_.score = (model_.score + 1) % 10;
  }
  Controller::Update();
}

Model &FlipSceneController::model() {
  return model_;
}
