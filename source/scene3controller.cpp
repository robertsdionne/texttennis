#include "constants.h"
#include "scene3controller.h"
#include "model.h"
#include "ofMain.h"
#include "scene3model.h"
#include "texttennis.h"
#include "utilities.h"

Scene3Controller::Scene3Controller(TextTennis &scene_manager, Scene3Model &model)
: Controller(scene_manager), model_(model), cardtable(), glassbreak() {
  hit1.loadSound("hit.wav");
  hit2.loadSound("hit2.wav");
  bounce1.loadSound("bounce1.wav");
  bounce2.loadSound("bounce2.wav");
  bounce3.loadSound("bounce3.wav");
  bounce4.loadSound("bounce4.wav");
  cardtable.loadSound("cardtable.wav");
  cardtable.setPan(0.377);
  glassbreak.loadSound("glassbreak.wav");
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
  if (contact->GetFixtureA() == model_.eight_body->GetFixtureList()->GetNext() ||
      contact->GetFixtureB() == model_.eight_body->GetFixtureList()->GetNext()) {
    model_.ball_body->GetFixtureList()->SetRestitution(restitution);
  }
  if (ball && court) {
    if (model_.opponent_index == 3 && model_.bounces == 0) {
      cardtable.play();
      for (int i = 0; i < 13; ++i) {
        Scene3Model::Particle particle;
        particle.position = ofVec2f(0.377 * half_court_length, court_thickness + racket_radius);
        particle.velocity = ofVec2f(3.0 / 4.0 * ofRandomf(), ofRandomf() / 4.0);
        particle.angle = ofRandomf();
        particle.angular_velocity = 10.0 * ofRandomf();
        particle.life = 1.0;
        model_.particles.push_back(particle);
      }
    }
    if (model_.opponent_index == 7) {
      Scene3Model::Trail trail;
      trail.position = OpenFrameworksVector(model_.ball_body->GetPosition());
      trail.text = "Bounce";
      model_.ball_trail.push_back(trail);
    }
    if (model_.opponent_index == 8 && !model_.eight_on_left_side) {
      model_.opponent_target.x = model_.opponent.x = ball->GetPosition().x;
      if (model_.opponent.x < 0.0) {
        model_.eight_on_left_side = true;
      }
    }
    if (model_.opponent_index == 8 && !model_.eight_on_left_side) {
      for (int i = 0; i < 13; ++i) {
        Scene3Model::Particle particle;
        particle.position = ofVec2f(model_.opponent.x, court_thickness + racket_radius);
        particle.velocity = ofVec2f(ofRandomf(), ofRandomf());
        particle.angle = ofRandomf();
        particle.angular_velocity = 10.0 * ofRandomf();
        particle.life = 1.0;
        model_.particles.push_back(particle);
      }
    }
  }
  if (ball && court && ball->GetPosition().x > 0 && model_.served) {
    model_.bounces += 1;
    if (model_.opponent_index != 9 && model_.bounces == ((model_.opponent_index == 5) ? 8 : 2)) {
      model_.angle = 0.0;
      model_.score += 1;
      model_.ball_in_play = false;
      if (model_.opponent_index == 5) {
        model_.opponent = model_.opponent_target = ofVec2f(half_court_length, racket_radius + court_thickness);
      }
      model_.dialogue.Trigger("point");
    } else if (model_.opponent_index == 9 && model_.bounces == 2) {
      if (model_.mirror_score < 2) {
        model_.mirror_score += 1;
        model_.ball_in_play = false;
        model_.dialogue.Trigger("score");
      } else {
        model_.angle = 0.0;
        model_.score += 1;
        model_.ball_in_play = false;
        model_.dialogue.Trigger("point");
      }
    }
  } else if (ball && court && ball->GetPosition().x < 0) {
    model_.bounces = 0;
  }
  if (ball) {
    bounce1.setPan(ball->GetPosition().x / half_court_length);
    bounce2.setPan(ball->GetPosition().x / half_court_length);
    bounce3.setPan(ball->GetPosition().x / half_court_length);
    bounce4.setPan(ball->GetPosition().x / half_court_length);

    if (ofRandomuf() < 0.5) {
      if (ofRandomuf() < 0.5) {
        bounce1.setSpeed(ofRandom(0.8, 1.2));
        bounce1.play();
      } else {
        bounce2.setSpeed(ofRandom(0.8, 1.2));
        bounce2.play();
      }
    } else {
      if (ofRandomuf() < 0.5) {
        bounce3.setSpeed(ofRandom(0.8, 1.2));
        bounce3.play();
      } else {
        bounce4.setSpeed(ofRandom(0.8, 1.2));
        bounce4.play();
      }
    }
  }
}

