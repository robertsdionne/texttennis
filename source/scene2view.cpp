#include "constants.h"
#include "model.h"
#include "scene2model.h"
#include "scene2view.h"

Scene2View::Scene2View()
: font() {
  bg.loadImage("500ball.png");
  font.loadFont(font_filename, 2, true, false, true, 0.0);
}

void Scene2View::Setup() {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
}

void Scene2View::Draw(Model &model) {
  Scene2Model &scene2_model = dynamic_cast<Scene2Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofSetColor(ofColor(255, 255, 255).lerp(ofColor::black, scene2_model.score / max_balls));
  bg.draw(0, 0);
  scene2_model.dialogue.Draw();
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  ofPushMatrix();
  ofScale(1, -1);
  ofPopMatrix();
  DrawCourt();
  DrawNet();
  DrawRacket(scene2_model.racket1);
  for (auto ball : scene2_model.ball_body) {
    DrawBall(scene2_model, ofVec2f(ball->GetPosition().x, ball->GetPosition().y),
             ball->GetFixtureList()->GetShape()->m_radius, ball->GetAngle());
  }
  DrawFrameRate();
  ofPopMatrix();
}

void Scene2View::DrawBall(Scene2Model &model, ofVec2f position, float radius, float angle) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, radius);
  ofSetColor(ofColor(255, 0, 0).lerp(ofColor::black, model.score / max_balls));
  //const ofVec2f beam = radius * ofVec2f(cos(angle), sin(angle));
  //ofLine(position, position - beam);
  //ofLine(position, position + beam);
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
