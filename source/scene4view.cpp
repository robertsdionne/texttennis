#include <vector>

#include "constants.h"
#include "model.h"
#include "scene4model.h"
#include "scene4view.h"
#include "utilities.h"

Scene4View::Scene4View() : background() {
  background.loadImage("tree_bg_final.png");
  for (int i = 0; i < 5; ++i) {
    std::stringstream filename;
    filename << "tree" << (i + 1) << "_final.png";
    trees[i].loadImage(filename.str());
  }
}

void Scene4View::Setup() {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
}

void Scene4View::Draw(Model &model) {
  ofBackground(ofColor::white);
  Scene4Model &scene4_model = dynamic_cast<Scene4Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofSetColor(ofColor::white);
  background.draw(0, 0);
  const int offset = 54;
  ofSetColor(ofColor::darkGray, 25);
  if (scene4_model.score >= 1) {
    ofSetColor(ofColor::white);
  }
  trees[0].draw(870, 157);
  ofSetColor(ofColor::darkGray, 25);
  if (scene4_model.score >= 2) {
    ofSetColor(ofColor::white);
  }
  trees[1].draw(731+offset, 201);
  ofSetColor(ofColor::darkGray, 25);
  if (scene4_model.score >= 3) {
    ofSetColor(ofColor::white);
  }
  trees[2].draw(598+2*offset, 272);
  ofSetColor(ofColor::darkGray, 25);
  if (scene4_model.score >= 4) {
    ofSetColor(ofColor::white);
  }
  trees[3].draw(434+3*offset, 273);
  ofSetColor(ofColor::darkGray, 25);
  if (scene4_model.score >= 5) {
    ofSetColor(ofColor::white);
  }
  trees[4].draw(274+4*offset, 334);
  scene4_model.dialogue.Draw();
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  DrawCourt();
  DrawNet();
  DrawRacket(scene4_model.racket1);
  //DrawTreePeople(scene4_model);
  ofSetColor(ofColor::yellow);
  ofBeginShape();
  ofVertices(scene4_model.points);
  ofEndShape();
  if (scene4_model.ball_body) {
    DrawBall(scene4_model, ofVec2f(scene4_model.ball_body->GetPosition().x,
                     scene4_model.ball_body->GetPosition().y),
             scene4_model.ball_body->GetAngle());
  }
  DrawFrameRate();
  ofPopMatrix();
}

void Scene4View::DrawBall(Scene4Model &model, ofVec2f position, float angle) {
  ofPushStyle();
  ofNoFill();
  int index = 0;
  ofPoint *previous = nullptr;
  for (auto &point : model.ball_trail) {
    if (previous) {
      ofVec2f offset0 = ofVec2f(0.0, 0.0 * delta_time * model.time_scales[index - 1] * (model.ball_trail.size() - index));
      ofVec2f offset1 = ofVec2f(0.0, 0.0 * delta_time * model.time_scales[index - 1] * (model.ball_trail.size() - (index + 1)));
      ofVec2f noise0 = model.noise[index] * static_cast<float>(model.ball_trail.size() - index) / ball_trail_length;
      ofVec2f noise1 = model.noise[index + 1] * static_cast<float>(model.ball_trail.size() - (index + 1)) / ball_trail_length;
      ofSetColor(ofColor::white, static_cast<float>(index) / ball_trail_length * 255.0);
      if ((point - *previous).lengthSquared() < 5.0) {
        ofLine(*previous + offset0 + noise0, point + offset1 + noise1);
      }
    }
    index += 1;
    previous = &point;
  }
  ofFill();
  ofSetColor(ofColor::white);
  ofCircle(position, ball_radius);
  ofSetColor(ofColor::black);
  ofLine(position, position - ball_radius * ofVec2f(cos(angle), sin(angle)));
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
