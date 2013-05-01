#include "constants.h"
#include "scene3controller.h"
#include "model.h"
#include "ofMain.h"
#include "scene3model.h"
#include "texttennis.h"
#include "utilities.h"

Scene3Controller::Scene3Controller(TextTennis &scene_manager, Scene3Model &model)
: Controller(scene_manager), model_(model) {
  hit1.loadSound("hit1.mp3");
  hit2.loadSound("hit2.mp3");
  bounce1.loadSound("bounce1.wav");
  bounce2.loadSound("bounce2.wav");
  bounce3.loadSound("bounce3.wav");
  bounce4.loadSound("bounce4.wav");
}

void Scene3Controller::BeginContact(b2Contact* contact) {
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
  if (ball && court && ball->GetPosition().x > 0 && model_.served) {
    model_.bounces += 1;
    if (model_.bounces == 2) {
      model_.angle = 0.0;
      model_.score += 1;
      model_.ball_in_play = false;
      if (model_.opponent_index == 5) {
        model_.opponent = model_.opponent_target = ofVec2f(half_court_length, racket_radius + court_thickness);
      }
      model_.dialogue.Trigger("point");
    }
  } else if (ball && court && ball->GetPosition().x < 0) {
    model_.bounces = 0;
  }

  bounce1.setPan(model_.ball_body->GetPosition().x / half_court_length);
  bounce2.setPan(model_.ball_body->GetPosition().x / half_court_length);
  bounce3.setPan(model_.ball_body->GetPosition().x / half_court_length);
  bounce4.setPan(model_.ball_body->GetPosition().x / half_court_length);
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

void Scene3Controller::Setup() {
  //scene_manager.GetMusic().TriggerTransition("scene3");
  // Box2D
  CreateBorder();
  CreateCourt();
  CreateNet();
  model_.world.SetContactListener(this);
  const ofPoint right(768-256, 50);
  const float pause = 2.0;
  model_.dialogue
      .Speed(25.0)
      .FontSize(16.0)
      .Foreground(ofColor::black)
      .Position("right", right).Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.1); //bass sound
        volume_targets.push_back(0.5); //high arpeg v1
        volume_targets.push_back(0.0); //high arpeg v2
        volume_targets.push_back(0.0); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.0); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Message("I don't believe in gravity, \nI will surely win this match!", "right").Then([this] () {
        model_.served = false;
        model_.ball_in_play = true;
        model_.opponent_index = 0;
      })
      .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.2); //bass sound
        volume_targets.push_back(0.5); //high arpeg v1
        volume_targets.push_back(0.0); //high arpeg v2
        volume_targets.push_back(1.0); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.0); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Clear().Pause(pause)
  .Message("I have time, \nI will surely win this match!", "right").Then([this] () {
    model_.served = false;
    model_.ball_in_play = true;
    model_.opponent_index = 1;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.5); //bass sound
        volume_targets.push_back(0.2); //high arpeg v1
        volume_targets.push_back(0.0); //high arpeg v2
        volume_targets.push_back(1.0); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.0); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Clear().Pause(pause)
  .Message("I have many racquets, \nI will surely win this match!", "right").Then([this] () {
    model_.served = false;
    model_.ball_in_play = true;
    model_.opponent_index = 2;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.5); //bass sound
        volume_targets.push_back(0.1); //high arpeg v1
        volume_targets.push_back(0.0); //high arpeg v2
        volume_targets.push_back(1.0); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.0); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Clear().Pause(pause)
  .Message("We're playing a whole different game,\nwe will surely win this match!", "right").Then([this] () {
    model_.served = false;
    model_.ball_in_play = true;
    model_.opponent_index = 3;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.5); //bass sound
        volume_targets.push_back(0.0); //high arpeg v1
        volume_targets.push_back(0.3); //high arpeg v2
        volume_targets.push_back(0.0); //low arpeg v1
        volume_targets.push_back(1.0); //low arpeg v2
        volume_targets.push_back(0.0); //words 1
        volume_targets.push_back(0.2); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Clear().Pause(pause)
  .Message("I'm made of glass, \nI will surely win this match!", "right").Then([this] () {
    model_.served = false;
    model_.ball_in_play = true;
    model_.opponent_index = 4;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.5); //bass sound
        volume_targets.push_back(0.0); //high arpeg v1
        volume_targets.push_back(0.5); //high arpeg v2
        volume_targets.push_back(0.0); //low arpeg v1
        volume_targets.push_back(1.0); //low arpeg v2
        volume_targets.push_back(0.0); //words 1
        volume_targets.push_back(0.2); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
  }).Clear().Pause(pause).Then([this] () {
    std::cout << "NOW!" << std::endl;
    model_.served = true;
    model_.ball_in_play = true;
    model_.opponent_index = 5;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.5); //bass sound
        volume_targets.push_back(0.5); //high arpeg v1
        volume_targets.push_back(0.0); //high arpeg v2
        volume_targets.push_back(1.0); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.5); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      })
      .Message("I'm late, I wil...", "right").Pause(0.5).Clear().Pause(0.5)
  .Message("I'm a blank slate,\nI will surely win this match!", "right").Then([this] () {
    model_.served = false;
    model_.ball_in_play = true;
    model_.opponent_index = 6;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.7); //bass sound
        volume_targets.push_back(0.5); //high arpeg v1
        volume_targets.push_back(0.0); //high arpeg v2
        volume_targets.push_back(1.0); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.2); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.2); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Clear().Pause(pause)
  .Message("I've spent my life studying this game,\nI will surely win this match!", "right").Then([this] () {
    model_.served = false;
    model_.ball_in_play = true;
    model_.opponent_index = 7;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.7); //bass sound
        volume_targets.push_back(0.2); //high arpeg v1
        volume_targets.push_back(0.0); //high arpeg v2
        volume_targets.push_back(0.5); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.1); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.1); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Clear().Pause(pause).Foreground(ofColor::white)
  .Message("I'm the score itself, \nI will surely win this match!", "right").Then([this] () {
    model_.served = true;
    model_.ball_in_play = true;
    model_.opponent_index = 8;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.5); //bass sound
        volume_targets.push_back(0.0); //high arpeg v1
        volume_targets.push_back(0.0); //high arpeg v2
        volume_targets.push_back(0.0); //low arpeg v1
        volume_targets.push_back(1.0); //low arpeg v2
        volume_targets.push_back(0.0); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Clear().Pause(pause).Foreground(ofColor::black)
  .Message("I'm you, \nI will surely win this match!", "right").Then([this] () {
    model_.served = false;
    model_.ball_in_play = true;
    model_.opponent_index = 9;
  })
      .Barrier("point").Clear();
}

