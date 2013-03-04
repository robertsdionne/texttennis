#include <Box2D/Box2D.h>

#include "texttennis.h"

/**
 * Public constant definitions.
 */
constexpr int TextTennis::kHalfWindowWidth;

constexpr int TextTennis::kWindowWidth;

constexpr int TextTennis::kWindowHeight;

/**
 * Private constant definitions.
 */
constexpr float TextTennis::kAngularDamping;

constexpr float TextTennis::kAngularVelocity;

constexpr float TextTennis::kBallCartoonFactor;

const ofVec2f TextTennis::kBallInitialPosition = ofVec2f(11, 1);

constexpr float TextTennis::kBallMass;

constexpr float TextTennis::kBallRadius;

constexpr int TextTennis::kBox2dVelocityIterations;

constexpr int TextTennis::kBox2dPositionIterations;

constexpr float TextTennis::kCeilingHeight;

constexpr float TextTennis::kCourtLength;

constexpr float TextTennis::kCourtThickness;

constexpr float TextTennis::kDefaultAngle;

constexpr float TextTennis::kDefaultAngularVelocity;

constexpr float TextTennis::kDeltaTime;

constexpr float TextTennis::kDensity;

constexpr float TextTennis::kFrameRate;

constexpr float TextTennis::kFriction;

constexpr float TextTennis::kGravity;

const b2Vec2 TextTennis::kGravityVector = b2Vec2(0.0, -kGravity);

constexpr float TextTennis::kHalfCourtLength;

constexpr float TextTennis::kHalfCourtThickness;

const ofVec2f TextTennis::kHitDirection = ofVec2f(1.0, 0.5).normalized();

constexpr float TextTennis::kHitMean;

constexpr float TextTennis::kHitVariance;

constexpr float TextTennis::kLinearDamping;

constexpr long TextTennis::kMaxBalls;

constexpr float TextTennis::kNetHeight;

constexpr float TextTennis::kNetThickness;

const ofVec2f TextTennis::kRacket1StartPosition = ofVec2f(-8, kCourtThickness + kRacketRadius);

constexpr float TextTennis::kRacketRadius;

constexpr float TextTennis::kRacketSpeed;

constexpr float TextTennis::kRestitution;

constexpr int TextTennis::kSaveEveryNFrames;

constexpr int TextTennis::kTrailSize;

const ofMatrix4x4 TextTennis::kViewMatrix =
    ofMatrix4x4::newScaleMatrix(kWindowWidth / kCourtLength, -kWindowWidth / kCourtLength, 1) *
        ofMatrix4x4::newTranslationMatrix(kHalfWindowWidth, kWindowHeight, 0.0);

const ofMatrix4x4 TextTennis::kViewMatrixInverse = ofMatrix4x4::getInverseOf(kViewMatrix);

/**
 * Public method definitions.
 */
TextTennis::TextTennis()
: console(), world(kGravityVector), ball_body(), ball_shape(), ball_fixture(nullptr),
  court_body(nullptr), court_shape(), court_fixture(nullptr), net_body(nullptr), net_shape(),
  net_fixture(nullptr), border_body(nullptr), border_shape(), border_fixture(nullptr),
  racket1(kRacket1StartPosition), mouse_position(), states(), previous_keys(), keys()
{}

void TextTennis::setup() {
  ofSetFrameRate(kFrameRate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);

  // Box2D
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
    if (ofGetFrameNum() % kSaveEveryNFrames == 0) {
      states.push_back(states.back());
      states.back().racket1 = racket1;
      states.back().balls.clear();
      for (auto body : ball_body) {
        states.back().balls.push_back(GameObject(ofVec2f(body->GetPosition().x, body->GetPosition().y),
                                                 ofVec2f(body->GetLinearVelocity().x, body->GetLinearVelocity().y),
                                                 body->GetAngle(), body->GetAngularVelocity()));
      }
    }
    if (keys[' '] && !previous_keys[' ']) {
      ofVec2f mouse = kHitMean * (mouse_position - kBallInitialPosition).normalized();
      CreateBall(kBallInitialPosition, mouse, 0.0, kAngularVelocity * ofRandomf());
      if (ball_body.size() > kMaxBalls) {
        b2Body *const body = ball_body.front();
        body->DestroyFixture(body->GetFixtureList());
        world.DestroyBody(body);
        ball_body.pop_front();
      }
    }
    if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
      if (ball_body.size() > 0) {
        b2Body *const body = ball_body.front();
        body->DestroyFixture(body->GetFixtureList());
        world.DestroyBody(body);
        ball_body.pop_front();
      }
    }
  }
  previous_keys = keys;
}

void TextTennis::draw() {
  ofMultMatrix(kViewMatrix);
  DrawCourt();
  DrawNet();
  if (keys['\t']) {
    DrawRacket(states.back().racket1);
    for (auto ball : states.back().balls) {
      DrawBall(ball.position, ball.angle);
    }
  } else {
    DrawRacket(racket1);
    for (auto ball : ball_body) {
      DrawBall(ofVec2f(ball->GetPosition().x, ball->GetPosition().y), ball->GetAngle());
    }
  }
  DrawFrameRate();
}

