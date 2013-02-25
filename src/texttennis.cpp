#include "texttennis.h"

void TextTennis::setup() {
  ofSetupScreenOrtho(kCourtLength, kCourtLength);
  ofSetFrameRate(30.0);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  states.push_back(GameState(GameObject(kBallRadius, kBallMass, ofVec2f(7, 1)), ofVec2f(-8, 1.5), ofVec2f(8, 1.5), std::list<ofVec2f>()));
}

void TextTennis::update() {
  if (keys['\t']) {
    if (states.size() > 1) {
      states.pop_back();
    }
  } else {
    states.push_back(states.back());
    UpdateRackets();
    Gravity();
    Damping();
    Accelerate(1.0 / 60.0);
    BorderCollide();
    RacketCollide();
    Inertia();
    BorderCollidePreserveImpulse();
    RacketCollidePreserveImpulse();
    states.back().trail.push_back(states.back().ball.position);
    if (states.back().trail.size() > kTrailSize) {
      states.back().trail.pop_front();
    }
  }
  previous_keys = keys;
}

void TextTennis::UpdateRackets() {
  if (keys[OF_KEY_LEFT] && states.back().racket2.x > -kCourtLength / 2.0) {
    states.back().racket2.x -= kRacketSpeed;
  }
  if (keys[OF_KEY_RIGHT] && states.back().racket2.x < kCourtLength / 2.0) {
    states.back().racket2.x += kRacketSpeed;
  }
  if (keys[OF_KEY_UP] && states.back().racket2.y < 2.0) {
    states.back().racket2.y += kRacketSpeed;
  }
  if (keys[OF_KEY_DOWN] && states.back().racket2.y - kRacketRadius > kCourtThickness) {
    states.back().racket2.y -= kRacketSpeed;
  }
  if (keys['a'] && states.back().racket1.x > -kCourtLength / 2.0) {
    states.back().racket1.x -= kRacketSpeed;
  }
  if (keys['d'] && states.back().racket1.x < kCourtLength / 2.0) {
    states.back().racket1.x += kRacketSpeed;
  }
  if (keys['w'] && states.back().racket1.y < 2.0) {
    states.back().racket1.y += kRacketSpeed;
  }
  if (keys['s'] && states.back().racket1.y - kRacketRadius > kCourtThickness) {
    states.back().racket1.y -= kRacketSpeed;
  }
}

void TextTennis::Gravity() {
  states.back().ball.force += ofVec2f(0, -kGravity);
}

void TextTennis::Damping() {
  states.back().ball.force += -kDrag * states.back().ball.velocity();
}

void TextTennis::Accelerate(float dt) {
  states.back().ball.Accelerate(dt);
}

void TextTennis::BorderCollide() {
  if (states.back().ball.position.y - states.back().ball.radius - kCourtThickness < 0) {
    states.back().ball.position.y = states.back().ball.radius + kCourtThickness;
  }
  if (states.back().ball.position.x - states.back().ball.radius < -kCourtLength / 2.0) {
    states.back().ball.position.x = states.back().ball.radius - kCourtLength / 2.0;
  } else if (states.back().ball.position.x + states.back().ball.radius > kCourtLength / 2.0) {
    states.back().ball.position.x = kCourtLength / 2.0 - states.back().ball.radius;
  }
}

void TextTennis::RacketCollide() {
}

void TextTennis::Inertia() {
  states.back().ball.Inertia();
}

void TextTennis::BorderCollidePreserveImpulse() {
  if (states.back().ball.position.y - states.back().ball.radius - kCourtThickness < 0) {
    float vy = (states.back().ball.previous_position.y - states.back().ball.position.y) * kDamping;
    states.back().ball.position.y = states.back().ball.radius + kCourtThickness;
    states.back().ball.previous_position.y = states.back().ball.position.y - vy;
  }
  if (states.back().ball.position.x - states.back().ball.radius < -kCourtLength / 2.0) {
    float vx = (states.back().ball.previous_position.x - states.back().ball.position.x) * kDamping;
    states.back().ball.position.x = states.back().ball.radius - kCourtLength / 2.0;
    states.back().ball.previous_position.x = states.back().ball.position.x - vx;
  } else if (states.back().ball.position.x + states.back().ball.radius > kCourtLength / 2.0) {
    float vx = (states.back().ball.previous_position.x - states.back().ball.position.x) * kDamping;
    states.back().ball.position.x = kCourtLength / 2.0 - states.back().ball.radius;
    states.back().ball.previous_position.x = states.back().ball.position.x - vx;
  }
}

void TextTennis::RacketCollidePreserveImpulse() {
  if ((states.back().ball.position - states.back().racket1).length() < kBallRadius + kRacketRadius) {
    states.back().ball.previous_position.x = states.back().ball.position.x - (kHitMean + ofRandomf() * kHitVariance);
    states.back().ball.previous_position.y = states.back().ball.position.y - (kHitMean + ofRandomf() * kHitVariance) / 2.0;
  }
  if ((states.back().ball.position - states.back().racket2).length() < kBallRadius + kRacketRadius) {
    states.back().ball.previous_position.x = states.back().ball.position.x + (kHitMean + ofRandomf() * kHitVariance);
    states.back().ball.previous_position.y = states.back().ball.position.y - (kHitMean + ofRandomf() * kHitVariance) / 2.0;
  }
}

void TextTennis::draw() {
  ofBackground(ofColor::white);
  ofSetColor(ofColor::black);
  ofRect(TransformPosition(ofVec2f(-kCourtLength / 2.0, kCourtThickness)), TransformSize(kCourtLength), TransformSize(kCourtThickness));
  ofRect(TransformPosition(ofVec2f(-kNetThickness / 2.0, kNetHeight + kCourtThickness)), TransformSize(kNetThickness), TransformSize(kNetHeight));
  ofCircle(TransformPosition(states.back().racket1), TransformSize(kRacketRadius));
  ofCircle(TransformPosition(states.back().racket2), TransformSize(kRacketRadius));
  ofCircle(TransformPosition(states.back().ball.position), TransformSize(states.back().ball.radius));
  ofVec2f *previous = nullptr;
  float index = 0;
  for (ofVec2f &next : states.back().trail) {
    if (previous) {
      const ofVec2f offset0 = ofVec2f(0, (states.back().trail.size() - index) / 30.0);
      const ofVec2f offset1 = ofVec2f(0, (states.back().trail.size() - (index + 1)) / 30.0);
      ofLine(TransformPosition(*previous + offset0), TransformPosition(next + offset1));
    }
    index += 1;
    previous = &next;
  };
}

ofVec2f TextTennis::TransformPosition(ofVec2f position) {
  ofVec2f new_position = (position + ofVec2f(kCourtLength / 2.0, 0.0)) * ofGetWidth() / kCourtLength;
  new_position.y = ofGetHeight() - new_position.y;
  return new_position;
}

float TextTennis::TransformSize(float size) {
  return size * ofGetWidth() / kCourtLength;
}

void TextTennis::keyPressed(int key) {
  keys[key] = true;
}

void TextTennis::keyReleased(int key) {
  keys[key] = false;
}

void TextTennis::mouseMoved(int x, int y) {

}

void TextTennis::mouseDragged(int x, int y, int button) {

}

void TextTennis::mousePressed(int x, int y, int button) {

}

void TextTennis::mouseReleased(int x, int y, int button) {

}

void TextTennis::windowResized(int w, int h) {

}

void TextTennis::gotMessage(ofMessage msg) {

}

void TextTennis::dragEvent(ofDragInfo dragInfo) { 

}