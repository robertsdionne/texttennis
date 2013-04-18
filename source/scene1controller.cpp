#include "constants.h"
#include "scene1controller.h"
#include "model.h"
#include "ofMain.h"
#include "scene1model.h"
#include "texttennis.h"
#include "utilities.h"

Scene1Controller::Scene1Controller(TextTennis &scene_manager, Scene1Model &model)
: Controller(scene_manager), model_(model), rhythm_music(), shiny_music(), hit1(), hit2() {
  rhythm_music.loadSound("music/scene01_rhythm.wav", true);
  shiny_music.loadSound("music/scene01_shiny.wav", true);
  hit1.loadSound("hit1.mp3");
  hit2.loadSound("hit2.mp3");
  bounce1.loadSound("bounce1.wav");
  bounce2.loadSound("bounce2.wav");
  bounce3.loadSound("bounce3.wav");
  bounce4.loadSound("bounce4.wav");
}

Scene1Controller::~Scene1Controller() {
  rhythm_music.stop();
  shiny_music.stop();
}

void Scene1Controller::Setup() {
  // Box2D
  CreateBorder();
  CreateCourt();
  CreateNet();
  rhythm_music.play();
  shiny_music.play();
  model_.scene_start_time = ofGetElapsedTimef();
  model_.rotation = 0;
  model_.world.SetContactListener(this);
  const ofPoint left(256-64, 320);
  const ofPoint right(768-64, 320);
  const float pause = 0.5;
  model_.dialogue
      .Speed(100.0)
      .Position("left", left)
      .Position("right", right)
      .Message("Hey let’s play tennis.", "left").Pause(pause)
      .Message("Okay cool.", "right").Pause(pause)
      .Message("You remember how to play right?", "left").Pause(pause)
      .Message("Just press left and right.", "right").Pause(pause)
      .Message("Cool, you serve.", "left").Pause(pause)
      .Clear().Pause(10.0)
      .Message("Hey, sorry. Let's stop, I got a cramp.", "left").Pause(pause)
      .Message("Okay... what are you thinking about?", "right").Pause(pause)
      .Message("I don't know, what are you thinking about?", "left").Pause(pause)
      .Message("Oh, cool that's interesting...", "left").Pause(pause)
      .Message("Okay. I'm good. I'll serve.", "left").Pause(pause)
      .Message("I'll get it!", "right").Pause(pause);
}

void Scene1Controller::BeginContact(b2Contact* contact) {
  if (ofRandomuf() < 0.5) {
    if (ofRandomuf() < 0.5) {
      bounce1.play();
    } else {
      bounce2.play();
    }
  } else {
    if (ofRandomuf() < 0.5) {
      bounce3.play();
    } else {
      bounce4.play();
    }
  }
}

void Scene1Controller::Update() {
  model_.dialogue.Update();
  UpdateRackets();
  if (model_.ball_body) {
    if (model_.rotation < 0.999) {
      b2Vec2 force = gravity_vector.GetValue();
      force *= ball_mass;
      model_.ball_body->ApplyForceToCenter(force);
    } else {
      b2Vec2 force = gravity_vector.GetValue();
      force *= ball_mass * (model_.ball_body->GetPosition().x > 0 ? -1 : 1);
      model_.ball_body->ApplyForceToCenter(force);
    }
  }
  model_.world.Step(delta_time, box2d_velocity_iterations, box2d_position_iterations);
  if (model_.rotation <= 0.999 && ofGetElapsedTimef() > model_.scene_start_time + 20.0) {
    model_.rotation += 0.001;
  }
  if (!model_.ball_body) {
    CreateBall(ofVec2f(6, court_thickness + ball_radius + 1), ofVec2f(), 0.0, 0.0);
  }
  if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
    if (model_.ball_body) {
      b2Body *const body = model_.ball_body;
      DestroyBall(body);
      model_.ball_body = nullptr;
    }
  }
  Controller::Update();
}

