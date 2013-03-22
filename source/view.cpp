#include "constants.h"
#include "model.h"
#include "view.h"

void View::Setup() const {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
}

void View::Draw(Model &model) const {
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  DrawCourt();
  DrawNet();
  if (model.rewinding) {
    DrawRacket(model.states.back().racket1);
    DrawRacket(model.states.back().racket2);
    for (auto ball : model.states.back().balls) {
      DrawBall(ball.position, ball.angle);
    }
  } else {
    DrawRacket(model.racket1);
    DrawRacket(model.racket2);
    for (auto ball : model.ball_body) {
      DrawBall(ofVec2f(ball->GetPosition().x, ball->GetPosition().y), ball->GetAngle());
    }
  }
  DrawFrameRate();
  ofPopMatrix();
}

void View::DrawBall(ofVec2f position, float angle) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, ball_radius);
  ofSetColor(ofColor::white);
  ofLine(position, position + ball_radius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void View::DrawCourt() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_court_length, court_thickness), court_length, -court_thickness);
  ofPopStyle();
}

void View::DrawFrameRate() const {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), -half_court_length, half_court_thickness);
  ofPopStyle();
}

void View::DrawNet() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_net_thickness, net_height + court_thickness), net_thickness, -net_height);
  ofPopStyle();
}

void View::DrawRacket(ofVec2f position) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, racket_radius);
  ofPopStyle();
}
