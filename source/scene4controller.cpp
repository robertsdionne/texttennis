#include "constants.h"
#include "scene4controller.h"
#include "model.h"
#include "ofMain.h"
#include "scene4model.h"
#include "texttennis.h"

Scene4Controller::Scene4Controller(TextTennis &scene_manager, Scene4Model &model)
: Controller(scene_manager), model_(model) {}

void Scene4Controller::BeginContact(b2Contact* contact) {
  const b2Body *body_a = contact->GetFixtureA()->GetBody();
  const b2Body *body_b = contact->GetFixtureB()->GetBody();
  const b2Body *ball = nullptr, *court = nullptr;
  if (model_.ball_body == body_a) {
    ball = body_a;
  }
  if (model_.ball_body == body_b) {
    ball = body_b;
  }
  if (model_.court_body == body_a) {
    court = body_a;
  }
  if (model_.court_body == body_b) {
    court = body_b;
  }
  if (ball && court && ball->GetPosition().x > 0) {
    model_.bounces += 1;
    if (model_.bounces == 2) {
      model_.score += 1;
    }
  }
}

void Scene4Controller::Setup() {
  // Box2D
  CreateBorder();
  CreateCourt();
  CreateNet();
  CreateTreePeople();
  model_.world.SetContactListener(this);
}

void Scene4Controller::Update() {
  if (model_.score >= 10) {
    scene_manager.NextScene();
    return;
  }
  if (model_.bounces >= 2) {
    DestroyBall(model_.ball_body);
    model_.ball_body = nullptr;
    model_.bounces = 0;
  }
  UpdateRackets();
  model_.world.Step(delta_time, box2d_velocity_iterations, box2d_position_iterations);
  if (!model_.ball_body) {
    CreateBall(ofVec2f(0.0, 2.0) + ball_initial_position, ball_initial_velocity, 0.0, angular_velocity * ofRandomf());
  }
  if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
    if (model_.ball_body) {
      DestroyBall(model_.ball_body);
      model_.ball_body = nullptr;
    }
  }
  Controller::Update();
}

Model &Scene4Controller::model() {
  return model_;
}

/**
 * Private method defintions.
 */
void Scene4Controller::CreateBall(ofVec2f position, ofVec2f velocity,
                                  float angle, float angular_velocity) {
  b2BodyDef ball_body_definition;
  ball_body_definition.type = b2_dynamicBody;
  ball_body_definition.position.Set(position.x, position.y);
  ball_body_definition.linearVelocity.Set(velocity.x, velocity.y);
  ball_body_definition.angle = angle;
  ball_body_definition.angularVelocity = angular_velocity;
  ball_body_definition.linearDamping = linear_damping;
  ball_body_definition.angularDamping = angular_damping;
  model_.ball_body = model_.world.CreateBody(&ball_body_definition);
  b2CircleShape ball_shape;
  ball_shape.m_radius = ball_radius;
  b2FixtureDef ball_fixture_definition;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = density;
  ball_fixture_definition.restitution = restitution;
  ball_fixture_definition.friction = friction;
  model_.ball_body->CreateFixture(&ball_fixture_definition);
}

void Scene4Controller::CreateTreePeople() {
  float offset = 4.0;
  for (int i = 0; i < 5; ++i) {
    const float radius = 0.5 + 0.1 * i;
    const float next_radius = 0.5 + 0.1 * (i + 1);

    b2BodyDef person_definition;
    person_definition.position.Set(offset, court_thickness + radius);
    model_.tree_people[i] = model_.world.CreateBody(&person_definition);
    b2CircleShape person_shape;
    person_shape.m_radius = radius;
    b2FixtureDef person_fixture_definition;
    person_fixture_definition.shape = &person_shape;
    model_.tree_people[i]->CreateFixture(&person_fixture_definition);

    offset += radius + next_radius + 2.0 * ball_radius;
  }
}

void Scene4Controller::CreateBorder() {
  b2BodyDef border_body_definition;
  border_body_definition.position.Set(0.0, court_thickness);
  model_.border_body = model_.world.CreateBody(&border_body_definition);
  b2Vec2 vertices[4];
  vertices[0].Set(-half_court_length, 0.0);
  vertices[1].Set(-half_court_length, ceiling_height);
  vertices[2].Set(half_court_length, ceiling_height);
  vertices[3].Set(half_court_length, 0.0);
  b2ChainShape border_shape;
  border_shape.CreateChain(vertices, 4);
  b2FixtureDef border_fixture_definition;
  border_fixture_definition.shape = &border_shape;
  model_.border_body->CreateFixture(&border_fixture_definition);
}

void Scene4Controller::CreateCourt() {
  b2BodyDef court_body_definition;
  court_body_definition.position.Set(0.0, half_court_thickness);
  model_.court_body = model_.world.CreateBody(&court_body_definition);
  b2PolygonShape court_shape;
  court_shape.SetAsBox(half_court_length, half_court_thickness);
  b2FixtureDef court_fixture_definition;
  court_fixture_definition.shape = &court_shape;
  court_fixture_definition.friction = friction;
  model_.court_body->CreateFixture(&court_fixture_definition);
}

void Scene4Controller::CreateNet() {
  b2BodyDef net_body_definition;
  net_body_definition.position.Set(0.0, court_thickness);
  model_.net_body = model_.world.CreateBody(&net_body_definition);
  b2EdgeShape net_shape;
  net_shape.Set(b2Vec2(), b2Vec2(0.0, net_height));
  b2FixtureDef net_fixture_definition;
  net_fixture_definition.shape = &net_shape;
  model_.net_body->CreateFixture(&net_fixture_definition);
}

void Scene4Controller::DestroyBall(b2Body *ball) {
  ball->DestroyFixture(ball->GetFixtureList());
  model_.world.DestroyBody(ball);
}

bool Scene4Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}

void Scene4Controller::RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
                               float hit_mean, int key_left, int key_right) {
  if (model_.ball_body) {
    const ofVec2f position = ofVec2f(model_.ball_body->GetPosition().x,
                                     model_.ball_body->GetPosition().y);
    const float dx = model_.ball_body->GetLinearVelocity().x;
    if ((position - racket_position).length() < ball_radius + 2.0 * racket_radius) {
      float variance = 0.0;
      float angular_velocity = 0.0;
      if ((keys[key_left] && dx < 0) || (keys[key_right] && dx > 0)) {
        variance = -hit_variance * ofRandomuf();
      } else if ((keys[key_left] && dx > 0) || (keys[key_right] && dx < 0)) {
        variance = hit_variance * ofRandomuf();
      } else {
        variance = hit_variance * ofRandomf();
      }
      const ofVec2f velocity = hit_mean * (1.0 + variance) * hit_direction;
      model_.ball_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
    }
  }
}

void Scene4Controller::UpdateRackets() {
  if (keys['a'] && model_.racket1.x > -half_court_length) {
    model_.racket1.x -= racket_speed;
  }
  if (keys['d'] && model_.racket1.x < -racket_speed - racket_radius) {
    model_.racket1.x += racket_speed;
  }
  if (keys['w'] && !previous_keys['w']) {
    RacketCollide(model_.racket1, racket1_high_hit_direction, high_hit_mean, 'a', 'd');
  } else if (keys['s'] && !previous_keys['s']) {
    RacketCollide(model_.racket1, racket1_low_hit_direction, low_hit_mean, 'a', 'd');
  }
}
