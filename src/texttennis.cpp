#include "describer.h"
#include "texttennis.h"

constexpr const char *TextTennis::kMessageBounce;

void TextTennis::setup() {
  //ofSetupScreenOrtho(kCourtLength, kCourtLength);
  ofSetFrameRate(GameObject::kFrameRate);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  states.push_back(GameState(GameObject(kBallRadius, kBallMass, ofVec2f(7, 1)), false,
                             ofVec2f(-8, kCourtThickness + kRacketRadius), ofVec2f(8, kCourtThickness + kRacketRadius), std::list<GameState::Trail>()));
  show_console = false;
  show_text = false;
  use_ai = false;
}

void TextTennis::update() {
  if (keys['\t']) {
    if (states.size() > 1) {
      states.pop_back();
    }
  } else {
    if (ofGetFrameNum() % 2 == 1) {
      states.push_back(states.back());
    }
    if (ofGetFrameNum() % 60 == 1) {
      const Describer describer;
      std::string description = describer.Describe(states.back());
      console.Log(description);
    }
    GameState::Trail trail;
    states.back().trail.push_back(trail);
    UpdateRackets();
    Gravity();
    Damping();
    Accelerate(GameObject::kDeltaTime);
    BorderCollide();
    NetCollide();
    RacketCollide();
    Inertia();
    BorderCollidePreserveImpulse();
    NetCollidePreserveImpulse();
    RacketCollidePreserveImpulse();
    states.back().trail.back().position = states.back().ball.position;
    if (states.back().trail.size() > kTrailSize) {
      states.back().trail.pop_front();
    }
  }
  previous_keys = keys;
}

void TextTennis::UpdateRackets() {
  if (!use_ai) {
    if (keys[OF_KEY_LEFT] && states.back().racket2.x > kRacketSpeed + kRacketRadius) {
      states.back().racket2.x -= kRacketSpeed;
    }
    if (keys[OF_KEY_RIGHT] && states.back().racket2.x < kCourtLength / 2.0) {
      states.back().racket2.x += kRacketSpeed;
    }
  } else {
    float racket_delta = 0;
    if (states.back().ball.position.x > 0) {
      if ((states.back().ball.position - states.back().racket2).x < 0) {
        racket_delta = -kRacketSpeed * ofNoise(ofGetElapsedTimef());
      } else {
        racket_delta = kRacketSpeed * ofNoise(ofGetElapsedTimef());
      }
    } else {
      racket_delta = kRacketSpeed * ofSignedNoise(ofGetElapsedTimef());
    }
    if (racket_delta > 0 && states.back().racket2.x > kRacketSpeed + kRacketRadius) {
      states.back().racket2.x += racket_delta;
    }
    if (racket_delta < 0 && states.back().racket2.x < kCourtLength / 2.0) {
      states.back().racket2.x += racket_delta;
    }
  }
  if (keys['a'] && states.back().racket1.x > -kCourtLength / 2.0) {
    states.back().racket1.x -= kRacketSpeed;
  }
  if (keys['d'] && states.back().racket1.x < -kRacketSpeed - kRacketRadius) {
    states.back().racket1.x += kRacketSpeed;
  }
  if (keys[' '] && !previous_keys[' ']) {
    show_text = !show_text;
  }
  if (keys['`'] && !previous_keys['`']) {
    show_console = !show_console;
  }
  if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
    use_ai = !use_ai;
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
  if (states.back().ball.position.y - states.back().ball.radius < kCourtThickness) {
    states.back().ball.position.y = states.back().ball.radius + kCourtThickness;
  }
  if (states.back().ball.position.x - states.back().ball.radius < -kCourtLength / 2.0) {
    states.back().ball.position.x = states.back().ball.radius - kCourtLength / 2.0;
  } else if (states.back().ball.position.x + states.back().ball.radius > kCourtLength / 2.0) {
    states.back().ball.position.x = kCourtLength / 2.0 - states.back().ball.radius;
  }
}

