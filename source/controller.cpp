#include "controller.h"
#include "ofMain.h"
#include "model.h"

Controller::Controller(Model &model)
: model(model), keys(), previous_keys() {}

void Controller::OnKeyPressed(int key) {
  keys[key] = true;
}

void Controller::OnKeyReleased(int key) {
  keys[key] = false;
}

void Controller::OnMouseDragged(int x, int y, int button) {
  OnMouseMoved(x, y);
}

void Controller::OnMouseMoved(int x, int y) {
  //model.mouse_position = ofVec3f(x, y) * kViewMatrixInverse;
}

void Controller::OnMousePressed(int x, int y, int button) {
  buttons[button] = true;
}

void Controller::OnMouseReleased(int x, int y, int button) {
  buttons[button] = false;
}

void Controller::Setup() {
  // Box2D
  CreateBorder();
  CreateCourt();
  CreateNet();
}

void Controller::Update() {
  previous_buttons = buttons;
  previous_keys = keys;
}

/**
 * Private method defintions.
 */
void Controller::CreateBall(ofVec2f position, ofVec2f velocity,
                            float angle, float angular_velocity) {
  b2BodyDef ball_body_definition;
  ball_body_definition.type = b2_dynamicBody;
  ball_body_definition.position.Set(position.x, position.y);
  ball_body_definition.linearVelocity.Set(velocity.x, velocity.y);
  ball_body_definition.angle = angle;
  ball_body_definition.angularVelocity = angular_velocity;
  ball_body_definition.linearDamping = kLinearDamping;
  ball_body_definition.angularDamping = kAngularDamping;
  model.ball_body.push_back(model.world.CreateBody(&ball_body_definition));
  b2CircleShape ball_shape;
  ball_shape.m_radius = kBallRadius;
  b2FixtureDef ball_fixture_definition;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = kDensity;
  ball_fixture_definition.restitution = kRestitution;
  ball_fixture_definition.friction = kFriction;
  model.ball_body.back()->CreateFixture(&ball_fixture_definition);
}

void Controller::CreateBorder() {
  b2BodyDef border_body_definition;
  border_body_definition.position.Set(0.0, kCourtThickness);
  model.border_body = model.world.CreateBody(&border_body_definition);
  b2Vec2 vertices[4];
  vertices[0].Set(-kHalfCourtLength, 0.0);
  vertices[1].Set(-kHalfCourtLength, kCeilingHeight);
  vertices[2].Set(kHalfCourtLength, kCeilingHeight);
  vertices[3].Set(kHalfCourtLength, 0.0);
  b2ChainShape border_shape;
  border_shape.CreateChain(vertices, 4);
  b2FixtureDef border_fixture_definition;
  border_fixture_definition.shape = &border_shape;
  model.border_body->CreateFixture(&border_fixture_definition);
}

void Controller::CreateCourt() {
  b2BodyDef court_body_definition;
  court_body_definition.position.Set(0.0, kHalfCourtThickness);
  model.court_body = model.world.CreateBody(&court_body_definition);
  b2PolygonShape court_shape;
  court_shape.SetAsBox(kHalfCourtLength, kHalfCourtThickness);
  b2FixtureDef court_fixture_definition;
  court_fixture_definition.shape = &court_shape;
  court_fixture_definition.friction = kFriction;
  model.court_body->CreateFixture(&court_fixture_definition);
}

void Controller::CreateNet() {
  b2BodyDef net_body_definition;
  net_body_definition.position.Set(0.0, kCourtThickness);
  model.net_body = model.world.CreateBody(&net_body_definition);
  b2EdgeShape net_shape;
  net_shape.Set(b2Vec2(), b2Vec2(0.0, kNetHeight));
  b2FixtureDef net_fixture_definition;
  net_fixture_definition.shape = &net_shape;
  model.net_body->CreateFixture(&net_fixture_definition);
}

bool Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}
