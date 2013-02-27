#include "describer.h"
#include "texttennis.h"

constexpr const char *TextTennis::kMessageBounce;

void TextTennis::setup() {
  //ofSetupScreenOrtho(kCourtLength, kCourtLength);
  ofSetFrameRate(GameObject::kFrameRate);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  states.push_back(GameState(GameObject(kBallRadius, kBallMass, ofVec2f(-7, 1)), false,
                             ofVec2f(-8, kCourtThickness + kRacketRadius), std::list<GameState::Trail>()));
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
    if (use_ai && ofGetFrameNum() % 1 == 0) {
      const ofVec2f start = ofVec2f(kCourtLength / 2.0, 1);
      const ofVec2f direction = (mouse_position - start).scale(1.5);
      states.back().balls.push_back(GameObject(kBallRadius, kBallMass, start));
      float skill = kHitVariance * ofRandomf();
      states.back().balls.back().previous_position.x = states.back().balls.back().position.x - (direction.x * kHitMean + skill);
      states.back().balls.back().previous_position.y = states.back().balls.back().position.y - (direction.y * kHitMean + skill);
    }
    GameState::Trail trail;
    states.back().trail.push_back(trail);
    UpdateRackets();
    Gravity();
    Damping();
    Accelerate(GameObject::kDeltaTime);
    NetCollide();
    Collide(false);
    BorderCollide();
    RacketCollide();
    Inertia();
    NetCollidePreserveImpulse();
    Collide(true);
    BorderCollidePreserveImpulse();
    RacketCollidePreserveImpulse();
    states.back().trail.back().position = states.back().balls.front().position;
    if (states.back().trail.size() > kTrailSize) {
      states.back().trail.pop_front();
    }
  }
  previous_keys = keys;
}

void TextTennis::UpdateRackets() {
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
  for (auto &ball : states.back().balls) {
    ball.force += ofVec2f(0, -kGravity);
  }
}

void TextTennis::Damping() {
  for (auto &ball : states.back().balls) {
    ball.force += -kDrag * ball.velocity();
  }
}

void TextTennis::Accelerate(float dt) {
  for (auto &ball : states.back().balls) {
    ball.Accelerate(dt);
  }
}

void TextTennis::Collide(bool preserve_impulse) {
  for (auto i = states.back().balls.begin(); i != states.back().balls.end(); ++i) {
    auto j = i;
    for (std::advance(j, 1); j != states.back().balls.end(); ++j) {
      Collide(preserve_impulse, *i, *j);
    }
  }
}

void TextTennis::Collide(bool preserve_impulse, GameObject &ball0, GameObject &ball1) {
  const ofVec2f ds = ball0.position - ball1.position;
  if (ds.length() < 2.0 * kBallRadius) {
    const float factor = (ds.length() - 2.0 * kBallRadius) / ds.length();
    ball0.position -= 0.5 * factor * ds;
    ball1.position += 0.5 * factor * ds;
    if (preserve_impulse) {
      ofVec2f v0 = ball0.position - ball0.previous_position;
      ofVec2f v1 = ball1.position - ball1.previous_position;
      const float f0 = kDamping * ds.dot(v0) / ds.lengthSquared();
      const float f1 = kDamping * ds.dot(v1) / ds.lengthSquared();
      v0 += f1 * ds - f0 * ds;
      v1 += f0 * ds - f1 * ds;
      ball0.previous_position = ball0.position - v0;
      ball1.previous_position = ball1.position - v1;
    }
  }
}

void TextTennis::BorderCollide() {
  for (auto &ball : states.back().balls) {
    if (ball.position.y - ball.radius < kCourtThickness) {
      ball.position.y = ball.radius + kCourtThickness;
    }
    if (ball.position.x - ball.radius < -kCourtLength / 2.0) {
      ball.position.x = ball.radius - kCourtLength / 2.0;
    } else if (ball.position.x + ball.radius > kCourtLength / 2.0) {
      ball.position.x = kCourtLength / 2.0 - ball.radius;
    }
  }
}

void TextTennis::NetCollide() {
  for (auto &ball : states.back().balls) {
    const ofVec2f net_top = ofVec2f(0, kCourtThickness + kNetHeight);
    const ofVec2f net_bottom = ofVec2f();
    const ofVec2f net_dir = net_top - net_bottom;
    const ofVec2f ball_dir = ball.position - ball.previous_position;
    const float t = ofVec3f(ball.previous_position - net_bottom).cross(ball_dir).z /
    ofVec3f(net_dir).cross(ball_dir).z;
    const float u = ofVec3f(ball.previous_position - net_bottom).cross(net_dir).z /
    ofVec3f(net_dir).cross(ball_dir).z;
    if (0 <= t && t <= 1 && 0 <= u && u <= 1 && !ball.collided_with_net) {
      ball.position = ball.previous_position + u * ball_dir;
      if (ball_dir.x <= 0) {
        ball.position.x += ball.radius;
      }
      if (ball_dir.x > 0) {
        ball.position.x -= ball.radius;
      }
    }
  }
}

