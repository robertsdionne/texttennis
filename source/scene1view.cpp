#include "constants.h"
#include "model.h"
#include "scene1model.h"
#include "scene1view.h"

void Scene1View::Setup() const {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
}

void Scene1View::Draw(Model &model) const {
  Scene1Model &scene2_model = dynamic_cast<Scene1Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  DrawCourt();
  DrawNet();
  DrawRacket(scene2_model.racket1);
  DrawRacket(scene2_model.racket2);
  for (auto ball : scene2_model.ball_body) {
    DrawBall(ofVec2f(ball->GetPosition().x, ball->GetPosition().y), ball->GetAngle());
  }
  DrawFrameRate();
  ofPopMatrix();
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