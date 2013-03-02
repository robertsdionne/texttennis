#include <iostream>

#include "vignettes.h"

void Vignettes::setup() {
  ofSetFrameRate(kFrameRate);
  ofBackground(ofColor::black);
  ofEnableAlphaBlending();
  background_alpha = 0.0;
  if (!image_crossroads.loadImage(kCrossroadsFilename)) {
    std::cout << "error loading " << kCrossroadsFilename << std::endl;
  }
  if (!image_man_left_0.loadImage(kManLeft0Filename)) {
    std::cout << "error loading " << kManLeft0Filename << std::endl;
  }
  if (!image_man_left_1.loadImage(kManLeft1Filename)) {
    std::cout << "error loading " << kManLeft1Filename << std::endl;
  }
  if (!image_man_left_2.loadImage(kManLeft2Filename)) {
    std::cout << "error loading " << kManLeft2Filename << std::endl;
  }
  if (!image_man_right_0.loadImage(kManRight0Filename)) {
    std::cout << "error loading " << kManRight0Filename << std::endl;
  }
  if (!image_man_right_1.loadImage(kManRight1Filename)) {
    std::cout << "error loading " << kManRight1Filename << std::endl;
  }
  if (!image_man_right_2.loadImage(kManRight2Filename)) {
    std::cout << "error loading " << kManRight2Filename << std::endl;
  }
  if (!image_signpost.loadImage(kSignpostFilename)) {
    std::cout << "error loading " << kSignpostFilename << std::endl;
  }
  if (!font_ubuntu_regular.loadFont(kUbuntuRegular, 18)) {
    std::cout << "error loading " << kUbuntuRegular << std::endl;
  }
  if (!font_ubuntu_mono_regular.loadFont(kUbuntuMonoRegular, 18)) {
    std::cout << "error loading " << kUbuntuMonoRegular << std::endl;
  }
}

void Vignettes::update() {
  if (background_alpha < kMaxAlpha) {
    background_alpha += kAlphaDelta;
  }
  previous_keys = keys;
}

void Vignettes::draw() {
  ofSetColor(ofColor::white, background_alpha);
  image_crossroads.draw(ofVec2f(), ofGetWidth(), ofGetHeight());
  ofSetColor(ofColor::white);
  font_ubuntu_mono_regular.drawString(kVignetteText, 100, 15);
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