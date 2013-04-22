#include "constants.h"
#include "model.h"
#include "scene5model.h"
#include "scene5view.h"

Scene5View::Scene5View() : font() {
  font.loadFont(font_filename, 16, true, true, true, 0.0);
}

void Scene5View::Setup() {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
}

void Scene5View::Draw(Model &model) {
  ofBackground(ofColor::black);
  Scene5Model &scene5_model = dynamic_cast<Scene5Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  scene5_model.dialogue.Draw();
}
