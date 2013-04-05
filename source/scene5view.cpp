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
  ofBackground(ofColor::black);
}

void Scene5View::Draw(Model &model) {
  Scene5Model &scene5_model = dynamic_cast<Scene5Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofPushMatrix();
  std::string hi = std::string("Test test test");
  //font.drawStringAsShapes(hi, 20, 20);
  ofPopMatrix();

}
