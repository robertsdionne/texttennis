#include "constants.h"
#include "model.h"
#include "view.h"

void View::Setup() const {
  ofSetFrameRate(kFrameRate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
}

void View::Draw(Model &model) const {
  ofMultMatrix(kViewMatrix);
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
  ofCircle(position, kBallRadius);
  ofSetColor(ofColor::white);
  ofLine(position, position + kBallRadius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void View::DrawCourt() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-kHalfCourtLength, kCourtThickness), kCourtLength, -kCourtThickness);
  ofPopStyle();
}

void View::DrawFrameRate() const {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), -kHalfCourtLength, kHalfCourtThickness);
  ofPopStyle();
}

void View::DrawNet() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-kHalfNetThickness, kNetHeight + kCourtThickness), kNetThickness, -kNetHeight);
  ofPopStyle();
}

void View::DrawRacket(ofVec2f position) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, kRacketRadius);
  ofPopStyle();
}
