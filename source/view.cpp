#include "constants.h"
#include "model.h"
#include "view.h"

void View::Setup() const {
  ofSetFrameRate(param_frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
}

void View::Draw(Model &model) const {
  ofMultMatrix(param_view_matrix);
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
}

void View::DrawBall(ofVec2f position, float angle) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, param_ball_radius);
  ofSetColor(ofColor::white);
  ofLine(position, position + param_ball_radius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void View::DrawCourt() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-param_half_court_length, param_court_thickness), param_court_length, -param_court_thickness);
  ofPopStyle();
}

void View::DrawFrameRate() const {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), -param_half_court_length, param_half_court_thickness);
  ofPopStyle();
}

void View::DrawNet() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-param_half_net_thickness, param_net_height + param_court_thickness), param_net_thickness, -param_net_height);
  ofPopStyle();
}

void View::DrawRacket(ofVec2f position) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, param_racket_radius);
  ofPopStyle();
}
