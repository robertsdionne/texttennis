#include "constants.h"
#include "model.h"
#include "scene5model.h"
#include "scene5view.h"

Scene5View::Scene5View()
: font() {
  font.loadFont(font_filename, 12, true, false, true, 0.0);
}

void Scene5View::Setup() {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
}

void Scene5View::Draw(Model &model) {
  Scene5Model &scene5_model = dynamic_cast<Scene5Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  ofPushMatrix();
  ofSetColor(ofColor::black);
  std::stringstream out;
  if (scene5_model.score < 10) {
    out << ' ';
  }
  out << fmod(scene5_model.score, 100.0f);
  ofScale(1.0, -1.0);
  font.drawStringAsShapes(out.str(), -8.5, -1);
  ofPopMatrix();
  DrawCourt();
  DrawNet();
  DrawRacket(scene5_model.racket1);
  DrawRacket(scene5_model.opponent);
  if (scene5_model.ball_body) {
    DrawBall(ofVec2f(scene5_model.ball_body->GetPosition().x,
                     scene5_model.ball_body->GetPosition().y),
             scene5_model.ball_body->GetAngle());
  }
  DrawFrameRate();
  ofPopMatrix();
}

void Scene5View::DrawBall(ofVec2f position, float angle) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, ball_radius);
  ofSetColor(ofColor::white);
  ofLine(position, position + ball_radius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void Scene5View::DrawCourt() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_court_length, court_thickness), court_length, -court_thickness);
  ofPopStyle();
}

void Scene5View::DrawFrameRate() const {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), -half_court_length, half_court_thickness);
  ofPopStyle();
}

void Scene5View::DrawNet() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_net_thickness, net_height + court_thickness), net_thickness, -net_height);
  ofPopStyle();
}

void Scene5View::DrawRacket(ofVec2f position) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, racket_radius);
  ofPopStyle();
}
