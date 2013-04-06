#include "constants.h"
#include "scene2controller.h"
#include "model.h"
#include "ofMain.h"
#include "scene2model.h"
#include "texttennis.h"
#include "utilities.h"

Scene2Controller::Scene2Controller(TextTennis &scene_manager, Scene2Model &model)
: Controller(scene_manager), model_(model), low_music(), high_music() {
  low_music.loadSound("music/scene02_lows.wav", true);
  high_music.loadSound("music/scene02_highs.wav", true);
}

Scene2Controller::~Scene2Controller() {
  low_music.stop();
  high_music.stop();
}

void Scene2Controller::Setup() {
  // Box2D
  CreateBorder();
  CreateCourt();
  CreateNet();
  low_music.play();
  high_music.play();
  scene_begin_time = ofGetElapsedTimef();
}

void Scene2Controller::Update() {
  UpdateRackets();
  model_.world.Step(delta_time, box2d_velocity_iterations, box2d_position_iterations);
  if (model_.score >= 500.0) {
    scene_manager.NextScene();
    return;
  }
  model_.score = 0.0;
  for (auto ball : model_.ball_body) {
    if (ball->GetPosition().x > 0 && ball->GetLinearVelocity().Length() < 5.0) {
      model_.score += 1.0;
    }
  }
  if (ofGetElapsedTimef() > scene_begin_time + 8.0 && ofGetFrameNum() % 4 == 0 && model_.ball_body.size() < max_balls) {
    CreateBall(ball_initial_position, ball_initial_velocity, 0.0, angular_velocity * ofRandomf());
    if (model_.ball_body.size() > max_balls) {
      b2Body *const body = model_.ball_body.front();
      DestroyBall(body);
      model_.ball_body.pop_front();
    }
  }
  if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
    if (model_.ball_body.size() > 0) {
      b2Body *const body = model_.ball_body.front();
      DestroyBall(body);
      model_.ball_body.pop_front();
    }
  }
  Controller::Update();
}

Model &Scene2Controller::model() {
  return model_;
}

/**
 * Private method defintions.
 */
void Scene2Controller::CreateBall(ofVec2f position, ofVec2f velocity,
                            float angle, float angular_velocity) {
  b2BodyDef ball_body_definition;
  ball_body_definition.type = b2_dynamicBody;
  ball_body_definition.position.Set(position.x, position.y);
  ball_body_definition.linearVelocity.Set(velocity.x, velocity.y);
  ball_body_definition.angle = angle;
  ball_body_definition.angularVelocity = angular_velocity;
  ball_body_definition.linearDamping = linear_damping;
  ball_body_definition.angularDamping = angular_damping;
  model_.ball_body.push_back(model_.world.CreateBody(&ball_body_definition));
  b2CircleShape ball_shape;
  ball_shape.m_radius = ball_radius;
  b2FixtureDef ball_fixture_definition;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = density;
  ball_fixture_definition.restitution = restitution;
  ball_fixture_definition.friction = friction;
  model_.ball_body.back()->CreateFixture(&ball_fixture_definition);
}

void Scene2Controller::CreateBorder() {
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

void Scene2Controller::CreateCourt() {
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

void Scene2Controller::CreateNet() {
  b2BodyDef net_body_definition;
  net_body_definition.position.Set(0.0, court_thickness);
  model_.net_body = model_.world.CreateBody(&net_body_definition);
  b2EdgeShape net_shape;
  net_shape.Set(b2Vec2(), b2Vec2(0.0, net_height));
  b2FixtureDef net_fixture_definition;
  net_fixture_definition.shape = &net_shape;
  model_.net_body->CreateFixture(&net_fixture_definition);
}

void Scene2Controller::DestroyBall(b2Body *ball) {
  ball->DestroyFixture(ball->GetFixtureList());
  model_.world.DestroyBody(ball);
}

bool Scene2Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}

void Scene2Controller::RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
                               float hit_mean, int key_left, int key_right) {
  for (auto ball : model_.ball_body) {
    const ofVec2f position = ofVec2f(ball->GetPosition().x, ball->GetPosition().y);
    const float dx = ball->GetLinearVelocity().x;
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
      ball->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
    }
  }
}

void Scene2Controller::UpdateRackets() {
  model_.racket1 = Lerp(model_.racket1, model_.racket1_target, player_move_smooth_factor);
  if (keys[OF_KEY_LEFT] && model_.racket1_target.x > -half_court_length) {
    model_.racket1_target.x -= racket_speed;
  }
  if (keys[OF_KEY_RIGHT] && model_.racket1_target.x < -racket_speed - racket_radius) {
    model_.racket1_target.x += racket_speed;
  }
  if (keys[OF_KEY_UP] && !previous_keys[OF_KEY_UP]) {
    RacketCollide(model_.racket1, racket1_high_hit_direction, high_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  } else if (keys[OF_KEY_DOWN] && !previous_keys[OF_KEY_DOWN]) {
    RacketCollide(model_.racket1, racket1_low_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  }
}
