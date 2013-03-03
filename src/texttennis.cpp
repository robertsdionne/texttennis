#include <Box2D/Box2D.h>

#include "describer.h"
#include "texttennis.h"

const b2Vec2 TextTennis::kGravityVector = b2Vec2(0.0, -9.81 / 2.0);
constexpr const char *TextTennis::kMessageBounce;

TextTennis::TextTennis()
: world(kGravityVector) {}

void TextTennis::setup() {
  ofSetFrameRate(GameObject::kFrameRate);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  
  racket1 = ofVec2f(-8, kCourtThickness + kRacketRadius);
  show_console = false;
  show_text = false;
  use_ai = false;
  
  // Box2D
  ball_body_definition.type = b2_dynamicBody;
  ball_body_definition.position.Set(11, 1);
  ball_body_definition.linearVelocity.Set(-10, 5);
  ball_body_definition.linearDamping = 0.1;
  ball_body_definition.angularDamping = 0.1;
  ball_body.push_back(world.CreateBody(&ball_body_definition));
  ball_shape.m_radius = kBallRadius;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = 1.0;
  ball_fixture_definition.restitution = 0.728;
  ball_fixture_definition.friction = 0.3;
  ball_fixture = ball_body.back()->CreateFixture(&ball_fixture_definition);
  
  court_body_definition.position.Set(0.0, kCourtThickness / 2.0);
  court_body = world.CreateBody(&court_body_definition);
  court_shape.SetAsBox(kCourtLength / 2.0, kCourtThickness / 2.0);
  court_fixture_definition.shape = &court_shape;
  court_fixture_definition.friction = 0.3;
  court_fixture = court_body->CreateFixture(&court_fixture_definition);
  
  net_body_definition.position.Set(0.0, kCourtThickness);
  net_body = world.CreateBody(&net_body_definition);
  net_shape.Set(b2Vec2(), b2Vec2(0.0, kNetHeight));
  net_fixture_definition.shape = &net_shape;
  net_fixture = net_body->CreateFixture(&net_fixture_definition);
  
  border_body_definition.position.Set(0.0, kCourtThickness);
  border_body = world.CreateBody(&border_body_definition);
  b2Vec2 vertices[4];
  vertices[0].Set(-kCourtLength / 2.0, 0.0);
  vertices[1].Set(-kCourtLength / 2.0, 100.0);
  vertices[2].Set(kCourtLength / 2.0, 100.0);
  vertices[3].Set(kCourtLength / 2.0, 0.0);
  border_shape.CreateChain(vertices, 4);
  border_fixture_definition.shape = &border_shape;
  border_fixture = border_body->CreateFixture(&border_fixture_definition);
}

void TextTennis::update() {
  if (!keys['\t']) {
    UpdateRackets();
    RacketCollide();
    world.Step(GameObject::kDeltaTime, kBox2dVelocityIterations, kBox2dPositionIterations);
    if (use_ai && ofGetFrameNum() % 120 == 0) {
      ball_body.push_back(world.CreateBody(&ball_body_definition));
      b2Vec2 mouse = b2Vec2(mouse_position.x, mouse_position.y) - b2Vec2(11, 1);
      mouse.Normalize();
      mouse *= 12.0;
      ball_body_definition.linearVelocity = mouse;
      ball_fixture = ball_body.back()->CreateFixture(&ball_fixture_definition);
      if (ball_body.size() > kMaxBalls) {
        b2Body *const body = ball_body.front();
        body->DestroyFixture(body->GetFixtureList());
        world.DestroyBody(body);
        ball_body.pop_front();
      }
    }
  }
  previous_keys = keys;
}

void TextTennis::UpdateRackets() {
  if (keys['a'] && racket1.x > -kCourtLength / 2.0) {
    racket1.x -= kRacketSpeed;
  }
  if (keys['d'] && racket1.x < -kRacketSpeed - kRacketRadius) {
    racket1.x += kRacketSpeed;
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

void TextTennis::RacketCollide() {
  for (auto ball : ball_body) {
    const ofVec2f position = ofVec2f(ball->GetPosition().x, ball->GetPosition().y);
    const float dx = ball->GetLinearVelocity().x;
    if ((position - racket1).length() < kBallRadius + kRacketRadius) {
      float skill = 0.0;
      if ((keys['a'] && dx < 0) || (keys['d'] && dx > 0)) {
        skill = -kHitVariance * ofRandomuf();
      } else if ((keys['a'] && dx > 0) || (keys['d'] && dx < 0)) {
        skill = kHitVariance * ofRandomuf();
      } else {
        skill = kHitVariance * ofRandomf();
      }
      ball->SetLinearVelocity(50.0 * b2Vec2(kHitMean + skill, (kHitMean + skill) / 2.0));
    }
  }
}

void TextTennis::draw() {
  ofBackground(ofColor::white);
  ofSetColor(ofColor::black);
  ofRect(TransformPosition(ofVec2f(-kCourtLength / 2.0, kCourtThickness)), TransformSize(kCourtLength), TransformSize(kCourtThickness));
  ofRect(TransformPosition(ofVec2f(-kNetThickness / 2.0, kNetHeight + kCourtThickness)), TransformSize(kNetThickness), TransformSize(kNetHeight));
  ofCircle(TransformPosition(racket1), TransformSize(kRacketRadius));
  for (auto ball : ball_body) {
    const float angle = ball->GetAngle();
    const b2Vec2 position = ball->GetPosition();
    ofSetColor(ofColor::black);
    ofCircle(TransformPosition(ofVec2f(position.x, position.y)), TransformSize(kBallRadius));
    ofSetColor(ofColor::white);
    ofLine(TransformPosition(ofVec2f(position.x, position.y)),
           TransformPosition(ofVec2f(position.x, position.y) + kBallRadius * ofVec2f(cos(angle), sin(angle))));
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