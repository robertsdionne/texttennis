#include "constants.h"
#include "model.h"
#include "scene3model.h"
#include "scene3view.h"

Scene3View::Scene3View()
: font() {
  font.loadFont(font_filename, 12, true, false, true, 0.0);
}

void Scene3View::Setup() {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
}

void Scene3View::Draw(Model &model) {
  Scene3Model &scene3_model = dynamic_cast<Scene3Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  DrawCourt();
  DrawNet();
  DrawRacket(scene3_model.racket1);
  for (auto ball : scene3_model.ball_body) {
    DrawBall(ofVec2f(ball->GetPosition().x, ball->GetPosition().y), ball->GetAngle());
  }
  ofSetColor(ofColor::black);
  std::stringstream out;
  if (scene3_model.score < 10) {
    out << ' ';
  }
  out << fmod(scene3_model.score, 100.0f);
  ofScale(1.0, -1.0);
  font.drawStringAsShapes(out.str(), -8.5, -1);
  DrawFrameRate();
  ofPopMatrix();
}

void Scene3View::DrawBall(ofVec2f position, float angle) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, ball_radius);
  ofSetColor(ofColor::white);
  ofLine(position, position + ball_radius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void Scene3View::DrawCourt() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_court_length, court_thickness), court_length, -court_thickness);
  ofPopStyle();
}

void Scene3View::DrawFrameRate() const {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), -half_court_length, half_court_thickness);
  ofPopStyle();
}

void Scene3View::DrawNet() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_net_thickness, net_height + court_thickness), net_thickness, -net_height);
  ofPopStyle();
}

void Scene3View::DrawRacket(ofVec2f position) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, racket_radius);
  ofPopStyle();
}
