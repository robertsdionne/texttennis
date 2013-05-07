#include "constants.h"
#include "scene2controller.h"
#include "model.h"
#include "ofMain.h"
#include "scene2model.h"
#include "texttennis.h"
#include "utilities.h"

Scene2Controller::Scene2Controller(TextTennis &scene_manager, Scene2Model &model)
: Controller(scene_manager), model_(model), hit1(), hit2() {
  hit1.loadSound("hit1.mp3");
  hit1.setMultiPlay(true);
  hit2.loadSound("hit2.mp3");
  hit2.setMultiPlay(true);
  bounce1.loadSound("bounce1.wav");
  bounce2.loadSound("bounce2.wav");
  bounce3.loadSound("bounce3.wav");
  bounce4.loadSound("bounce4.wav");
}

Scene2Controller::~Scene2Controller() {
}

void Scene2Controller::BeginContact(b2Contact* contact) {
}

void Scene2Controller::Setup() {
  //scene_manager.GetMusic().TriggerTransition("scene2");
  // Box2D
  CreateBorder();
  CreateCourt();
  CreateNet();
  scene_begin_time = ofGetElapsedTimef();
  const ofPoint left(256-64, 200);
  const ofPoint right(768-64, 200);
  const float pause = 0.5;
  model_.dialogue
      .Speed(20.0)
      .Foreground(ofColor::white)
      .Background(ofColor(255, 255, 255, 32))
      .Position("left", left)
      .Position("right", right)
      .Message("You know why you're here, right?", "right").Pause(pause)
      .Message("No, why am I here?", "left").Pause(pause)
      .Message("Because you're bad at tennis.\nI'm gonna make you good.", "right").Pause(2.0)
      .Clear();
}

void Scene2Controller::Update() {
  model_.dialogue.Update();
  UpdateRackets();
  model_.world.Step(delta_time * 0.5, box2d_velocity_iterations, box2d_position_iterations);
  if (model_.score >= max_balls_goal) {
    scene_manager.NextScene();
    return;
  }
  model_.score = 0.0;
  model_.inverse_score = 0.0;
  for (auto ball : model_.ball_body) {
    if (ball->GetPosition().x > 0 && ball->GetLinearVelocity().Length() < 5.0) {
      model_.score += 1.0;
    }
    if (ball->GetPosition().x < 0 && ball->GetLinearVelocity().Length() < 5.0) {
      model_.inverse_score += 1.0;
    }
  }
  if (ofGetElapsedTimef() > scene_begin_time + 8.0 && ofGetFrameNum() % 1 == 0 && model_.ball_body.size() < max_balls) {
    const ofVec2f position = ball_initial_position.GetValue() + ofVec2f(-ofNoise(-1.7 * ofGetElapsedTimef()),
                                                                        ofSignedNoise(1.3 * ofGetElapsedTimef()));
    const ofVec2f velocity = ball_initial_velocity.GetValue()
        .rotated(-15.0 + ofSignedNoise(ofGetElapsedTimef()) * 30.0) * (1.0 + 0.1 * ofSignedNoise(1.3 * ofGetElapsedTimef()));
    CreateBall(position, velocity, 0.0, angular_velocity * ofRandomf());
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
//  ball_shape.m_radius = ball_radius + 2.0 * ball_radius * model_.ball_body.size() / 500.0;
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
    const ofVec2f position = ofVec2f(ball->GetPosition().x,
                                     ball->GetPosition().y);
    const float dx = ball->GetLinearVelocity().x;
    if (ofRandomuf() < 0.1 && abs((position - racket_position).x) < racket_speed + racket_radius
        && abs((position - racket_position).y) < racket_speed + 2.0 * racket_radius) {
      float variance = 0.0;
      float angular_velocity = 0.0;
      if ((keys[key_left] && dx < 0) || (keys[key_right] && dx > 0)) {
        variance = -hit_variance * ofRandomuf();
      } else if ((keys[key_left] && dx > 0) || (keys[key_right] && dx < 0)) {
        variance = hit_variance * ofRandomuf();
      } else {
        variance = hit_variance * ofRandomf();
      }
      const ofVec2f velocity = 2.0 * hit_mean * (1.0 + variance) * hit_direction;
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
  RacketCollide(model_.racket1, racket1_low_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
}
