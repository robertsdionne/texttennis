#include <Box2D/Box2D.h>

#include "constants.h"
#include "texttennis.h"

/**
 * Public method definitions.
 */
TextTennis::TextTennis()
: model(), view(), controller(model), keys(), previous_keys() {}

void TextTennis::setup() {
  view.Setup();
  controller.Setup();

  model.states.push_back(GameState());
  model.states.back().racket1 = model.racket1;
  model.states.back().racket2 = model.racket2;
  for (auto body : model.ball_body) {
    model.states.back().balls.push_back(GameObject(ofVec2f(body->GetPosition().x, body->GetPosition().y),
                                             ofVec2f(body->GetLinearVelocity().x, body->GetLinearVelocity().y),
                                             body->GetAngle(), body->GetAngularVelocity()));
  }
}

void TextTennis::update() {
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
    model.world.Step(kDeltaTime, kBox2dVelocityIterations, kBox2dPositionIterations);
    if (ofGetFrameNum() % kSaveEveryNFrames == 0) {
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
      ofVec2f mouse = kLowHitMean * (model.mouse_position - kBallInitialPosition).normalized();
      CreateBall(kBallInitialPosition, mouse, 0.0, kAngularVelocity * ofRandomf());
      if (model.ball_body.size() > kMaxBalls) {
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
  previous_keys = keys;
  controller.Update();
}

void TextTennis::draw() {
  view.Draw(model);
}

void TextTennis::keyPressed(int key) {
  keys[key] = true;
  controller.OnKeyPressed(key);
}

void TextTennis::keyReleased(int key) {
  keys[key] = false;
  controller.OnKeyReleased(key);
}

void TextTennis::mouseMoved(int x, int y) {
  model.mouse_position = ofVec3f(x, y) * kViewMatrixInverse;
  controller.OnMouseMoved(x, y);
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

void TextTennis::DestroyBall(b2Body *ball) {
  ball->DestroyFixture(ball->GetFixtureList());
  model.world.DestroyBody(ball);
}

void TextTennis::RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
                               float hit_mean, int key_left, int key_right) {
  for (auto ball : model.ball_body) {
    const ofVec2f position = ofVec2f(ball->GetPosition().x, ball->GetPosition().y);
    const float dx = ball->GetLinearVelocity().x;
    if ((position - racket_position).length() < kBallRadius + 2.0 * kRacketRadius) {
      float variance = 0.0;
      float angular_velocity = 0.0;
      if ((keys[key_left] && dx < 0) || (keys[key_right] && dx > 0)) {
        variance = -kHitVariance * ofRandomuf();
      } else if ((keys[key_left] && dx > 0) || (keys[key_right] && dx < 0)) {
        variance = kHitVariance * ofRandomuf();
      } else {
        variance = kHitVariance * ofRandomf();
      }
      const ofVec2f velocity = hit_mean * (1.0 + variance) * hit_direction;
      ball->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
    }
  }
}

void TextTennis::UpdateRackets() {
  if (keys['a'] && model.racket1.x > -kHalfCourtLength) {
    model.racket1.x -= kRacketSpeed;
  }
  if (keys['d'] && model.racket1.x < -kRacketSpeed - kRacketRadius) {
    model.racket1.x += kRacketSpeed;
  }
  if (keys[OF_KEY_LEFT] && model.racket2.x > kRacketSpeed + kRacketRadius) {
    model.racket2.x -= kRacketSpeed;
  }
  if (keys[OF_KEY_RIGHT] && model.racket2.x < kHalfCourtLength) {
    model.racket2.x += kRacketSpeed;
  }
  if (keys['w'] && !previous_keys['w']) {
    RacketCollide(model.racket1, kRacket1HighHitDirection, kHighHitMean, 'a', 'd');
  } else if (keys['s'] && !previous_keys['s']) {
    RacketCollide(model.racket1, kRacket1LowHitDirection, kLowHitMean, 'a', 'd');
  }
  if (keys[OF_KEY_UP] && !previous_keys[OF_KEY_UP]) {
    RacketCollide(model.racket2, kRacket2HighHitDirection, kHighHitMean, OF_KEY_LEFT, OF_KEY_RIGHT);
  } else if (keys[OF_KEY_DOWN] && !previous_keys[OF_KEY_DOWN]) {
    RacketCollide(model.racket2, kRacket2LowHitDirection, kLowHitMean, OF_KEY_LEFT, OF_KEY_RIGHT);
  }
}