#include "controller.h"
#include "ofMain.h"

Controller::Controller()
: keys(), previous_keys() {}

void Controller::OnKeyPressed(int key) {
  keys[key] = true;
}

void Controller::OnKeyReleased(int key) {
  keys[key] = false;
}

void Controller::OnMouseDragged(int x, int y, int button) {
  OnMouseMoved(x, y);
}

void Controller::OnMouseMoved(int x, int y) {
  //model.mouse_position = ofVec3f(x, y) * kViewMatrixInverse;
}

void Controller::OnMousePressed(int x, int y, int button) {
  buttons[button] = true;
}

void Controller::OnMouseReleased(int x, int y, int button) {
  buttons[button] = false;
}

void Controller::Update() {
  previous_buttons = buttons;
  previous_keys = keys;
}

bool Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}
