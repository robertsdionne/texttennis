#include "constants.h"
#include "controller.h"
#include "ofMain.h"
#include "model.h"
#include "texttennis.h"

Controller::Controller(TextTennis &scene_manager, Model &model)
: scene_manager(scene_manager), model(model), keys(), previous_keys() {}

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
  if (keys['r'] && !previous_keys['r']) {
    scene_manager.RestartScene();
    return;
  }
  if (keys['['] && !previous_keys['[']) {
    scene_manager.PreviousScene();
    return;
  }
  if (keys[']'] && !previous_keys[']']) {
    scene_manager.NextScene();
    return;
  }
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
    model.world.Step(delta_time, box2d_velocity_iterations, box2d_position_iterations);
    if (ofGetFrameNum() % save_every_n_frames == 0) {
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
      ofVec2f mouse = low_hit_mean * (model.mouse_position - ball_initial_position).normalized();
      CreateBall(ball_initial_position, mouse, 0.0, angular_velocity * ofRandomf());
      if (model.ball_body.size() > max_balls) {
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

void Controller::keyPressed(ofKeyEventArgs &event) {
  keys[event.key] = true;
}

void Controller::keyReleased(ofKeyEventArgs &event) {
  keys[event.key] = false;
}

void Controller::mouseDragged(ofMouseEventArgs &event) {
  mouseMoved(event);
}

void Controller::mouseMoved(ofMouseEventArgs &event) {
  model.mouse_position = ofVec3f(event.x, event.y) * view_matrix_inverse;
}

void Controller::mousePressed(ofMouseEventArgs &event) {
  buttons[event.button] = true;
}

void Controller::mouseReleased(ofMouseEventArgs &event) {
  buttons[event.button] = false;
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
  ball_body_definition.linearDamping = linear_damping;
  ball_body_definition.angularDamping = angular_damping;
  model.ball_body.push_back(model.world.CreateBody(&ball_body_definition));
  b2CircleShape ball_shape;
  ball_shape.m_radius = ball_radius;
  b2FixtureDef ball_fixture_definition;
  ball_fixture_definition.shape = &ball_shape;
  ball_fixture_definition.density = density;
  ball_fixture_definition.restitution = restitution;
  ball_fixture_definition.friction = friction;
  model.ball_body.back()->CreateFixture(&ball_fixture_definition);
}

void Controller::CreateBorder() {
  b2BodyDef border_body_definition;
  border_body_definition.position.Set(0.0, court_thickness);
  model.border_body = model.world.CreateBody(&border_body_definition);
  b2Vec2 vertices[4];
  vertices[0].Set(-half_court_length, 0.0);
  vertices[1].Set(-half_court_length, ceiling_height);
  vertices[2].Set(half_court_length, ceiling_height);
  vertices[3].Set(half_court_length, 0.0);
  b2ChainShape border_shape;
  border_shape.CreateChain(vertices, 4);
  b2FixtureDef border_fixture_definition;
  border_fixture_definition.shape = &border_shape;
  model.border_body->CreateFixture(&border_fixture_definition);
}

void Controller::CreateCourt() {
  b2BodyDef court_body_definition;
  court_body_definition.position.Set(0.0, half_court_thickness);
  model.court_body = model.world.CreateBody(&court_body_definition);
  b2PolygonShape court_shape;
  court_shape.SetAsBox(half_court_length, half_court_thickness);
  b2FixtureDef court_fixture_definition;
  court_fixture_definition.shape = &court_shape;
  court_fixture_definition.friction = friction;
  model.court_body->CreateFixture(&court_fixture_definition);
}

void Controller::CreateNet() {
  b2BodyDef net_body_definition;
  net_body_definition.position.Set(0.0, court_thickness);
  model.net_body = model.world.CreateBody(&net_body_definition);
  b2EdgeShape net_shape;
  net_shape.Set(b2Vec2(), b2Vec2(0.0, net_height));
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

void Controller::UpdateRackets() {
  if (keys['a'] && model.racket1.x > -half_court_length) {
    model.racket1.x -= racket_speed;
  }
  if (keys['d'] && model.racket1.x < -racket_speed - racket_radius) {
    model.racket1.x += racket_speed;
  }
  if (keys[OF_KEY_LEFT] && model.racket2.x > racket_speed + racket_radius) {
    model.racket2.x -= racket_speed;
  }
  if (keys[OF_KEY_RIGHT] && model.racket2.x < half_court_length) {
    model.racket2.x += racket_speed;
  }
  if (keys['w'] && !previous_keys['w']) {
    RacketCollide(model.racket1, racket1_high_hit_direction, high_hit_mean, 'a', 'd');
  } else if (keys['s'] && !previous_keys['s']) {
    RacketCollide(model.racket1, racket1_low_hit_direction, low_hit_mean, 'a', 'd');
  }
  if (keys[OF_KEY_UP] && !previous_keys[OF_KEY_UP]) {
    RacketCollide(model.racket2, racket2_high_hit_direction, high_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  } else if (keys[OF_KEY_DOWN] && !previous_keys[OF_KEY_DOWN]) {
    RacketCollide(model.racket2, racket2_low_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  }
}