void Scene3Controller::Setup() {
  // Box2D
  CreateBorder();
  CreateCourt();
  CreateEight();
  CreateNet();
  model_.world.SetContactListener(this);
  const ofPoint right(768-256, 50);
  const float pause = 2.0;
  model_.dialogue
      .Speed(25.0)
      .PunctuationDelay(0.0)
      .FontSize(16.0)
      .Foreground(ofColor::black)
      .Position("court", ofPoint(768, 600))
      .Position("right", right)
      .Position("below", right + ofVec2f(0, 100)).Then([this] () {
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
        volume_targets.push_back(0.3); //high arpeg v1
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
        volume_targets.push_back(0.2); //high arpeg v1
        volume_targets.push_back(0.0); //high arpeg v2
        volume_targets.push_back(1.0); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.0); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Clear().Pause(pause)
  .Message("We're playing a whole different game,\nwe will surely win this match!", "right").Then([this] () {
    model_.served = true;
    model_.ball_in_play = true;
    model_.opponent_index = 3;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.5); //bass sound
        volume_targets.push_back(0.2); //high arpeg v1
        volume_targets.push_back(0.0); //high arpeg v2
        volume_targets.push_back(0.9); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.0); //words 1
        volume_targets.push_back(0.3); //words 2
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
        volume_targets.push_back(0.3); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
  }).Clear().Pause(pause).Then([this] () {
    model_.served = true;
    model_.ball_in_play = true;
    model_.opponent_index = 5;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.5); //bass sound
        volume_targets.push_back(0.0); //high arpeg v1
        volume_targets.push_back(0.5); //high arpeg v2
        volume_targets.push_back(1.0); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.6); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.0); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      })
      .Message("I'm late, I will...", "court").Pause(0.5).Clear().Pause(0.5)
  .Message("I'm a blank slate,\nI will surely win this match!", "right").Then([this] () {
    model_.served = false;
    model_.ball_in_play = true;
    model_.opponent_index = 6;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.7); //bass sound
        volume_targets.push_back(0.0); //high arpeg v1
        volume_targets.push_back(0.5); //high arpeg v2
        volume_targets.push_back(1.0); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.4); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.4); //words 3
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
        volume_targets.push_back(0.0); //high arpeg v1
        volume_targets.push_back(0.3); //high arpeg v2
        volume_targets.push_back(0.5); //low arpeg v1
        volume_targets.push_back(0.0); //low arpeg v2
        volume_targets.push_back(0.4); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.4); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Clear().Pause(pause).Foreground(ofColor::white)
  .Message("I'm the score itself, \nI will surely win this match!", "right").Then([this] () {
    model_.eight_body->SetActive(true);
    model_.served = false;
    model_.ball_in_play = true;
    model_.opponent_index = 8;
  })
  .Barrier("point").Then([this] () {
        std::vector<float> volume_targets;
        volume_targets.push_back(0.9); //bass sound
        volume_targets.push_back(0.0); //high arpeg v1
        volume_targets.push_back(0.2); //high arpeg v2
        volume_targets.push_back(0.0); //low arpeg v1
        volume_targets.push_back(1.0); //low arpeg v2
        volume_targets.push_back(0.5); //words 1
        volume_targets.push_back(0.0); //words 2
        volume_targets.push_back(0.5); //words 3
        scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
      }).Clear().Pause(pause).Foreground(ofColor::black)
  .Message("I'm you, \nI will surely win this match!", "right").Then([this] () {
    model_.eight_body->SetActive(false);
    model_.served = false;
    model_.ball_in_play = true;
    model_.opponent_index = 9;
  })
  .Barrier("score").Then([this] () {
    model_.served = false;
    model_.ball_in_play = true;
  }).Barrier("score").Then([this] () {
    model_.served = false;
    model_.ball_in_play = true;
  }).Barrier("point").Clear();
}

