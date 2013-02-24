#include "texttennis.h"

void TextTennis::setup() {
  ball = GameObject(kBallRadius, kBallMass, ofVec2f(0, 10), ofVec2f(100, 25));
  ofSetupScreenOrtho(kCourtLength, kCourtLength);
  ofSetFrameRate(30.0);
}

void TextTennis::update() {
  Gravity();
  Damping();
  Accelerate(1.0 / 60.0);
  BorderCollide();
  Inertia();
  BorderCollidePreserveImpulse();
  previous_keys = keys;
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

void TextTennis::draw() {
  ofBackground(ofColor::white);
  ofSetColor(ofColor::black);
  ofCircle(TransformPosition(ball.position), TransformSize(ball.radius));
  ofRect(TransformPosition(ofVec2f(-kCourtLength / 2.0, kCourtThickness)), TransformSize(kCourtLength), TransformSize(kCourtThickness));
  ofRect(TransformPosition(ofVec2f(-kNetThickness / 2.0, kNetHeight + kCourtThickness)), TransformSize(kNetThickness), TransformSize(kNetHeight));
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