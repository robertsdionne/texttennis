#include "controller.h"
#include "model.h"
#include "texttennis.h"

Controller::Controller(TextTennis &scene_manager)
: scene_manager(scene_manager), buttons(), keys(), previous_buttons(), previous_keys() {}

bool Controller::AnyButtonPressed() {
  for (auto pair : buttons) {
    if (pair.second && !previous_buttons[pair.first]) {
      return true;
    }
  }
  return false;
}

bool Controller::AnyKeyPressed() {
  for (auto pair : keys) {
    if (pair.second && !previous_keys[pair.first]) {
      return true;
    }
  }
  return false;
}

void Controller::Update() {
  if (keys['`'] && !previous_keys['`']) {
    scene_manager.ToggleSettings();
  }
  if (keys['r'] && !previous_keys['r']) {
    scene_manager.RestartScene();
    return;
  }
  if (keys['['] && !previous_keys['[']) {
    scene_manager.PreviousScene();
    return;
  }
  if (keys[']'] && !previous_keys[']']) {
    scene_manager.NextScene();
    return;
  }
  previous_buttons = buttons;
  previous_keys = keys;
}

void Controller::keyPressed(ofKeyEventArgs &event) {
  keys[event.key] = true;
}

void Controller::keyReleased(ofKeyEventArgs &event) {
  keys[event.key] = false;
}

void Controller::mouseDragged(ofMouseEventArgs &event) {
  mouseMoved(event);
}

void Controller::mouseMoved(ofMouseEventArgs &event) {
  model().mouse_position = ofVec3f(event.x, event.y) * view_matrix_inverse;
}

void Controller::mousePressed(ofMouseEventArgs &event) {
  buttons[event.button] = true;
}

void Controller::mouseReleased(ofMouseEventArgs &event) {
  buttons[event.button] = false;
}