void Scene3Controller::Update() {
  model_.dialogue.Update();
  if (model_.score >= 10) {
    scene_manager.NextScene();
    return;
  }
  if (model_.bounces >= ((model_.opponent_index == 5) ? 8 : 2)) {
    DestroyBall(model_.ball_body);
    model_.ball_body = nullptr;
    model_.bounces = 0;
  }
  if (model_.opponent_index != 2 && model_.extra_balls.size()) {
    for (auto ball : model_.extra_balls) {
      model_.world.DestroyBody(ball);
    }
    model_.extra_balls.clear();
  }
  UpdateRackets();
  model_.world.Step(model_.time_slowed ? 0.1 * delta_time : delta_time, box2d_velocity_iterations, box2d_position_iterations);

  for (std::vector<Scene3Model::Particle>::iterator particle = model_.particles.begin(); particle != model_.particles.end(); ++particle) {
    particle->angle += particle->angular_velocity * delta_time;
    particle->position += particle->velocity * delta_time;
    particle->velocity += -ofVec2f(0.0, 0.5) * delta_time;
    particle->life -= 1.0 / 60.0 / 8.0;
  }
  model_.particles.erase(std::remove_if(model_.particles.begin(), model_.particles.end(), [] (Scene3Model::Particle &particle) -> bool {
    return particle.life <= 0.0;
  }), model_.particles.end());
  
  if (model_.ball_trail.size() > ball_trail_length_scholar || (model_.opponent_index != 7 && model_.ball_trail.size() >  0)) {
    model_.ball_trail.pop_front();
  }
  if (model_.ball_body && model_.opponent_index == 7) {
    Scene3Model::Trail trail;
    trail.position = OpenFrameworksVector(model_.ball_body->GetPosition());
    trail.text = nullptr;
    model_.ball_trail.push_back(trail);
  }
  if (model_.ball_in_play && !model_.ball_body) {
    CreateBall(ofVec2f(0.377 * half_court_length, court_height), ofVec2f(0, 0), 0.0, -ofRandomuf() * angular_velocity);
    if (model_.opponent_index == 8) {
      model_.ball_body->GetFixtureList()->SetRestitution(0.0);
    }
    if (!(model_.opponent_index == 9 && model_.mirror_score > 0)) {
      model_.opponent = model_.opponent_target = ofVec2f(half_court_length, racket_radius + court_thickness);
    }
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
  if (model_.glass_hits == 2 && model_.glass <= 1.0 - 1.0 / 60.0) {
    model_.glass += 1.0 / 60.0;
  }
  if (model_.glass_hits > 2 && model_.glass <= 1.0 - 1.0 / 60.0) {
    model_.glass += 1.0 / 60.0;
  }
  if (model_.opponent_index == 7 && model_.nerd_energy >= 1.0 / 60.0 / 30.0) {
    model_.nerd_energy -= 1.0 / 60.0 / 30.0;
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

void Scene3Controller::CreateEight() {
  b2BodyDef eight_body_definition;
  eight_body_definition.position.Set(0.0, 0.0);
  model_.eight_body = model_.world.CreateBody(&eight_body_definition);
  b2EdgeShape edge_0, edge_1, edge_2, edge_3;
  edge_0.Set(b2Vec2(4.52842, 10.845), b2Vec2(3.97107, 10.2412));
  edge_1.Set(b2Vec2(3.4834, 10.3341), b2Vec2(8.84783, 5.92178));
  edge_2.Set(b2Vec2(9.26584, 5.66633), b2Vec2(9.26584, 6.66633));
  edge_3.Set(b2Vec2(9.46773, 6.01467), b2Vec2(6.54879, 2.71705));
  b2FixtureDef eight_fixture_definition;
  eight_fixture_definition.shape = &edge_0;
  model_.eight_body->CreateFixture(&eight_fixture_definition);
  eight_fixture_definition.shape = &edge_1;
  model_.eight_body->CreateFixture(&eight_fixture_definition);
  eight_fixture_definition.shape = &edge_2;
  model_.eight_body->CreateFixture(&eight_fixture_definition);
  eight_fixture_definition.shape = &edge_3;
  model_.eight_body->CreateFixture(&eight_fixture_definition);
  model_.eight_body->SetActive(false);
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
                                     float hit_mean, int key_left, int key_right, bool opponent) {
  if (model_.ball_body) {
    const ofVec2f position = ofVec2f(model_.ball_body->GetPosition().x,
                                     model_.ball_body->GetPosition().y);
    const float dx = model_.ball_body->GetLinearVelocity().x;
    const float probability = model_.opponent_index == 8 ? 1.0 : 0.1;
    if (ofRandomuf() < probability && abs((position - racket_position).x) < ball_radius + 2.0 * racket_radius
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
      if (opponent && model_.opponent_index == 1) {
        model_.time_slowed = true;
      }
      if (!opponent && model_.opponent_index == 1) {
        model_.time_slowed = false;
      }
      if (opponent && model_.opponent_index == 8) {
        model_.bounces += 1;
      }
      if (opponent && model_.opponent_index == 2) {
        for (int i = 0; i < 4; ++i) {
          b2BodyDef ball_body_definition;
          ball_body_definition.type = b2_dynamicBody;
          ball_body_definition.position.Set(model_.ball_body->GetPosition().x + 0.1 * ofRandomf(),
                                            model_.ball_body->GetPosition().y + 0.1 * ofRandomf());
          ball_body_definition.linearVelocity.Set(model_.ball_body->GetLinearVelocity().x + 3.0 * ofRandomf(),
                                                  model_.ball_body->GetLinearVelocity().y + 0.25 * ofRandomf());
          ball_body_definition.angle = model_.ball_body->GetAngle();
          ball_body_definition.angularVelocity = model_.ball_body->GetAngularVelocity();
          ball_body_definition.linearDamping = linear_damping;
          ball_body_definition.angularDamping = angular_damping;
          model_.extra_balls.push_back(model_.world.CreateBody(&ball_body_definition));
          b2CircleShape ball_shape;
          ball_shape.m_radius = ball_radius;
          b2FixtureDef ball_fixture_definition;
          ball_fixture_definition.shape = &ball_shape;
          ball_fixture_definition.density = density;
          ball_fixture_definition.restitution = restitution;
          ball_fixture_definition.friction = friction;
          model_.extra_balls.back()->CreateFixture(&ball_fixture_definition);
        }
      }
      if (opponent && model_.opponent_index == 4 && ofGetElapsedTimef() > model_.last_hit + 0.3) {
        if (model_.glass_hits == 0) {
          model_.served = true;
        }
        if (model_.glass_hits <= 2) {
          model_.glass = 0.0;
        }
        model_.glass_hits += 1;
        if (model_.glass_hits == 3) {
          glassbreak.setPan(model_.opponent.x / half_court_length);
          glassbreak.play();
          for (int i = 0; i < 100; ++i) {
            Scene3Model::Particle particle;
            particle.position = model_.opponent + ofVec2f(racket_radius * ofRandomf(), 4.0 * racket_radius * ofRandomuf());
            particle.velocity = ofVec2f(3.0 / 4.0 * ofRandomf(), ofRandomf() / 4.0);
            particle.angle = ofRandomf();
            particle.angular_velocity = 10.0 * ofRandomf();
            particle.life = 1.0;
            model_.particles.push_back(particle);
          }
        }
      }
      if (model_.opponent_index == 7) {
        Scene3Model::Trail trail;
        trail.position = OpenFrameworksVector(model_.ball_body->GetPosition());
        trail.text = "Volley";
        model_.ball_trail.push_back(trail);
      }
      model_.served = true;
      hit1.setSpeed(ofRandom(0.8, 1.2));
      hit2.setSpeed(ofRandom(0.8, 1.2));
      hit1.setPan(racket_position.x / half_court_length);
      hit2.setPan(racket_position.x / half_court_length);

      if (ofGetElapsedTimef() > model_.last_hit + 0.3) {
        ofRandomuf() > 0.5 ? hit1.play() : hit2.play();
      }
      model_.last_hit = ofGetElapsedTimef();
    }
  }
}

void Scene3Controller::UpdateRackets() {
  model_.racket1 = Lerp(model_.racket1, model_.racket1_target, player_move_smooth_factor);
  if (model_.opponent_index == 7) {
    model_.opponent = Lerp(model_.opponent, model_.opponent_target, player_move_smooth_factor * model_.nerd_energy);
  } else {
    model_.opponent = Lerp(model_.opponent, model_.opponent_target, player_move_smooth_factor);
  }
  if (keys[OF_KEY_LEFT] && model_.racket1_target.x > -half_court_length) {
    model_.racket1_target.x -= racket_speed;
  }
  if (keys[OF_KEY_RIGHT] && model_.racket1_target.x < -racket_speed - racket_radius) {
    model_.racket1_target.x += racket_speed;
  }
  if (model_.score != 5 && model_.opponent_index != 8 && model_.opponent_index != 3
      && model_.opponent_index != 9 && model_.opponent_index != 7 && model_.opponent_index != 4) {
    if (model_.opponent_index == 0) {
      const float dy = ofNoise(-ofGetElapsedTimef()) * racket_speed / 10.0;
      model_.opponent_target.y += dy;
    }
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
  if (model_.opponent_index == 3) {
    model_.opponent_target.x = .377 * half_court_length;
  }
  if (model_.opponent_index == 5 && model_.score != 5) {
    model_.opponent_target.x = 7;
  }
  if (model_.opponent_index == 7 || (model_.opponent_index == 4 && model_.glass_hits < 3)) {
    if (model_.ball_body && model_.ball_body->GetPosition().x > 0) {
      const float dx = model_.ball_body->GetLinearVelocity().x;
      model_.opponent_target.x = model_.ball_body->GetPosition().x + 3.0 * dx * delta_time;
      model_.opponent_target.x = max(model_.opponent_target.x, racket_radius.GetValue());
    } else {
      model_.opponent_target.x = racket_radius + (half_court_length - 2.0 * racket_radius) * ofNoise(ofGetElapsedTimef());
    }
  }
  if (model_.opponent_index == 9) {
    model_.opponent_target.x = -model_.racket1_target.x;
  }
  RacketCollide(model_.racket1, racket1_low_hit_direction, low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT);
  if (model_.score != 5 && model_.opponent_index != 3 && model_.opponent_index != 4) {
    RacketCollide(model_.opponent, model_.opponent_index == 6 ?
                  -racket2_low_hit_direction.GetValue() : racket2_low_hit_direction,
                  low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT, true);
  }
  if (model_.opponent_index == 4 && model_.glass_hits < 3) {
    RacketCollide(model_.opponent, model_.opponent_index == 6 ?
                  -racket2_low_hit_direction.GetValue() : racket2_low_hit_direction,
                  low_hit_mean, OF_KEY_LEFT, OF_KEY_RIGHT, true);
  }
}