void TextTennis::NetCollide() {
  const ofVec2f net_top = ofVec2f(0, kCourtThickness + kNetHeight);
  const ofVec2f net_bottom = ofVec2f();
  const ofVec2f net_dir = net_top - net_bottom;
  const ofVec2f ball_dir = states.back().ball.position - states.back().ball.previous_position;
  const float t = ofVec3f(states.back().ball.previous_position - net_bottom).cross(ball_dir).z /
  ofVec3f(net_dir).cross(ball_dir).z;
  const float u = ofVec3f(states.back().ball.previous_position - net_bottom).cross(net_dir).z /
  ofVec3f(net_dir).cross(ball_dir).z;
  if (0 <= t && t <= 1 && 0 <= u && u <= 1 && !states.back().collided_with_net) {
    states.back().ball.position = states.back().ball.previous_position + u * ball_dir;
    if (ball_dir.x <= 0) {
      states.back().ball.position.x += states.back().ball.radius;
    }
    if (ball_dir.x > 0) {
      states.back().ball.position.x -= states.back().ball.radius;
    }
  }
}

void TextTennis::RacketCollide() {
  
}

void TextTennis::Inertia() {
  states.back().ball.Inertia();
}

void TextTennis::BorderCollidePreserveImpulse() {
  if (states.back().ball.position.y - states.back().ball.radius < kCourtThickness) {
    float vy = (states.back().ball.previous_position.y - states.back().ball.position.y) * kDamping;
    states.back().ball.position.y = states.back().ball.radius + kCourtThickness;
    states.back().ball.previous_position.y = states.back().ball.position.y - vy;
    states.back().trail.back().text = kMessageBounce;
  }
  if (states.back().ball.position.x - states.back().ball.radius < -kCourtLength / 2.0) {
    float vx = (states.back().ball.previous_position.x - states.back().ball.position.x) * kDamping;
    states.back().ball.position.x = states.back().ball.radius - kCourtLength / 2.0;
    states.back().ball.previous_position.x = states.back().ball.position.x - vx;
    states.back().trail.back().text = kMessageOut;
  } else if (states.back().ball.position.x + states.back().ball.radius > kCourtLength / 2.0) {
    float vx = (states.back().ball.previous_position.x - states.back().ball.position.x) * kDamping;
    states.back().ball.position.x = kCourtLength / 2.0 - states.back().ball.radius;
    states.back().ball.previous_position.x = states.back().ball.position.x - vx;
    states.back().trail.back().text = kMessageOut;
  }
}

void TextTennis::NetCollidePreserveImpulse() {
  const ofVec2f net_top = ofVec2f(0, kCourtThickness + kNetHeight);
  const ofVec2f net_bottom = ofVec2f();
  const ofVec2f net_dir = net_top - net_bottom;
  const ofVec2f ball_dir = states.back().ball.position - states.back().ball.previous_position;
  const float t = ofVec3f(states.back().ball.previous_position - net_bottom).cross(ball_dir).z /
  ofVec3f(net_dir).cross(ball_dir).z;
  const float u = ofVec3f(states.back().ball.previous_position - net_bottom).cross(net_dir).z /
  ofVec3f(net_dir).cross(ball_dir).z;
  if (0 <= t && t <= 1 && 0 <= u && u <= 1 && !states.back().collided_with_net) {
    float vx = (states.back().ball.previous_position.x - states.back().ball.position.x) * kDamping;
    states.back().ball.position = states.back().ball.previous_position + u * ball_dir;
    if (ball_dir.x <= 0) {
      states.back().ball.position.x += states.back().ball.radius;
    }
    if (ball_dir.x > 0) {
      states.back().ball.position.x -= states.back().ball.radius;
    }
    states.back().ball.previous_position.x = states.back().ball.position.x - vx;
    states.back().collided_with_net = true;
    states.back().trail.back().text = kMessageNet;
  } else {
    states.back().collided_with_net = false;
  }
}

