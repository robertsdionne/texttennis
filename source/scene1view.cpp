#include "constants.h"
#include "model.h"
#include "scene1model.h"
#include "scene1view.h"
#include "utilities.h"

void Scene1View::Setup() {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
}

void Scene1View::Draw(Model &model) {
  Scene1Model &scene1_model = dynamic_cast<Scene1Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  scene1_model.dialogue.Draw();
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  ofTranslate(0.0, court_height / 2.0);
  ofRotateZ(H01(scene1_model.rotation) * 180.0);
  ofTranslate(0.0, -court_height / 2.0);
  DrawCourt();
  DrawNet();
  DrawRacket(scene1_model.racket1);
  DrawRacket(scene1_model.racket2);
  if (scene1_model.ball_body) {
    DrawBall(ofVec2f(scene1_model.ball_body->GetPosition().x,
                     scene1_model.ball_body->GetPosition().y), scene1_model.ball_body->GetAngle());
  }
  DrawFrameRate();
  ofPopMatrix();
}

float Scene1View::H01(float t) {
  return -2 * t * t * t + 3 * t * t;
}

void Scene1View::DrawBall(ofVec2f position, float angle) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, ball_radius);
  ofSetColor(ofColor::white);
  ofLine(position, position + ball_radius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void Scene1View::DrawCourt() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_court_length, court_thickness), court_length, -court_thickness);
  ofPopStyle();
}

void Scene1View::DrawFrameRate() const {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), -half_court_length, half_court_thickness);
  ofPopStyle();
}

void Scene1View::DrawNet() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_net_thickness, net_height + court_thickness), net_thickness, -net_height);
  ofPopStyle();
}

void Scene1View::DrawRacket(ofVec2f position) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, racket_radius);
  ofPopStyle();
}