void TextTennis::keyPressed(int key) {
  keys[key] = true;
}

void TextTennis::keyReleased(int key) {
  keys[key] = false;
}

void TextTennis::mouseMoved(int x, int y) {
  mouse_position = ofVec3f(x, y) * kViewMatrixInverse;
}

/**
 * Private method defintions.
 */
void TextTennis::CreateBall(ofVec2f position, ofVec2f velocity,
                            float angle, float angular_velocity) {
  b2BodyDef ball_body_definition;
  ball_body_definition.type = b2_dynamicBody;
  ball_body_definition.position.Set(position.x, position.y);
  ball_body_definition.linearVelocity.Set(velocity.x, velocity.y);
  ball_body_definition.angle = angle;
  ball_body_definition.angularVelocity = angular_velocity;
  ball_body_definition.linearDamping = kLinearDamping;
  ball_body_definition.angularDamping = kAngularDamping;
  ball_body.push_back(world.CreateBody(&ball_body_definition));
  ball_shape.m_radius = kBallRadius;
  b2FixtureDef ball_fixture_definition;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = kDensity;
  ball_fixture_definition.restitution = kRestitution;
  ball_fixture_definition.friction = kFriction;
  ball_fixture = ball_body.back()->CreateFixture(&ball_fixture_definition);
}

void TextTennis::CreateBorder() {
  b2BodyDef border_body_definition;
  border_body_definition.position.Set(0.0, kCourtThickness);
  border_body = world.CreateBody(&border_body_definition);
  b2Vec2 vertices[4];
  vertices[0].Set(-kHalfCourtLength, 0.0);
  vertices[1].Set(-kHalfCourtLength, kCeilingHeight);
  vertices[2].Set(kHalfCourtLength, kCeilingHeight);
  vertices[3].Set(kHalfCourtLength, 0.0);
  border_shape.CreateChain(vertices, 4);
  b2FixtureDef border_fixture_definition;
  border_fixture_definition.shape = &border_shape;
  border_fixture = border_body->CreateFixture(&border_fixture_definition);
}

void TextTennis::CreateCourt() {
  b2BodyDef court_body_definition;
  court_body_definition.position.Set(0.0, kHalfCourtThickness);
  court_body = world.CreateBody(&court_body_definition);
  court_shape.SetAsBox(kHalfCourtLength, kHalfCourtThickness);
  b2FixtureDef court_fixture_definition;
  court_fixture_definition.shape = &court_shape;
  court_fixture_definition.friction = kFriction;
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

void TextTennis::DrawBall(ofVec2f position, float angle) {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, kBallRadius);
  ofSetColor(ofColor::white);
  ofLine(position, position + kBallRadius * ofVec2f(cos(angle), sin(angle)));
  ofPopStyle();
}

void TextTennis::DrawCourt() {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-kHalfCourtLength, kCourtThickness), kCourtLength, -kCourtThickness);
  ofPopStyle();
}

void TextTennis::DrawFrameRate() {
  std::stringstream out;
  out << ofGetFrameRate();
  ofPushStyle();
  ofSetColor(ofColor::white);
  ofDrawBitmapString(out.str(), -kHalfCourtLength, kHalfCourtThickness);
  ofPopStyle();
}

void TextTennis::DrawNet() {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofRect(ofVec2f(-kHalfNetThickness, kNetHeight + kCourtThickness), kNetThickness, -kNetHeight);
  ofPopStyle();
}

void TextTennis::DrawRacket(ofVec2f position) {
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofCircle(position, kRacketRadius);
  ofPopStyle();
}

void TextTennis::RacketCollide() {
  for (auto ball : ball_body) {
    const ofVec2f position = ofVec2f(ball->GetPosition().x, ball->GetPosition().y);
    const float dx = ball->GetLinearVelocity().x;
    if ((position - racket1).length() < kBallRadius + kRacketRadius) {
      float variance = 0.0;
      if ((keys['a'] && dx < 0) || (keys['d'] && dx > 0)) {
        variance = -kHitVariance * ofRandomuf();
      } else if ((keys['a'] && dx > 0) || (keys['d'] && dx < 0)) {
        variance = kHitVariance * ofRandomuf();
      } else {
        variance = kHitVariance * ofRandomf();
      }
      const ofVec2f velocity = kHitMean * (1.0 + variance) * kHitDirection;
      ball->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
    }
  }
}

void TextTennis::UpdateRackets() {
  if (keys['a'] && racket1.x > -kHalfCourtLength) {
    racket1.x -= kRacketSpeed;
  }
  if (keys['d'] && racket1.x < -kRacketSpeed - kRacketRadius) {
    racket1.x += kRacketSpeed;
  }
}