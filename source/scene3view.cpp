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
    DrawOpponent(scene3_model);
  }
  DrawParticles(scene3_model);
  if (scene3_model.ball_body) {
    DrawBall(scene3_model, ofVec2f(scene3_model.ball_body->GetPosition().x,
                     scene3_model.ball_body->GetPosition().y),
             scene3_model.ball_body->GetAngle());
    if (scene3_model.opponent_index == 9) {
      DrawBall(scene3_model, ofVec2f(-scene3_model.ball_body->GetPosition().x,
                       scene3_model.ball_body->GetPosition().y),
               -scene3_model.ball_body->GetAngle(), true);
    }
  }
  if (scene3_model.opponent_index == 2 && (scene3_model.ball_in_play ||
                                           (scene3_model.angle > 0.0 && scene3_model.angle < 180.0))) {
    for (auto ball : scene3_model.extra_balls) {
      DrawBall(scene3_model, ofVec2f(ball->GetPosition().x, ball->GetPosition().y), ball->GetAngle());
    }
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
  ofPopMatrix();
}



void Scene3View::DrawParticles(Scene3Model &model) {
  ofSetRectMode(OF_RECTMODE_CENTER);
  int index = 0;
  for (auto particle : model.particles) {
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(particle.position.x, particle.position.y);
    ofRotateZ(ofRadToDeg(particle.angle));
    ofFill();
    ofEnableAlphaBlending();
    if (model.opponent_index == 3) {
      ofSetColor(ofColor(255, 255, 255).lerp(ofColor::black, ofNoise(ofGetElapsedTimef() + 10.0 * index)), particle.life * 255.0);
      ofRect(ofPoint(), 0.125, 0.25);
    } else if (model.opponent_index == 8) {
      ofSetColor(ofColor::white, particle.life * 128.0);
      ofRect(ofPoint(), 0.25 * particle.life, 0.25 * particle.life);
    } else if (model.opponent_index == 4) {
      ofSetColor(ofColor::white, particle.life * 128.0);
      ofScale(0.25, 0.25);
      ofTriangle(ofPoint(0.0, 0.1), ofPoint(0.0, -0.1), ofPoint(1.0, 0.0));
      ofTriangle(ofPoint(0.1, 0.0), ofPoint(-0.1, 0.0), ofPoint(0.0, 0.5));
    }
    ofPopMatrix();
    ofPopStyle();
    ++index;
  }
  ofSetRectMode(OF_RECTMODE_CORNER);
}

void Scene3View::DrawBall(Scene3Model &model, ofVec2f position, float angle, bool inverted) const {
  ofPushStyle();
  if (model.opponent_index == 7) {
    int index = 0;
    Scene3Model::Trail *previous = nullptr;
    for (auto &point : model.ball_trail) {
      if (previous) {
        ofVec2f offset0 = ofVec2f(0.0, 2.0 * delta_time * (model.ball_trail.size() - index));
        ofVec2f offset1 = ofVec2f(0.0, 2.0 * delta_time * (model.ball_trail.size() - (index + 1)));
        const float alpha = (1.0 - static_cast<float>(index) / max((float)ball_trail_length_scholar.GetValue(),
                                                                   (float)model.ball_trail.size())) * 255.0;
        ofSetColor(ofColor::white, alpha);
        ofLine(previous->position + offset0, point.position + offset1);
        if (point.text) {
          ofSetColor(ofColor::black, alpha);
          ofDrawBitmapString(point.text, point.position + offset1);
        }
      }
      index += 1;
      previous = &point;
    }
  }
  ofSetColor(inverted ? ofColor::black : ofColor::white);
  ofCircle(position, ball_radius);
  ofSetColor(inverted ? ofColor::white : ofColor::black);
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

void Scene3View::DrawRacket(ofVec2f position, bool inverted) const {
  ofPushStyle();
  ofSetColor(inverted ? ofColor::black : ofColor::white);
  ofCircle(position, racket_radius);
  ofPopStyle();
}

void Scene3View::DrawOpponent(const Scene3Model &model) const {
  ofPushStyle();
  switch (model.opponent_index) {
    case 3: {
      ofSetColor(ofColor::black);
      ofTriangle(model.opponent + ofVec2f(-1, -racket_radius),
                 model.opponent + ofVec2f(0, 1-racket_radius),
                 model.opponent + ofVec2f(1, -racket_radius));
      DrawRacket(model.opponent + ofVec2f(-2.0 * racket_radius, 0));
      DrawRacket(model.opponent);
      DrawRacket(model.opponent + ofVec2f(2.0 * racket_radius, 0));
      ofRect(model.opponent + ofVec2f(-2.0 * racket_radius, 0), 4.0 * racket_radius, -0.25 * racket_radius);
      break;
    }
    case 4: {
      if (model.glass_hits != 3) {
        ofSetColor(ofColor::white);
        ofRect(model.opponent + ofVec2f(-racket_radius, -racket_radius), 2.0 * racket_radius, 4.0 * racket_radius);
      }
      break;
    }
    case 8: {
      if (model.served) {
        DrawRacket(model.opponent + ofVec2f(0.0, 1.8 * racket_radius));
        DrawRacket(model.opponent);
      }
      break;
    }
    case 9: {
      DrawRacket(model.opponent, true);
      break;
    }
    default: {
      DrawRacket(model.opponent);
      break;
    }
  }
  ofPopStyle();
}

float Scene3View::HalfLambert(ofVec3f light, ofVec3f normal) {
  const float highlight = (-normal.dot(light) / 2.0 + 1.0 / 2.0);
  return highlight * highlight;
}
