#include "constants.h"
#include "scene1controller.h"
#include "model.h"
#include "ofMain.h"
#include "scene1model.h"
#include "texttennis.h"
#include "utilities.h"

Scene1Controller::Scene1Controller(TextTennis &scene_manager, Scene1Model &model)
: Controller(scene_manager), model_(model), music(), hit1(), hit2() {
  music.loadSound("main_theme.wav", true);
  music.setLoop(true);
  hit1.loadSound("hit1.mp3");
  hit2.loadSound("hit2.mp3");
  bounce1.loadSound("bounce1.wav");
  bounce2.loadSound("bounce2.wav");
  bounce3.loadSound("bounce3.wav");
  bounce4.loadSound("bounce4.wav");
}

Scene1Controller::~Scene1Controller() {
  music.stop();
}

void Scene1Controller::Setup() {
  // Box2D
  CreateBorder();
  CreateCourt();
  CreateNet();
  music.play();
  model_.scene_start_time = ofGetElapsedTimef();
  model_.rotation = 0;
  model_.world.SetContactListener(this);
  const ofPoint left(128, 320);
  const ofPoint right(704, 320);
  const float pause = 1.0;
  model_.dialogue
      .Speed(100.0)
      .Position("left", left)
      .Position("right", right)
      .Message("Hey let's play tennis.", "left").Pause(pause)
      .Message("Okay cool.", "right").Pause(pause)
      .Message("You remember how to play right?", "left").Pause(pause)
      .Message("Just press left and right.", "right").Pause(pause)
      .Message("Cool, you serve.", "left").Then([this] () {
        model_.scene_start_time = ofGetElapsedTimef();
        model_.frozen = false;
      }).Barrier("hit").Clear().Barrier("rotation_started").Barrier("opponent_has_ball").Then([this] () {
        model_.frozen = true;
        model_.rotating = true;
        model_.ball_body->GetFixtureList()->SetRestitution(0);
      }).Message("Hey, sorry. Let's stop, I got a cramp.", "left").Pause(2.0 * pause)
      .Message("Okay... what are you thinking about?", "right").Pause(2.0 * pause)
      .Message("I don't know, what are you thinking about?", "left").Pause(2.0 * pause)
      .Message("Nothing...", "right").Pause(2.0 * pause)
      .Message("Oh, cool that's interesting...", "left").Barrier("flipped").Clear()
      .Message("Okay. I'm good. I'll serve.", "left").Then([this] () {
        model_.frozen = false;
        model_.fallen = true;
      }).Barrier("opponent_hit").Then([this] () {
        model_.platform_appearing = true;
      }).Barrier("ball_below").Then([this] () {
        model_.player_released = true;
      }).Message("I'll get it!", "right").Barrier("retrieved").Then([this] () {
        model_.title_started = true;
        model_.ball_body->GetFixtureList()->SetRestitution(restitution);
      }).Clear();
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
  const ofPoint left1(128, 320);
  const ofPoint left2(300, 320);
  const ofPoint left = Lerp(left1, left2, model_.rotation);
  const ofPoint right1(704, 320);
  const ofPoint right2(900, 320);
  const ofPoint right = Lerp(right1, right2, model_.rotation);
  const ofMatrix4x4 transform = ofMatrix4x4::newTranslationMatrix(ofVec2f(0.0, -court_height / 2.0)) *
  ofMatrix4x4::newRotationMatrix(model_.rotation * 180.0, 0, 0, 1) *
      ofMatrix4x4::newTranslationMatrix(ofVec2f(0.0, court_height / 2.0));
  model_.dialogue.SetPosition("left",  ofVec2f(left * view_matrix_inverse * transform * view_matrix));
  model_.dialogue.SetPosition("right",  ofVec2f(right * view_matrix_inverse * transform * view_matrix));
  model_.dialogue.Update();
  if (!model_.frozen) {
    UpdateRackets();
  }
  if (model_.ball_body) {
    if (model_.dialogue.IsBlocked("opponent_has_ball") && model_.ball_body->GetPosition().x < 0
        && model_.ball_body->GetLinearVelocity().x < 0) {
      model_.dialogue.Trigger("opponent_has_ball");
    }
    if (model_.flipped && model_.dialogue.IsBlocked("ball_below") && model_.ball_body->GetPosition().y > 0.9 * court_height) {
      model_.dialogue.Trigger("ball_below");
    }
    if (!model_.fallen) {
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
  if (ofGetElapsedTimef() > model_.scene_start_time + 20.0 && model_.dialogue.IsBlocked("rotation_started")) {
    model_.dialogue.Trigger("rotation_started");
  }
  if (model_.rotating && model_.rotation <= 0.999) {
    model_.rotation += 0.001;
  }
  if (model_.platform_appearing && model_.platform <= 0.99) {
    model_.platform += 0.01;
  }
  if (model_.rotation >= 0.999 && model_.dialogue.IsBlocked("flipped")) {
    model_.dialogue.Trigger("flipped");
    model_.flipped = true;
  }
  if (model_.title_started && model_.title < 1.0) {
    model_.title += 0.0005;
  }
  if (model_.title >= 1.0) {
    scene_manager.NextScene();
    return;
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

  court_shape.SetAsBox(half_court_length, court_thickness,
                       b2Vec2(0.0, court_height - half_court_thickness), 0.0);
  court_fixture_definition.shape = &court_shape;
  model_.court_body->CreateFixture(&court_fixture_definition);
}

void Scene1Controller::CreateNet() {
  b2BodyDef net_body_definition;
  net_body_definition.position.Set(0.0, 0.0);
  model_.net_body = model_.world.CreateBody(&net_body_definition);
  b2EdgeShape net_shape;
  net_shape.Set(b2Vec2(0.0, court_thickness), b2Vec2(0.0, court_thickness + net_height));
  b2FixtureDef net_fixture_definition;
  net_fixture_definition.shape = &net_shape;
  model_.net_body->CreateFixture(&net_fixture_definition);

  net_shape.Set(b2Vec2(0.0, court_height - court_thickness), b2Vec2(0.0, court_height - court_thickness - net_height));
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
      if (model_.dialogue.IsBlocked("hit")) {
        model_.dialogue.Trigger("hit");
      }
      if (model_.dialogue.IsBlocked("opponent_hit")) {
        model_.dialogue.Trigger("opponent_hit");
      }
      if (model_.dialogue.IsBlocked("retrieved")) {
        model_.dialogue.Trigger("retrieved");
      }
    }
  }
}

void Scene1Controller::UpdateRackets() {
  model_.racket2 = Lerp(model_.racket2, model_.racket2_target, player_move_smooth_factor);
  model_.racket1 = Lerp(model_.racket1, model_.racket1_target, player_move_smooth_factor);
  if (!model_.player_released) {
    if (keys[OF_KEY_LEFT] && model_.racket2_target.x >  racket_speed + racket_radius) {
      model_.racket2_target.x -= racket_speed;
    }
    if (keys[OF_KEY_RIGHT] && model_.racket2_target.x < half_court_length) {
      model_.racket2_target.x += racket_speed;
    }
  } else {
    if (model_.racket2_target.y < court_height - court_thickness - racket_radius) {
      const ofVec2f gravity_force = -OpenFrameworksVector(gravity_vector.GetValue());
      model_.racket2_velocity += gravity_force * delta_time;
      model_.racket2_target += model_.racket2_velocity * delta_time;
    } else {
      model_.racket2_target.y = court_height - court_thickness - racket_radius;
    }
    if (keys[OF_KEY_LEFT] && model_.racket2_target.x < half_court_length) {
      model_.racket2_target.x += racket_speed;
    }
    if (keys[OF_KEY_RIGHT] && model_.racket2_target.x > racket_speed + racket_radius) {
      model_.racket2_target.x -= racket_speed;
    }
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
  if (!model_.player_released) {
    RacketCollide(model_.racket2, racket2_low_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
    RacketCollide(model_.racket1, racket1_low_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  } else {
    RacketCollide(model_.racket2, -racket_diagonal_hit_direction.GetValue(), low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
    RacketCollide(model_.racket1, racket_diagonal_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  }
}
