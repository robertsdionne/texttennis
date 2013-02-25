#include "texttennis.h"

void TextTennis::setup() {
  ball = GameObject(kBallRadius, kBallMass, ofVec2f(7, 1));
  ofSetupScreenOrtho(kCourtLength, kCourtLength);
  ofSetFrameRate(30.0);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  racket1 = ofVec2f(-8, 1.5);
  racket2 = ofVec2f(8, 1.5);
}

void TextTennis::update() {
  UpdateRackets();
  Gravity();
  Damping();
  Accelerate(1.0 / 60.0);
  BorderCollide();
  RacketCollide();
  Inertia();
  BorderCollidePreserveImpulse();
  RacketCollidePreserveImpulse();
  trail.push_back(ball.position);
  if (trail.size() > kTrailSize) {
    trail.pop_front();
  }
  previous_keys = keys;
}

void TextTennis::UpdateRackets() {
  if (keys[OF_KEY_LEFT] && racket2.x > -kCourtLength / 2.0) {
    racket2.x -= kRacketSpeed;
  }
  if (keys[OF_KEY_RIGHT] && racket2.x < kCourtLength / 2.0) {
    racket2.x += kRacketSpeed;
  }
  if (keys[OF_KEY_UP] && racket2.y < 2.0) {
    racket2.y += kRacketSpeed;
  }
  if (keys[OF_KEY_DOWN] && racket2.y - kRacketRadius > kCourtThickness) {
    racket2.y -= kRacketSpeed;
  }
  if (keys['a'] && racket1.x > -kCourtLength / 2.0) {
    racket1.x -= kRacketSpeed;
  }
  if (keys['d'] && racket1.x < kCourtLength / 2.0) {
    racket1.x += kRacketSpeed;
  }
  if (keys['w'] && racket1.y < 2.0) {
    racket1.y += kRacketSpeed;
  }
  if (keys['s'] && racket1.y - kRacketRadius > kCourtThickness) {
    racket1.y -= kRacketSpeed;
  }
}

void TextTennis::Gravity() {
  ball.force += ofVec2f(0, -kGravity);
}

void TextTennis::Damping() {
  ball.force += -kDrag * ball.velocity();
}

void TextTennis::Accelerate(float dt) {
  ball.Accelerate(dt);
}

void TextTennis::BorderCollide() {
  if (ball.position.y - ball.radius - kCourtThickness < 0) {
    ball.position.y = ball.radius + kCourtThickness;
  }
  if (ball.position.x - ball.radius < -kCourtLength / 2.0) {
    ball.position.x = ball.radius - kCourtLength / 2.0;
  } else if (ball.position.x + ball.radius > kCourtLength / 2.0) {
    ball.position.x = kCourtLength / 2.0 - ball.radius;
  }
}

void TextTennis::RacketCollide() {
}

void TextTennis::Inertia() {
  ball.Inertia();
}

void TextTennis::BorderCollidePreserveImpulse() {
  if (ball.position.y - ball.radius - kCourtThickness < 0) {
    float vy = (ball.previous_position.y - ball.position.y) * kDamping;
    ball.position.y = ball.radius + kCourtThickness;
    ball.previous_position.y = ball.position.y - vy;
  }
  if (ball.position.x - ball.radius < -kCourtLength / 2.0) {
    float vx = (ball.previous_position.x - ball.position.x) * kDamping;
    ball.position.x = ball.radius - kCourtLength / 2.0;
    ball.previous_position.x = ball.position.x - vx;
  } else if (ball.position.x + ball.radius > kCourtLength / 2.0) {
    float vx = (ball.previous_position.x - ball.position.x) * kDamping;
    ball.position.x = kCourtLength / 2.0 - ball.radius;
    ball.previous_position.x = ball.position.x - vx;
  }
}

void TextTennis::RacketCollidePreserveImpulse() {
  if ((ball.position - racket1).length() < kBallRadius + kRacketRadius) {
    ball.previous_position.x = ball.position.x - (kHitMean + ofRandomf() * kHitVariance);
    ball.previous_position.y = ball.position.y - (kHitMean + ofRandomf() * kHitVariance) / 2.0;
  }
  if ((ball.position - racket2).length() < kBallRadius + kRacketRadius) {
    ball.previous_position.x = ball.position.x + (kHitMean + ofRandomf() * kHitVariance);
    ball.previous_position.y = ball.position.y - (kHitMean + ofRandomf() * kHitVariance) / 2.0;
  }
}

void TextTennis::draw() {
  ofBackground(ofColor::white);
  ofSetColor(ofColor::black);
  ofRect(TransformPosition(ofVec2f(-kCourtLength / 2.0, kCourtThickness)), TransformSize(kCourtLength), TransformSize(kCourtThickness));
  ofRect(TransformPosition(ofVec2f(-kNetThickness / 2.0, kNetHeight + kCourtThickness)), TransformSize(kNetThickness), TransformSize(kNetHeight));
  ofCircle(TransformPosition(racket1), TransformSize(kRacketRadius));
  ofCircle(TransformPosition(racket2), TransformSize(kRacketRadius));
  ofCircle(TransformPosition(ball.position), TransformSize(ball.radius));
  ofVec2f *previous = nullptr;
  float index = 0;
  for (ofVec2f &next : trail) {
    if (previous) {
      const ofVec2f offset0 = ofVec2f(0, (trail.size() - index) / 30.0);
      const ofVec2f offset1 = ofVec2f(0, (trail.size() - (index + 1)) / 30.0);
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