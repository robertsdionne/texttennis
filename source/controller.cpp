#include "controller.h"
#include "model.h"
#include "texttennis.h"

Controller::Controller(TextTennis &scene_manager)
: scene_manager(scene_manager), buttons(), keys(), previous_buttons(), previous_keys() {}

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
