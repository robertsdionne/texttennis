#include "constants.h"
#include "model.h"
#include "flipscenemodel.h"
#include "flipsceneview.h"

void FlipSceneView::Setup() {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
  for (int i = 0; i < 10; ++i) {
    std::stringstream top_filename, bottom_filename;
    top_filename << i << "_top.png";
    bottom_filename << i << "_bottom.png";
    top[i].loadImage(top_filename.str());
    bottom[i].loadImage(bottom_filename.str());
  }
}

void FlipSceneView::Draw(Model &model) {
  FlipSceneModel &flipscene_model = dynamic_cast<FlipSceneModel &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  ofImage &top_image = top[(flipscene_model.score + 1) % 10];
  ofImage &bottom_image = bottom[flipscene_model.score];
  ofSetColor(ofColor::white);
  top_image.draw(0.0, 2.0 * half_court_height, half_court_length, -half_court_height);
  bottom_image.draw(0.0, half_court_height, half_court_length, -half_court_height);
  ofPushMatrix();
  ofTranslate(0, half_court_height);
  ofRotateX(flipscene_model.angle);
  ofTranslate(0, -half_court_height);
  const ofVec3f normal = [flipscene_model] () {
    if (flipscene_model.angle < 90) {
      return ofVec3f(0, 0, 1);
    } else {
      return ofVec3f(0, 0, -1);
    }
  }();
  const ofVec3f rotated_normal = normal.rotated(flipscene_model.angle, ofVec3f(1, 0, 0));
  const ofVec3f light = ofVec3f(0, 0, -1).normalized();
  ofImage &image = flipscene_model.angle < 90 ? top[flipscene_model.score] : bottom[(flipscene_model.score + 1) % 10];
  const float offset = flipscene_model.angle < 90 ? half_court_height : 0.0;
  const float negate = flipscene_model.angle < 90 ? -1.0 : 1.0;
  ofSetColor(ofColor::white);
  if (flipscene_model.angle > 90) {
    ofRect(0.0, half_court_height, half_court_length, half_court_height);
    ofEnableAlphaBlending();
    const float alpha = 1 + ofVec3f(0, -1, 0).dot(rotated_normal);
    ofSetColor(ofColor::white, alpha * 255.0);
    image.draw(0.0, half_court_height + offset, half_court_length, negate * half_court_height);
    ofDisableAlphaBlending();
  } else {
    ofSetColor(HalfLambert(light, rotated_normal) * 255.0);
    image.draw(0.0, half_court_height + offset, half_court_length, negate * half_court_height);
  }
  ofPopMatrix();
  ofPopMatrix();
}

float FlipSceneView::HalfLambert(ofVec3f light, ofVec3f normal) {
  const float highlight = (-normal.dot(light) / 2.0 + 1.0 / 2.0);
  return highlight * highlight;
}