void Scene3Controller::Update() {
  model_.dialogue.Update();
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
  if (model_.ball_in_play && !model_.ball_body) {
    CreateBall(ofVec2f(0.25 * half_court_length, court_height), ofVec2f(0, 0), 0.0, -ofRandomuf() * angular_velocity);
    model_.opponent = model_.opponent_target = ofVec2f(half_court_length, racket_radius + court_thickness);
  }
  if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
    if (model_.ball_body) {
      DestroyBall(model_.ball_body);
      model_.ball_body = nullptr;
    }
  }
  if (model_.angle <= 180.0 - 180.0 / 60.0 / 2.0) {
    model_.angle += 180.0 / 60.0 / 2.0;
  }
  Controller::Update();
}

Model &Scene3Controller::model() {
  return model_;
}

/**
 * Private method defintions.
 */
void Scene3Controller::CreateBall(ofVec2f position, ofVec2f velocity,
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

void Scene3Controller::CreateBorder() {
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

void Scene3Controller::CreateCourt() {
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

void Scene3Controller::CreateNet() {
  b2BodyDef net_body_definition;
  net_body_definition.position.Set(0.0, court_thickness);
  model_.net_body = model_.world.CreateBody(&net_body_definition);
  b2EdgeShape net_shape;
  net_shape.Set(b2Vec2(), b2Vec2(0.0, net_height));
  b2FixtureDef net_fixture_definition;
  net_fixture_definition.shape = &net_shape;
  model_.net_body->CreateFixture(&net_fixture_definition);
}

void Scene3Controller::DestroyBall(b2Body *ball) {
  ball->DestroyFixture(ball->GetFixtureList());
  model_.world.DestroyBody(ball);
}

bool Scene3Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}

void Scene3Controller::RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
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
      model_.bounces = 0;
      model_.served = true;
      hit1.setPan(racket_position.x / half_court_length);
      hit2.setPan(racket_position.x / half_court_length);
      ofRandomuf() > 0.5 ? hit1.play() : hit2.play();
    }
  }
}

void Scene3Controller::UpdateRackets() {
  model_.racket1 = Lerp(model_.racket1, model_.racket1_target, player_move_smooth_factor);
  model_.opponent = Lerp(model_.opponent, model_.opponent_target, player_move_smooth_factor);
  if (keys[OF_KEY_LEFT] && model_.racket1_target.x > -half_court_length) {
    model_.racket1_target.x -= racket_speed;
  }
  if (keys[OF_KEY_RIGHT] && model_.racket1_target.x < -racket_speed - racket_radius) {
    model_.racket1_target.x += racket_speed;
  }
  if (model_.score != 5 && model_.opponent_index != 8) {
    // opponent
    if (model_.ball_body && model_.ball_body->GetPosition().x > 0) {
      const float dx = model_.ball_body->GetPosition().x - model_.opponent_target.x;
      if (dx > racket_radius + ball_radius) {
        model_.opponent_target.x += racket_speed - ofNoise(ofGetElapsedTimef()) * racket_speed;
      } else if (dx < -racket_radius - ball_radius) {
        model_.opponent_target.x -= racket_speed - ofNoise(ofGetElapsedTimef()) * racket_speed;
      }
    } else {
      const float dx = ofSignedNoise(ofGetElapsedTimef()) * racket_speed;
      if (dx > 0 && model_.opponent_target.x < half_court_length) {
        model_.opponent_target.x += dx;
      }
      if (dx < 0 && model_.opponent_target.x > dx + racket_radius) {
        model_.opponent_target.x += dx;
      }
    }
  }
  RacketCollide(model_.racket1, racket1_low_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  if (model_.score != 5 && model_.opponent_index != 8) {
    RacketCollide(model_.opponent, racket2_low_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  }
}
