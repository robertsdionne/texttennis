#include "vignettes.h"

void Vignettes::setup() {
  ofBackground(ofColor::white);
}

void Vignettes::update() {
  previous_keys = keys;
}

void Vignettes::draw() {
  ofSetColor(ofColor::black);
  ofDrawBitmapString(kVignetteText, 0, 15);
}

void Vignettes::keyPressed(int key) {
  keys[key] = true;
}

void Vignettes::keyReleased(int key) {
  keys[key] = false;
}

void Vignettes::mouseMoved(int x, int y) {
}

void Vignettes::mouseDragged(int x, int y, int button) {
}

void Vignettes::mousePressed(int x, int y, int button) {
}

void Vignettes::mouseReleased(int x, int y, int button) {
}

void Vignettes::windowResized(int w, int h) {
}

void Vignettes::gotMessage(ofMessage msg) {
}

void Vignettes::dragEvent(ofDragInfo dragInfo) {
}