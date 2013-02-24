#include "texttennis.h"

void TextTennis::setup() {
  ball = GameObject(kTennisBallRadius, kTennisBallMass);
}

void TextTennis::update() {
  ball.Accelerate(1.0 / ofGetFrameRate());
  ball.Inertia();
  previous_keys = keys;
}

void TextTennis::draw() {
  SetViewTransform();
  ofBackground(ofColor::white);
  ofSetColor(ofColor::black);
  ofCircle(ball.position, ball.radius);
}

void TextTennis::SetViewTransform() {
  const float inverse_aspect_ratio = static_cast<float>(ofGetHeight()) / ofGetWidth();
  ofScale(ofGetWidth() / 24.0, -ofGetWidth() / 24.0);
  ofTranslate(12.0, -12.0 * inverse_aspect_ratio);
}

void TextTennis::keyPressed(int key) {
  keys[key] = true;
}

void TextTennis::keyReleased(int key) {
  keys[key] = false;
}

void TextTennis::mouseMoved(int x, int y) {

}

void TextTennis::mouseDragged(int x, int y, int button) {

}

void TextTennis::mousePressed(int x, int y, int button) {

}

void TextTennis::mouseReleased(int x, int y, int button) {

}

void TextTennis::windowResized(int w, int h) {

}

void TextTennis::gotMessage(ofMessage msg) {

}

void TextTennis::dragEvent(ofDragInfo dragInfo) { 

}