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
  for (int i = 0; i < 10; ++i) {
    std::stringstream filename;
    filename << i << ".png";
    ofImage image;
    image.loadImage(filename.str());
    top[i].cropFrom(image, 0, 0, 1024, 320);
    bottom[i].cropFrom(image, 0, 320, 1024, 320);
  }
}

void Scene3View::Draw(Model &model) {
  ofBackground(ofColor::black);
  Scene3Model &scene3_model = dynamic_cast<Scene3Model &>(model);

  ofSetRectMode(OF_RECTMODE_CORNER);
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  ofImage &top_image = top[(scene3_model.score) % 10];
  int index = scene3_model.angle >= 180.0 ? 1 : 0;
  ofImage &bottom_image = bottom[(scene3_model.score + index - 1) % 10];
  ofSetColor(ofColor::white);
  top_image.draw(-half_court_length, court_height, court_length, -half_court_height);
  bottom_image.draw(-half_court_length, half_court_height, court_length, -half_court_height);

  DrawCourt();
  DrawNet();
  DrawRacket(scene3_model.racket1);
  if (scene3_model.ball_in_play || (scene3_model.angle > 0.0 && scene3_model.angle < 180.0)) {
    DrawOpponent(scene3_model.opponent, scene3_model.opponent_index);
  }
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
      ofRect(-half_court_length, half_court_height, court_length, half_court_height);
      ofEnableAlphaBlending();
      const float alpha = 1 + ofVec3f(0, -1, 0).dot(rotated_normal);
      ofSetColor(ofColor::white, alpha * 255.0);
      image.draw(-half_court_length, half_court_height + offset, court_length, negate * half_court_height);
      ofDisableAlphaBlending();
    } else {
      ofSetColor(HalfLambert(light, rotated_normal) * 255.0);
      image.draw(-half_court_length, half_court_height + offset, court_length, negate * half_court_height);
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

void Scene3View::DrawOpponent(ofVec2f position, int opponent_index) const {
  ofPushStyle();
  switch (opponent_index) {
    case 3: {
      ofSetColor(ofColor::black);
      ofTriangle(position + ofVec2f(-1, -racket_radius),
                 position + ofVec2f(0, 1-racket_radius),
                 position + ofVec2f(1, -racket_radius));
      DrawRacket(position + ofVec2f(-2.0 * racket_radius, 0));
      DrawRacket(position);
      DrawRacket(position + ofVec2f(2.0 * racket_radius, 0));
      ofRect(position + ofVec2f(-2.0 * racket_radius, 0), 4.0 * racket_radius, -0.25 * racket_radius);
      break;
    }
    case 8: {
      break;
    }
    default: {
      DrawRacket(position);
      break;
    }
  }
  ofPopStyle();
}

float Scene3View::HalfLambert(ofVec3f light, ofVec3f normal) {
  const float highlight = (-normal.dot(light) / 2.0 + 1.0 / 2.0);
  return highlight * highlight;
}
