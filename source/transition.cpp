#include "constants.h"
#include "transition.h"

Transition::Transition(ofImage &from, ofImage &to) : angle() {
  from_top.cropFrom(from, 0, 0, window_width, window_height / 2.0);
  from_top.reloadTexture();
  from_bottom.cropFrom(from, 0, window_height / 2.0, window_width, window_height / 2.0);
  from_bottom.reloadTexture();
  to_top.cropFrom(to, 0, 0, window_width, window_height / 2.0);
  to_top.reloadTexture();
  to_bottom.cropFrom(to, 0, window_height / 2.0, window_width, window_height / 2.0);
  to_bottom.reloadTexture();
}

void Transition::Draw() {
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  ofImage &top_image = to_top;
  ofImage &bottom_image = from_bottom;
  ofBackground(ofColor::black);
  ofSetColor(ofColor::white);
  top_image.draw(-half_court_length, 2.0 * half_court_height, court_length, -half_court_height);
  bottom_image.draw(-half_court_length, half_court_height, court_length, -half_court_height);

  if (0.0 <= angle && angle <= 180.0) {
    ofPushMatrix();
    ofTranslate(0, half_court_height);
    ofRotateX(angle);
    ofTranslate(0, -half_court_height);
    ofVec3f normal = angle < 90 ? ofVec3f(0, 0, 1) : ofVec3f(0, 0, -1);
    const ofVec3f rotated_normal = normal.rotated(angle, ofVec3f(1, 0, 0));
    const ofVec3f light = ofVec3f(0, 0, -1).normalized();
    ofImage &image = angle < 90 ? from_top : to_bottom;
    const float offset = angle < 90 ? half_court_height : 0.0;
    const float negate = angle < 90 ? -1.0 : 1.0;
    if (angle > 90) {
      ofSetColor(ofColor::white);
      ofRect(-half_court_length, half_court_height, court_length, half_court_height);
      ofEnableAlphaBlending();
      const float alpha = 1 + ofVec3f(0, -1, 0).dot(rotated_normal);
      ofSetColor(ofColor::white, alpha * 255.0);
      image.draw(-half_court_length, half_court_height + offset, court_length, negate * half_court_height);
      ofDisableAlphaBlending();
    } else {
      ofSetColor(ofColor::black);
      ofRect(-half_court_length, half_court_height + offset, court_length, negate * half_court_height);
      ofSetColor(HalfLambert(light, rotated_normal) * 255.0);
      image.draw(-half_court_length, half_court_height + offset, court_length, negate * half_court_height);
    }
    ofPopMatrix();
  }
  ofPopMatrix();
}

bool Transition::IsDone() {
  return angle >= 180.0;
}

void Transition::Setup() {
  
}

void Transition::Update() {
  if (angle <= 180.0 - 180.0 / 60.0 / 2.0) {
    angle += 180.0 / 60.0 / 2.0;
  }
}

float Transition::HalfLambert(ofVec3f light, ofVec3f normal) {
  const float highlight = (-normal.dot(light) / 2.0 + 1.0 / 2.0);
  return highlight * highlight;
}
