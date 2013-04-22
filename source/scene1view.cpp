#include "constants.h"
#include "model.h"
#include "scene1model.h"
#include "scene1view.h"
#include "utilities.h"

void Scene1View::Setup() {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  bg.loadImage("scene1.png");
  text.loadImage("scene1_titleImage_text.png");
  tennis.loadImage("scene1_titleImage_Tennis.png");
}

void Scene1View::Draw(Model &model) {
  ofBackground(ofColor(177));
  Scene1Model &scene1_model = dynamic_cast<Scene1Model &>(model);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofSetColor(ofColor::white);

  ofPushMatrix();
  ofMultMatrix(view_matrix);
  ofTranslate(0.0, court_height / 2.0);
  ofRotateZ(H01(scene1_model.rotation) * 180.0);
  ofTranslate(0.0, -court_height / 2.0);
  ofSetColor(ofColor::white);
  ofSetRectMode(OF_RECTMODE_CENTER);
  float scale = court_length / window_width;
  ofScale(scale, -scale);
  bg.draw(0, -half_court_height / scale);
  ofPopMatrix();
  ofSetRectMode(OF_RECTMODE_CORNER);

  ofPushMatrix();
  scale = scene1_model.title;
  ofTranslate(window_width / 2.0, window_height / 2.0);
  ofScale(scale, scale);
  ofSetRectMode(OF_RECTMODE_CENTER);
  ofSetColor(ofColor::white, scene1_model.title * 255.0);
  text.draw(Lerp(ofVec2f(0, 0), ofVec2f(0, -window_height / 4.0), scene1_model.title));
  tennis.draw(Lerp(ofVec2f(0, 0), ofVec2f(0.0, window_height / 4.0), scene1_model.title));
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofPopMatrix();
  ofPopMatrix();
  
  ofSetColor(ofColor::white);
  scene1_model.dialogue.Draw();
  
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  ofTranslate(0.0, court_height / 2.0);
  ofRotateZ(H01(scene1_model.rotation) * 180.0);
  ofTranslate(0.0, -court_height / 2.0);
  DrawCourt(scene1_model);
  DrawNet(scene1_model);
  DrawRacket(scene1_model.racket1);
  DrawRacket(scene1_model.racket2);
  if (scene1_model.ball_body) {
    DrawBall(ofVec2f(scene1_model.ball_body->GetPosition().x,
                     scene1_model.ball_body->GetPosition().y), scene1_model.ball_body->GetAngle());
  }
  DrawFrameRate();
  ofPopMatrix();
}

float Scene1View::H01(float t) const {
  return -2 * t * t * t + 3 * t * t;
}

void Scene1View::DrawBall(ofVec2f position, float angle) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, ball_radius);
  ofSetColor(ofColor::white);
  ofLine(position - ball_radius * ofVec2f(cos(angle), sin(angle)),
         position + ball_radius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void Scene1View::DrawCourt(Scene1Model &model) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-court_length + half_net_thickness, court_thickness), court_length, -10.0);
  ofSetColor(ofColor::black, H01(1.0 - model.platform) * 255.0);
  ofRect(ofVec2f(half_net_thickness, court_thickness), court_length, -10.0);
  ofSetColor(ofColor::black, H01(model.platform) * 255.0);
  ofRect(ofVec2f(-half_net_thickness, court_height - court_thickness), court_length, 10.0);
  ofPopStyle();
}

void Scene1View::DrawFrameRate() const {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), -half_court_length, half_court_thickness);
  ofPopStyle();
}

void Scene1View::DrawNet(Scene1Model &model) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-half_net_thickness, net_height + court_thickness), net_thickness, -net_height);
  ofSetColor(ofColor::black, H01(model.platform) * 255.0);
  ofRect(ofVec2f(-half_net_thickness, court_height - net_height - court_thickness), net_thickness, net_height);
  ofPopStyle();
}

void Scene1View::DrawRacket(ofVec2f position) const {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, racket_radius);
  ofPopStyle();
}
