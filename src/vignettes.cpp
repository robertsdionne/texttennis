#include <iostream>

#include "vignettes.h"

void Vignettes::setup() {
  ofSetFrameRate(kFrameRate);
  ofBackground(ofColor::black);
  ofEnableAlphaBlending();
  increase_background = true;
  background_alpha = 0.0;
  background = 0.0;
  text_cursor = 0;
  man = Man(image_man_left_0, image_man_left_1, image_man_left_2,
            image_man_right_0, image_man_right_1, image_man_right_2, ofVec2f());
  if (!image_cliffside.loadImage(kCliffsideFilename)) {
    std::cout << "error loading " << kCliffsideFilename << std::endl;
  }
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
  if (!sound_insanity_music.loadSound(kInsanityMusicFilename, true)) {
    std::cout << "error loading " << kInsanityMusicFilename << std::endl;
  }
  if (!font_ubuntu_regular.loadFont(kUbuntuRegular, 18)) {
    std::cout << "error loading " << kUbuntuRegular << std::endl;
  }
  if (!font_ubuntu_mono_regular.loadFont(kUbuntuMonoRegular, 18)) {
    std::cout << "error loading " << kUbuntuMonoRegular << std::endl;
  }
  image_cliffside.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  image_crossroads.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  image_man_left_0.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  image_man_left_1.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  image_man_left_2.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  image_man_right_0.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  image_man_right_1.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  image_man_right_2.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  image_signpost.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  sound_insanity_music.play();
}

void Vignettes::update() {
  if (background_alpha < kMaxAlpha && increase_background) {
    background_alpha += kAlphaDelta;
  }
  if (background_alpha >= kMaxAlpha && increase_background) {
    increase_background = false;
  }
  if (background_alpha > 0 && !increase_background) {
    ofBackground(ofColor::white);
    background_alpha -= 10.0 * kAlphaDelta;
  }
  if (ofGetFrameNum() % 7 == 0) {
    text_cursor += 1;
  }
  if (keys[OF_KEY_LEFT]) {
    man.Walk(ofVec2f(-1, 0));
  }
  if (keys[OF_KEY_RIGHT]) {
    man.Walk(ofVec2f(1, 0));
  }
  if (keys[OF_KEY_UP]) {
    man.Walk(ofVec2f(0, -1));
  }
  if (keys[OF_KEY_DOWN]) {
    man.Walk(ofVec2f(0, 1));
  }
  if (!(keys[OF_KEY_LEFT] || keys[OF_KEY_RIGHT] || keys[OF_KEY_UP] || keys[OF_KEY_DOWN])) {
    man.Stop();
  }
  previous_keys = keys;
}

void Vignettes::draw() {
  if (!increase_background) {
    ofSetColor(ofColor::white, 255.0 - background_alpha);
    image_cliffside.draw(ofVec2f(), ofGetWidth(), ofGetHeight());
  }
  ofSetColor(ofColor::white, background_alpha);
  image_crossroads.draw(ofVec2f(), ofGetWidth(), ofGetHeight());
  if (background_alpha > 0) {
    ofSetColor(ofColor::white);
    font_ubuntu_mono_regular.drawString(std::string(kVignetteText).substr(0, text_cursor), 150, 260);
  }
  man.Draw();
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