void TextTennis::RacketCollide() {
  
}

void TextTennis::Inertia() {
  for (auto &ball : states.back().balls) {
    ball.Inertia();
  }
}

void TextTennis::BorderCollidePreserveImpulse() {
  for (auto &ball : states.back().balls) {
    if (ball.position.y - ball.radius < kCourtThickness) {
      float vy = (ball.previous_position.y - ball.position.y) * kDamping;
      ball.position.y = ball.radius + kCourtThickness;
      ball.previous_position.y = ball.position.y - vy;
      states.back().trail.back().text = kMessageBounce;
    }
    if (ball.position.x - ball.radius < -kCourtLength / 2.0) {
      float vx = (ball.previous_position.x - ball.position.x) * kDamping;
      ball.position.x = ball.radius - kCourtLength / 2.0;
      ball.previous_position.x = ball.position.x - vx;
      states.back().trail.back().text = kMessageOut;
    } else if (ball.position.x + ball.radius > kCourtLength / 2.0) {
      float vx = (ball.previous_position.x - ball.position.x) * kDamping;
      ball.position.x = kCourtLength / 2.0 - ball.radius;
      ball.previous_position.x = ball.position.x - vx;
      states.back().trail.back().text = kMessageOut;
    }
  }
}

void TextTennis::NetCollidePreserveImpulse() {
  for (auto &ball : states.back().balls) {
    const ofVec2f net_top = ofVec2f(0, kCourtThickness + kNetHeight);
    const ofVec2f net_bottom = ofVec2f();
    const ofVec2f net_dir = net_top - net_bottom;
    const ofVec2f ball_dir = ball.position - ball.previous_position;
    const float t = ofVec3f(ball.previous_position - net_bottom).cross(ball_dir).z /
    ofVec3f(net_dir).cross(ball_dir).z;
    const float u = ofVec3f(ball.previous_position - net_bottom).cross(net_dir).z /
    ofVec3f(net_dir).cross(ball_dir).z;
    if (0 <= t && t <= 1 && 0 <= u && u <= 1 && !ball.collided_with_net) {
      float vx = (ball.previous_position.x - ball.position.x) * kDamping;
      ball.position = ball.previous_position + u * ball_dir;
      if (ball_dir.x <= 0) {
        ball.position.x += ball.radius;
      }
      if (ball_dir.x > 0) {
        ball.position.x -= ball.radius;
      }
      ball.previous_position.x = ball.position.x - vx;
      ball.collided_with_net = true;
      states.back().trail.back().text = kMessageNet;
    } else {
      ball.collided_with_net = false;
    }
  }
}

void TextTennis::RacketCollidePreserveImpulse() {
  for (auto &ball : states.back().balls) {
    if ((ball.position - states.back().racket1).length() < kBallRadius + kRacketRadius) {
      const float dx = ball.position.x - ball.previous_position.x;
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
      ball.previous_position.x = ball.position.x - (kHitMean + skill);
      ball.previous_position.y = ball.position.y - (kHitMean + skill) / 2.0;
    }
  }
}

void TextTennis::draw() {
  ofBackground(ofColor::white);
  DrawTrail(states.back().trail);
  ofSetColor(ofColor::black);
  ofRect(TransformPosition(ofVec2f(-kCourtLength / 2.0, kCourtThickness)), TransformSize(kCourtLength), TransformSize(kCourtThickness));
  ofRect(TransformPosition(ofVec2f(-kNetThickness / 2.0, kNetHeight + kCourtThickness)), TransformSize(kNetThickness), TransformSize(kNetHeight));
  ofCircle(TransformPosition(states.back().racket1), TransformSize(kRacketRadius));
  for (auto &ball : states.back().balls) {
    ofCircle(TransformPosition(ball.position), TransformSize(ball.radius));
  }
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

ofVec2f TextTennis::TransformPositionInverse(ofVec2f position) {
  ofVec2f new_position = position;
  new_position.y = ofGetHeight() - new_position.y;
  new_position = new_position * kCourtLength / ofGetWidth() - ofVec2f(kCourtLength / 2.0, 0.0);
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
  mouse_position = TransformPositionInverse(ofVec2f(x, y));
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