#include "constants.h"
#include "model.h"
#include "scene2model.h"
#include "scene2view.h"

Scene2View::Scene2View()
: font() {
  font.loadFont(font_filename, 2, true, false, true, 0.0);
}

void Scene2View::Setup() {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
}

void Scene2View::Draw(Model &model) {
  Scene2Model &scene2_model = dynamic_cast<Scene2Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  ofPushMatrix();
  ofScale(1, -1);
  std::stringstream out;
  if (scene2_model.score < 100) {
    out << ' ';
  }
  if (scene2_model.score < 10) {
    out << ' ';
  }
  out << scene2_model.score << "/" << scene2_model.ball_body.size();
  font.drawStringAsShapes(out.str(), -2, -half_court_height);
  ofPopMatrix();
  DrawCourt();
  DrawNet();
  DrawRacket(scene2_model.racket1);
  for (auto ball : scene2_model.ball_body) {
    DrawBall(ofVec2f(ball->GetPosition().x, ball->GetPosition().y), ball->GetAngle());
  }
  DrawFrameRate();
  ofPopMatrix();
}

void Scene2View::DrawBall(ofVec2f position, float angle) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, ball_radius);
  ofSetColor(ofColor::white);
  ofLine(position, position + ball_radius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void Scene2View::DrawCourt() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_court_length, court_thickness), court_length, -court_thickness);
  ofPopStyle();
}

void Scene2View::DrawFrameRate() const {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), -half_court_length, half_court_thickness);
  ofPopStyle();
}

void Scene2View::DrawNet() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_net_thickness, net_height + court_thickness), net_thickness, -net_height);
  ofPopStyle();
}

void Scene2View::DrawRacket(ofVec2f position) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, racket_radius);
  ofPopStyle();
}