void TextTennis::RacketCollidePreserveImpulse() {
  if ((states.back().ball.position - states.back().racket1).length() < kBallRadius + kRacketRadius) {
    const float dx = states.back().ball.position.x - states.back().ball.previous_position.x;
    float skill = 0.0;
    if ((keys['a'] && dx < 0) || (keys['d'] && dx > 0)) {
      skill = -kHitVariance * ofRandomuf();
      states.back().trail.back().text = kMessageWeakVolley;
    } else if ((keys['a'] && dx > 0) || (keys['d'] && dx < 0)) {
      skill = kHitVariance * ofRandomuf();
      states.back().trail.back().text = kMessageStrongVolley;
    } else {
      skill = kHitVariance * ofRandomf();
      states.back().trail.back().text = kMessageVolley;
    }
    states.back().ball.previous_position.x = states.back().ball.position.x - (kHitMean + skill);
    states.back().ball.previous_position.y = states.back().ball.position.y - (kHitMean + skill) / 2.0;
  }
  if ((states.back().ball.position - states.back().racket2).length() < kBallRadius + kRacketRadius) {
    const float dx = states.back().ball.position.x - states.back().ball.previous_position.x;
    float skill = 0.0;
    if ((keys[OF_KEY_LEFT] && dx < 0) || (keys[OF_KEY_RIGHT] && dx > 0)) {
      skill = -kHitVariance * ofRandomuf();
      states.back().trail.back().text = kMessageWeakVolley;
    } else if ((keys[OF_KEY_LEFT] && dx > 0) || (keys[OF_KEY_RIGHT] && dx < 0)) {
      skill = kHitVariance * ofRandomuf();
      states.back().trail.back().text = kMessageStrongVolley;
    } else {
      skill = kHitVariance * ofRandomf();
      states.back().trail.back().text = kMessageVolley;
    }
    states.back().ball.previous_position.x = states.back().ball.position.x + (kHitMean + skill);
    states.back().ball.previous_position.y = states.back().ball.position.y - (kHitMean + skill) / 2.0;
  }
}

void TextTennis::draw() {
  ofBackground(ofColor::white);
  DrawTrail(states.back().trail);
  ofSetColor(ofColor::black);
  ofRect(TransformPosition(ofVec2f(-kCourtLength / 2.0, kCourtThickness)), TransformSize(kCourtLength), TransformSize(kCourtThickness));
  ofRect(TransformPosition(ofVec2f(-kNetThickness / 2.0, kNetHeight + kCourtThickness)), TransformSize(kNetThickness), TransformSize(kNetHeight));
  ofCircle(TransformPosition(states.back().racket1), TransformSize(kRacketRadius));
  ofCircle(TransformPosition(states.back().racket2), TransformSize(kRacketRadius));
  ofCircle(TransformPosition(states.back().ball.position), TransformSize(states.back().ball.radius));
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), 0, ofGetHeight());
  ofPopStyle();
  if (show_console) {
    console.Draw();
  }
}

void TextTennis::DrawTrail(const std::list<GameState::Trail> &trail) {
  const GameState::Trail *previous = nullptr;
  float index = 0;
  ofPushStyle();
  for (const GameState::Trail &next : trail) {
    if (previous) {
      const ofVec2f offset0 = ofVec2f(0, 2.0  * GameObject::kDeltaTime * (trail.size() - index));
      const ofVec2f offset1 = ofVec2f(0, 2.0  * GameObject::kDeltaTime * (trail.size() - (index + 1)));
      ofColor color;
      if (keys['\t']) {
        color = ofColor::black;
      } else {
        color = ofColor::white;
        color.lerp(ofColor::black, (trail.size() - index) / kTrailSize);
      }
      ofSetColor(color);
      ofLine(TransformPosition(previous->position + offset0), TransformPosition(next.position + offset1));
      if (show_text && next.text) {
        ofDrawBitmapString(next.text, TransformPosition(next.position + offset1) + ofVec2f(0, 10));
      }
    }
    index += 1;
    previous = &next;
  };
  ofPopStyle();
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