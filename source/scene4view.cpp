#include "constants.h"
#include "model.h"
#include "scene4model.h"
#include "scene4view.h"
#include "utilities.h"

Scene4View::Scene4View() : background() {
  background.loadImage("tree_bg_final.png");
}

void Scene4View::Setup() {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
}

void Scene4View::Draw(Model &model) {
  Scene4Model &scene4_model = dynamic_cast<Scene4Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofSetColor(ofColor::white);
  background.draw(0, 0);
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  DrawCourt();
  DrawNet();
  DrawRacket(scene4_model.racket1);
  DrawTreePeople(scene4_model);
  if (scene4_model.ball_body) {
    DrawBall(ofVec2f(scene4_model.ball_body->GetPosition().x,
                     scene4_model.ball_body->GetPosition().y),
             scene4_model.ball_body->GetAngle());
  }
  DrawFrameRate();
  ofPopMatrix();
}

void Scene4View::DrawBall(ofVec2f position, float angle) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, ball_radius);
  ofSetColor(ofColor::white);
  ofLine(position, position + ball_radius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void Scene4View::DrawCourt() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_court_length, court_thickness), court_length, -court_thickness);
  ofPopStyle();
}

void Scene4View::DrawFrameRate() const {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), -half_court_length, half_court_thickness);
  ofPopStyle();
}

void Scene4View::DrawNet() const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_net_thickness, net_height + court_thickness), net_thickness, -net_height);
  ofPopStyle();
}

void Scene4View::DrawRacket(ofVec2f position) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, racket_radius);
  ofPopStyle();
}

void Scene4View::DrawTreePeople(Scene4Model &model) const {
  ofPushStyle();
  for (int i = 0; i < 5; ++i) {
    const float radius = model.tree_people[i]->GetFixtureList()->GetShape()->m_radius;
    ofSetColor(4 - i < model.score ? ofColor::royalBlue : ofColor::black);
    ofCircle(OpenFrameworksVector(model.tree_people[i]->GetPosition()), radius);
  }
  ofPopStyle();
}
