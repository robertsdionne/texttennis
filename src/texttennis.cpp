#include <Box2D/Box2D.h>

#include "texttennis.h"

const b2Vec2 TextTennis::kGravityVector = b2Vec2(0.0, -kGravity);

TextTennis::TextTennis()
: console(), world(kGravityVector), ball_body(), ball_shape(), ball_fixture(nullptr),
  court_body(nullptr), court_shape(), court_fixture(nullptr), net_body(nullptr), net_shape(),
  net_fixture(nullptr), border_body(nullptr), border_shape(), border_fixture(nullptr),
  show_console(false), show_text(false), use_ai(false),
  racket1(-8, kCourtThickness + kRacketRadius), mouse_position(), states(), previous_keys(), keys()
{}

void TextTennis::setup() {
  ofSetFrameRate(kFrameRate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  
  // Box2D
  CreateBall(ofVec2f(11, 1), ofVec2f(-15, 7.5));
  CreateBorder();
  CreateCourt();
  CreateNet();
  
  states.push_back(GameState());
  states.back().racket1 = racket1;
  for (auto body : ball_body) {
    states.back().balls.push_back(GameObject(ofVec2f(body->GetPosition().x, body->GetPosition().y),
                                             ofVec2f(body->GetLinearVelocity().x, body->GetLinearVelocity().y),
                                             body->GetAngle(), body->GetAngularVelocity()));
  }
}

void TextTennis::CreateBall(ofVec2f position, ofVec2f velocity,
                            float angle, float angular_velocity) {
  b2BodyDef ball_body_definition;
  ball_body_definition.type = b2_dynamicBody;
  ball_body_definition.position.Set(position.x, position.y);
  ball_body_definition.linearVelocity.Set(velocity.x, velocity.y);
  ball_body_definition.angle = angle;
  ball_body_definition.angularVelocity = angular_velocity;
  ball_body_definition.linearDamping = 0.1;
  ball_body_definition.angularDamping = 0.1;
  ball_body.push_back(world.CreateBody(&ball_body_definition));
  ball_shape.m_radius = kBallRadius;
  b2FixtureDef ball_fixture_definition;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = 1.0;
  ball_fixture_definition.restitution = 0.728;
  ball_fixture_definition.friction = 0.3;
  ball_fixture = ball_body.back()->CreateFixture(&ball_fixture_definition);
}

void TextTennis::CreateBorder() {
  b2BodyDef border_body_definition;
  border_body_definition.position.Set(0.0, kCourtThickness);
  border_body = world.CreateBody(&border_body_definition);
  b2Vec2 vertices[4];
  vertices[0].Set(-kCourtLength / 2.0, 0.0);
  vertices[1].Set(-kCourtLength / 2.0, 100.0);
  vertices[2].Set(kCourtLength / 2.0, 100.0);
  vertices[3].Set(kCourtLength / 2.0, 0.0);
  border_shape.CreateChain(vertices, 4);
  b2FixtureDef border_fixture_definition;
  border_fixture_definition.shape = &border_shape;
  border_fixture = border_body->CreateFixture(&border_fixture_definition);
}

void TextTennis::CreateCourt() {
  b2BodyDef court_body_definition;
  court_body_definition.position.Set(0.0, kCourtThickness / 2.0);
  court_body = world.CreateBody(&court_body_definition);
  court_shape.SetAsBox(kCourtLength / 2.0, kCourtThickness / 2.0);
  b2FixtureDef court_fixture_definition;
  court_fixture_definition.shape = &court_shape;
  court_fixture_definition.friction = 0.3;
  court_fixture = court_body->CreateFixture(&court_fixture_definition);
}

void TextTennis::CreateNet() {
  b2BodyDef net_body_definition;
  net_body_definition.position.Set(0.0, kCourtThickness);
  net_body = world.CreateBody(&net_body_definition);
  net_shape.Set(b2Vec2(), b2Vec2(0.0, kNetHeight));
  b2FixtureDef net_fixture_definition;
  net_fixture_definition.shape = &net_shape;
  net_fixture = net_body->CreateFixture(&net_fixture_definition);
}

void TextTennis::update() {
  if (keys['\t']) {
    if (states.size() > 1) {
      states.pop_back();
    }
  } else {
    if (!keys['\t'] && previous_keys['\t']) {
      racket1 = states.back().racket1;
      for (auto body : ball_body) {
        body->DestroyFixture(body->GetFixtureList());
        world.DestroyBody(body);
      }
      ball_body.clear();
      for (auto ball : states.back().balls) {
        CreateBall(ball.position, ball.velocity, ball.angle, ball.angular_velocity);
      }
    }
    UpdateRackets();
    RacketCollide();
    world.Step(kDeltaTime, kBox2dVelocityIterations, kBox2dPositionIterations);
    if (ofGetFrameNum() % 2 == 0) {
      states.push_back(states.back());
      states.back().racket1 = racket1;
      states.back().balls.clear();
      for (auto body : ball_body) {
        states.back().balls.push_back(GameObject(ofVec2f(body->GetPosition().x, body->GetPosition().y),
                                                 ofVec2f(body->GetLinearVelocity().x, body->GetLinearVelocity().y),
                                                 body->GetAngle(), body->GetAngularVelocity()));
      }
    }
    if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
      ofVec2f mouse = 12.0 * (mouse_position - ofVec2f(11, 1)).normalized();
      CreateBall(ofVec2f(11, 1), mouse, 0.0, 100.0 * ofRandomf());
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
  if (keys['\t']) {
    ofCircle(TransformPosition(states.back().racket1), TransformSize(kRacketRadius));
    for (auto ball : states.back().balls) {
      ofSetColor(ofColor::black);
      ofCircle(TransformPosition(ball.position), TransformSize(kBallRadius));
      ofSetColor(ofColor::white);
      ofLine(TransformPosition(ball.position),
             TransformPosition(ball.position + kBallRadius * ofVec2f(cos(ball.angle), sin(ball.angle))));
    }
  } else {
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