Model &Scene1Controller::model() {
  return model_;
}

/**
 * Private method defintions.
 */
void Scene1Controller::CreateBall(ofVec2f position, ofVec2f velocity,
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

void Scene1Controller::CreateBorder() {
  b2BodyDef border_body_definition;
  border_body_definition.position.Set(0.0, court_thickness);
  model_.border_body = model_.world.CreateBody(&border_body_definition);
  b2Vec2 vertices[4];
  vertices[0].Set(-half_court_length, 0.0);
  vertices[1].Set(-half_court_length, court_height);
  vertices[2].Set(half_court_length, court_height);
  vertices[3].Set(half_court_length, 0.0);
  b2ChainShape border_shape;
  border_shape.CreateChain(vertices, 4);
  b2FixtureDef border_fixture_definition;
  border_fixture_definition.shape = &border_shape;
  model_.border_body->CreateFixture(&border_fixture_definition);
}

void Scene1Controller::CreateCourt() {
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

void Scene1Controller::CreateNet() {
  b2BodyDef net_body_definition;
  net_body_definition.position.Set(0.0, court_thickness);
  model_.net_body = model_.world.CreateBody(&net_body_definition);
  b2EdgeShape net_shape;
  net_shape.Set(b2Vec2(), b2Vec2(0.0, net_height));
  b2FixtureDef net_fixture_definition;
  net_fixture_definition.shape = &net_shape;
  model_.net_body->CreateFixture(&net_fixture_definition);
}

void Scene1Controller::DestroyBall(b2Body *ball) {
  ball->DestroyFixture(ball->GetFixtureList());
  model_.world.DestroyBody(ball);
}

bool Scene1Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}

void Scene1Controller::RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
                               float hit_mean, int key_left, int key_right) {
  if (model_.ball_body) {
    const ofVec2f position = ofVec2f(model_.ball_body->GetPosition().x,
                                     model_.ball_body->GetPosition().y);
    const float dx = model_.ball_body->GetLinearVelocity().x;
    if (ofRandomuf() < 0.1 && abs((position - racket_position).x) < ball_radius + 2.0 * racket_radius
        && abs((position - racket_position).y) < ball_radius + 2.0 * racket_radius) {
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
      ofRandomuf() > 0.5 ? hit1.play() : hit2.play();
    }
  }
}

void Scene1Controller::UpdateRackets() {
  model_.racket2 = Lerp(model_.racket2, model_.racket2_target, player_move_smooth_factor);
  model_.racket1 = Lerp(model_.racket1, model_.racket1_target, player_move_smooth_factor);
  if (keys[OF_KEY_LEFT] && model_.racket2_target.x >  racket_speed + racket_radius) {
    model_.racket2_target.x -= racket_speed;
  }
  if (keys[OF_KEY_RIGHT] && model_.racket2_target.x < half_court_length) {
    model_.racket2_target.x += racket_speed;
  }
  // opponent
  if (model_.ball_body && model_.ball_body->GetPosition().x < 0) {
    const float dx = model_.ball_body->GetPosition().x - model_.racket1_target.x;
    if (dx > racket_radius + ball_radius) {
      model_.racket1_target.x += racket_speed - ofNoise(ofGetElapsedTimef()) * racket_speed;
    } else if (dx < -racket_radius - ball_radius) {
      model_.racket1_target.x -= racket_speed - ofNoise(ofGetElapsedTimef()) * racket_speed;
    }
  } else {
    const float dx = ofSignedNoise(ofGetElapsedTimef()) * racket_speed;
    if (dx > 0 && model_.racket1_target.x < 0 - dx - racket_radius) {
      model_.racket1_target.x += dx;
    }
    if (dx < 0 && model_.racket1_target.x > -half_court_length) {
      model_.racket1_target.x += dx;
    }
  }
  RacketCollide(model_.racket2, racket2_low_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  RacketCollide(model_.racket1, racket1_low_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
}
