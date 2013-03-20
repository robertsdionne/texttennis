#include "constants.h"
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
  model.mouse_position = ofVec3f(x, y) * param_view_matrix_inverse;
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
  
  model.states.push_back(GameState());
  model.states.back().racket1 = model.racket1;
  model.states.back().racket2 = model.racket2;
  for (auto body : model.ball_body) {
    model.states.back().balls.push_back(GameObject(ofVec2f(body->GetPosition().x, body->GetPosition().y),
                                                   ofVec2f(body->GetLinearVelocity().x, body->GetLinearVelocity().y),
                                                   body->GetAngle(), body->GetAngularVelocity()));
  }
}

void Controller::Update() {
  if (keys['\t']) {
    if (model.states.size() > 1) {
      model.states.pop_back();
    }
    model.rewinding = true;
  } else {
    if (!keys['\t'] && previous_keys['\t']) {
      model.racket1 = model.states.back().racket1;
      model.racket2 = model.states.back().racket2;
      for (auto body : model.ball_body) {
        DestroyBall(body);
      }
      model.ball_body.clear();
      for (auto ball : model.states.back().balls) {
        CreateBall(ball.position, ball.velocity, ball.angle, ball.angular_velocity);
      }
      model.rewinding = false;
    }
    UpdateRackets();
    model.world.Step(param_delta_time, param_box2d_velocity_iterations, param_box2d_position_iterations);
    if (ofGetFrameNum() % param_save_every_n_frames == 0) {
      model.states.push_back(model.states.back());
      model.states.back().racket1 = model.racket1;
      model.states.back().racket2 = model.racket2;
      model.states.back().balls.clear();
      for (auto body : model.ball_body) {
        model.states.back().balls.push_back(GameObject(ofVec2f(body->GetPosition().x, body->GetPosition().y),
                                                       ofVec2f(body->GetLinearVelocity().x, body->GetLinearVelocity().y),
                                                       body->GetAngle(), body->GetAngularVelocity()));
      }
    }
    if (keys[' '] && !previous_keys[' ']) {
      ofVec2f mouse = param_low_hit_mean * (model.mouse_position - param_ball_initial_position).normalized();
      CreateBall(param_ball_initial_position, mouse, 0.0, param_angular_velocity * ofRandomf());
      if (model.ball_body.size() > param_max_balls) {
        b2Body *const body = model.ball_body.front();
        DestroyBall(body);
        model.ball_body.pop_front();
      }
    }
    if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
      if (model.ball_body.size() > 0) {
        b2Body *const body = model.ball_body.front();
        DestroyBall(body);
        model.ball_body.pop_front();
      }
    }
  }
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
  ball_body_definition.linearDamping = param_linear_damping;
  ball_body_definition.angularDamping = param_angular_damping;
  model.ball_body.push_back(model.world.CreateBody(&ball_body_definition));
  b2CircleShape ball_shape;
  ball_shape.m_radius = param_ball_radius;
  b2FixtureDef ball_fixture_definition;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = param_density;
  ball_fixture_definition.restitution = param_restitution;
  ball_fixture_definition.friction = param_friction;
  model.ball_body.back()->CreateFixture(&ball_fixture_definition);
}

void Controller::CreateBorder() {
  b2BodyDef border_body_definition;
  border_body_definition.position.Set(0.0, param_court_thickness);
  model.border_body = model.world.CreateBody(&border_body_definition);
  b2Vec2 vertices[4];
  vertices[0].Set(-param_half_court_length, 0.0);
  vertices[1].Set(-param_half_court_length, param_ceiling_height);
  vertices[2].Set(param_half_court_length, param_ceiling_height);
  vertices[3].Set(param_half_court_length, 0.0);
  b2ChainShape border_shape;
  border_shape.CreateChain(vertices, 4);
  b2FixtureDef border_fixture_definition;
  border_fixture_definition.shape = &border_shape;
  model.border_body->CreateFixture(&border_fixture_definition);
}

void Controller::CreateCourt() {
  b2BodyDef court_body_definition;
  court_body_definition.position.Set(0.0, param_half_court_thickness);
  model.court_body = model.world.CreateBody(&court_body_definition);
  b2PolygonShape court_shape;
  court_shape.SetAsBox(param_half_court_length, param_half_court_thickness);
  b2FixtureDef court_fixture_definition;
  court_fixture_definition.shape = &court_shape;
  court_fixture_definition.friction = param_friction;
  model.court_body->CreateFixture(&court_fixture_definition);
}

void Controller::CreateNet() {
  b2BodyDef net_body_definition;
  net_body_definition.position.Set(0.0, param_court_thickness);
  model.net_body = model.world.CreateBody(&net_body_definition);
  b2EdgeShape net_shape;
  net_shape.Set(b2Vec2(), b2Vec2(0.0, param_net_height));
  b2FixtureDef net_fixture_definition;
  net_fixture_definition.shape = &net_shape;
  model.net_body->CreateFixture(&net_fixture_definition);
}

void Controller::DestroyBall(b2Body *ball) {
  ball->DestroyFixture(ball->GetFixtureList());
  model.world.DestroyBody(ball);
}

bool Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}

void Controller::RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
                               float hit_mean, int key_left, int key_right) {
  for (auto ball : model.ball_body) {
    const ofVec2f position = ofVec2f(ball->GetPosition().x, ball->GetPosition().y);
    const float dx = ball->GetLinearVelocity().x;
    if ((position - racket_position).length() < param_ball_radius + 2.0 * param_racket_radius) {
      float variance = 0.0;
      float angular_velocity = 0.0;
      if ((keys[key_left] && dx < 0) || (keys[key_right] && dx > 0)) {
        variance = -param_hit_variance * ofRandomuf();
      } else if ((keys[key_left] && dx > 0) || (keys[key_right] && dx < 0)) {
        variance = param_hit_variance * ofRandomuf();
      } else {
        variance = param_hit_variance * ofRandomf();
      }
      const ofVec2f velocity = hit_mean * (1.0 + variance) * hit_direction;
      ball->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
    }
  }
}

void Controller::UpdateRackets() {
  if (keys['a'] && model.racket1.x > -param_half_court_length) {
    model.racket1.x -= param_racket_speed;
  }
  if (keys['d'] && model.racket1.x < -param_racket_speed - param_racket_radius) {
    model.racket1.x += param_racket_speed;
  }
  if (keys[OF_KEY_LEFT] && model.racket2.x > param_racket_speed + param_racket_radius) {
    model.racket2.x -= param_racket_speed;
  }
  if (keys[OF_KEY_RIGHT] && model.racket2.x < param_half_court_length) {
    model.racket2.x += param_racket_speed;
  }
  if (keys['w'] && !previous_keys['w']) {
    RacketCollide(model.racket1, param_racket1_high_hit_direction, param_high_hit_mean, 'a', 'd');
  } else if (keys['s'] && !previous_keys['s']) {
    RacketCollide(model.racket1, param_racket1_low_hit_direction, param_low_hit_mean, 'a', 'd');
  }
  if (keys[OF_KEY_UP] && !previous_keys[OF_KEY_UP]) {
    RacketCollide(model.racket2, param_racket2_high_hit_direction, param_high_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  } else if (keys[OF_KEY_DOWN] && !previous_keys[OF_KEY_DOWN]) {
    RacketCollide(model.racket2, param_racket2_low_hit_direction, param_low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  }
}
