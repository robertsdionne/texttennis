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
  ofBackground(ofColor::black);
  for (int i = 0; i < 10; ++i) {
    std::stringstream top_filename, bottom_filename;
    top_filename << i << "_top_inverted.png";
    bottom_filename << i << "_bottom_inverted.png";
    top[i].loadImage(top_filename.str());
    bottom[i].loadImage(bottom_filename.str());
  }
}

void Scene3View::Draw(Model &model) {
  Scene3Model &scene3_model = dynamic_cast<Scene3Model &>(model);

  ofSetRectMode(OF_RECTMODE_CORNER);
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  ofImage &top_image = top[(scene3_model.score) % 10];
  int index = scene3_model.angle >= 180.0 ? 1 : 0;
  ofImage &bottom_image = bottom[(scene3_model.score + index - 1) % 10];
  ofSetColor(ofColor::white);
  top_image.draw(0.0, 2.0 * half_court_height, half_court_length, -half_court_height);
  bottom_image.draw(0.0, half_court_height, half_court_length, -half_court_height);

  DrawCourt();
  DrawNet();
  DrawRacket(scene3_model.racket1);
  DrawRacket(scene3_model.opponent);
  ofPopMatrix();

  scene3_model.dialogue.Draw();

  ofPushMatrix();
  ofMultMatrix(view_matrix);
  if (0.0 <= scene3_model.angle && scene3_model.angle < 180.0) {
    ofPushMatrix();
    ofTranslate(0, half_court_height);
    ofRotateX(scene3_model.angle);
    ofTranslate(0, -half_court_height);
    ofVec3f normal = scene3_model.angle < 90 ? ofVec3f(0, 0, 1) : ofVec3f(0, 0, -1);
    const ofVec3f rotated_normal = normal.rotated(scene3_model.angle, ofVec3f(1, 0, 0));
    const ofVec3f light = ofVec3f(0, 0, -1).normalized();
    ofImage &image = scene3_model.angle < 90 ? top[(scene3_model.score - 1) % 10] : bottom[(scene3_model.score) % 10];
    const float offset = scene3_model.angle < 90 ? half_court_height : 0.0;
    const float negate = scene3_model.angle < 90 ? -1.0 : 1.0;
    ofSetColor(ofColor::white);
    if (scene3_model.angle > 90) {
      ofRect(0.0, half_court_height, half_court_length, half_court_height);
      ofEnableAlphaBlending();
      const float alpha = 1 + ofVec3f(0, -1, 0).dot(rotated_normal);
      ofSetColor(ofColor::white, alpha * 255.0);
      image.draw(0.0, half_court_height + offset, half_court_length, negate * half_court_height);
      ofDisableAlphaBlending();
    } else {
      ofSetColor(HalfLambert(light, rotated_normal) * 255.0);
      image.draw(0.0, half_court_height + offset, half_court_length, negate * half_court_height);
    }
    ofPopMatrix();
  }
  if (scene3_model.ball_body) {
    DrawBall(ofVec2f(scene3_model.ball_body->GetPosition().x,
                     scene3_model.ball_body->GetPosition().y),
             scene3_model.ball_body->GetAngle());
  }
  DrawFrameRate();
  ofPopMatrix();
}

void Scene3View::DrawBall(ofVec2f position, float angle) const {
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofCircle(position, ball_radius);
  ofSetColor(ofColor::black);
  ofLine(position, position + ball_radius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void Scene3View::DrawCourt() const {
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofRect(ofVec2f(-half_court_length, court_thickness), court_length, -court_thickness);
  ofPopStyle();
}

void Scene3View::DrawFrameRate() const {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofDrawBitmapString(out.str(), -half_court_length, half_court_thickness);
  ofPopStyle();
}

void Scene3View::DrawNet() const {
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofRect(ofVec2f(-half_net_thickness, net_height + court_thickness), net_thickness, -net_height);
  ofPopStyle();
}

void Scene3View::DrawRacket(ofVec2f position) const {
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofCircle(position, racket_radius);
  ofPopStyle();
}

float Scene3View::HalfLambert(ofVec3f light, ofVec3f normal) {
  const float highlight = (-normal.dot(light) / 2.0 + 1.0 / 2.0);
  return highlight * highlight;
}
