#include "constants.h"
#include "scene4controller.h"
#include "model.h"
#include "ofMain.h"
#include "scene4model.h"
#include "texttennis.h"
#include "utilities.h"

Scene4Controller::Scene4Controller(TextTennis &scene_manager, Scene4Model &model)
: Controller(scene_manager), model_(model) {
  for (int i = 0; i < 5; ++i) {
    std::stringstream out;
    out << "tree" << (i + 1);
    tree[i] = out.str();
  }
  hit1.loadSound("hit1.mp3");
  hit2.loadSound("hit2.mp3");
  bounce1.loadSound("bounce1.wav");
  bounce2.loadSound("bounce2.wav");
  bounce3.loadSound("bounce3.wav");
  bounce4.loadSound("bounce4.wav");
}

Scene4Controller::~Scene4Controller() {
}

void Scene4Controller::BeginContact(b2Contact* contact) {
  const b2Body *body_a = contact->GetFixtureA()->GetBody();
  const b2Body *body_b = contact->GetFixtureB()->GetBody();
  const b2Body *ball = nullptr, *other = nullptr;
  if (model_.ball_body == body_a) {
    ball = body_a;
    other = body_b;
  }
  if (model_.ball_body == body_b) {
    ball = body_b;
    other = body_a;
  }
  if (ball && other) {
    if (other == model_.court_body && ball->GetPosition().x > 0) {
      model_.bounces += 1;
      model_.rising[4 - model_.score] = true;
      model_.dialogue.Trigger("collide");
      scene_manager.GetMusic().PlaySoundEffect(tree[model_.score]);
      model_.score += 1;
      model_.reset_ball = true;
      if (model_.time_scale == 1.0) {
        model_.time_scale = 1.0 / 6.0;
        hit1.setVolume(0.0);
        hit2.setVolume(0.0);
        bounce1.setVolume(0.0);
        bounce2.setVolume(0.0);
        bounce3.setVolume(0.0);
        bounce4.setVolume(0.0);
      }
    } else if (other == model_.court_body && ball->GetPosition().x < 0) {
      model_.bounces = 0;
    }
  }

  if (model_.ball_body) {
    bounce1.setPan(model_.ball_body->GetPosition().x / half_court_length);
    bounce2.setPan(model_.ball_body->GetPosition().x / half_court_length);
    bounce3.setPan(model_.ball_body->GetPosition().x / half_court_length);
    bounce4.setPan(model_.ball_body->GetPosition().x / half_court_length);
  }
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

void Scene4Controller::Setup() {
  //scene_manager.GetMusic().TriggerTransition("scene4");
  // Box2D
  CreateBorder();
  CreateCourt();
  CreateNet();
  CreateTreePeople();
  model_.world.SetContactListener(this);
  const float duration = 15.0;
  model_.dialogue
      .Speed(10.0)
      .Mute()
      .Foreground(ofColor::white)
      .Background(ofColor::black)
      .Position("tree0", ofPoint(512, 100))
      .Position("tree1", ofPoint(512, 180))
      .Position("tree2", ofPoint(512, 245))
      .Position("tree3", ofPoint(512, 295))
      .Position("tree4", ofPoint(512, 330))
      .Barrier("collide").Speed(4.0 / 3.0 * 69.0 / duration)
      .Message("Ladies and gentlemen,\nwe are proud to present\na short story,\n\"Nothing is real.\"", "tree0") // 69
      .Barrier("collide").Speed(4.0 / 3.0 * 51.0 / duration)
      .Message("The trees and\nthe tree people\nwere in disagreement.", "tree1") // 51
      .Barrier("collide").Speed(4.0 / 3.0 * 37.0 / duration)
      .Message("\"Let's work it out,\"\none person said.", "tree2") // 37
      .Barrier("collide").Speed(4.0 / 3.0 * 20.0 / duration)
      .Message("But nothing changed.", "tree3") // 20
      .Barrier("collide").Speed(4.0 / 3.0 * 8.0 / duration)
  .Message("The end.", "tree4").Pause(12.0).Then([this] () {
    model_.done = true;
  }); // 8
}

void Scene4Controller::Update() {
  if (model_.done) {
    scene_manager.NextScene();
    return;
  }
  model_.dialogue.Update();
  if (model_.reset_ball) {
    if (model_.ball_body) {
      DestroyBall(model_.ball_body);
      model_.ball_body = nullptr;
    }
    //model_.ball_trail.clear();
    model_.reset_ball = false;
  }
  for (int i = 0; i < 5; ++i) {
    if (model_.rising[i] && model_.heights[i] <= 1.0 - 1.0 / 60.0 / 24.0) {
      model_.heights[i] += 1.0 / 60.0 / 24.0;
    }
  }
//  for (int i = 0; i < 5; ++i) {
//    if (4 - i == model_.score) {
//      model_.tree_people[i]->SetActive(true);
//    } else {
//      model_.tree_people[i]->SetActive(false);
//    }
//  }
  if (model_.score >= 6) {
    scene_manager.NextScene();
    return;
  }
  if (keys['-'] && !previous_keys['-']) {
    model_.points.clear();
  }
  if (buttons[0] && !previous_buttons[0]) {
    model_.points.push_back(model_.mouse_position);
  }
  if (model_.bounces >= max(2, model_.score)) {
    DestroyBall(model_.ball_body);
    model_.ball_body = nullptr;
    model_.bounces = 0;
  }
  UpdateRackets();
  model_.world.Step(delta_time * model_.time_scale, box2d_velocity_iterations, box2d_position_iterations);
  if (model_.ball_trail.size() > ball_trail_length) {
    model_.ball_trail.pop_front();
    model_.noise.pop_front();
    model_.time_scales.pop_front();
  }
  if (model_.ball_body) {
    model_.ball_trail.push_back(OpenFrameworksVector(model_.ball_body->GetPosition()));
    model_.noise.push_back(2.0 * ofVec2f(ofSignedNoise(model_.time_scale * 8.0 * ofGetElapsedTimef()), ofSignedNoise(model_.time_scale * -8.0 * ofGetElapsedTimef())));
    model_.time_scales.push_back(model_.time_scale);
  }
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


/*
 Tree1 bounding polygon:
 (8.68527, 0.464453)
 (8.47627, 6.6649)
 (8.61561, 9.75352)
 (9.61418, 11.054)
 (10.7289, 11.0075)
 (11.5881, 9.9393)
 (11.7739, 7.77959)
 (11.8203, 2.80994)
 (11.7042, 0.487676)
 */

/*
 Tree2 bounding polygon:
 (7.31514, 0.510899)
 (6.71135, 3.73885)
 (6.61846, 7.4777)
 (6.89713, 9.10328)
 (7.1758, 9.54451)
 (7.73314, 10.1251)
 (8.49949, 10.1483)
 (9.2194, 9.03361)
 (9.40518, 7.4777)
 (9.52129, 3.87818)
 (9.26584, 0.510899)
 */

/*
 Tree3 bounding polygon:
 (5.66633, 0.464453)
 (4.89998, 2.80994)
 (4.59809, 6.29334)
 (4.78387, 7.40803)
 (5.45732, 8.31371)
 (6.13078, 8.4066)
 (6.64168, 7.70992)
 (7.12936, 6.52557)
 (7.33836, 4.38908)
 (6.99002, 2.09004)
 (6.47912, 0.487676)
 */

/*
 Tree4 bounding polygon:
 (2.67061, 0.464453)
 (2.92605, 5.80566)
 (3.01895, 7.24547)
 (3.9943, 7.8957)
 (4.73742, 7.77959)
 (5.34121, 5.736)
 (5.75922, 1.81137)
 (5.736, 0.510899)
 */

/*
 Tree5 bounding polygon:
 (0.232226, 6.06111)
 (3.13506, 6.03789)
 (3.13506, 0.673457)
 (2.32227, 0.487676)
 (1.09146, 0.464453)
 (0.0696678, 1.16113)
 */

void Scene4Controller::CreateTreePeople() {
  float offset = 2.0;
  for (int i = 0; i < 5; ++i) {
    const float radius = 1.0;
    const float next_radius = 1.0;

    b2BodyDef person_definition;
    person_definition.position.Set(offset, court_thickness + radius);
    person_definition.active = false;
    model_.tree_people[i] = model_.world.CreateBody(&person_definition);
    b2CircleShape person_shape;
    person_shape.m_radius = radius;
    b2FixtureDef person_fixture_definition;
    person_fixture_definition.shape = &person_shape;
    model_.tree_people[i]->CreateFixture(&person_fixture_definition);

    offset += radius + next_radius + 2.0 * ball_radius;
    
    model_.tree_people[i]->SetActive(false);
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
    if (ofRandomuf() < 0.1 && abs((position - racket_position).x) < ball_radius + 2.0 * racket_radius
        && abs((position - racket_position).y) < ball_radius + 2.0 * racket_radius) {
      if (4 - model_.score > -1) {
        const float angle[] = {
          80.0,
          50.0,
          40.0,
          30.0,
          20.0
        };
        const ofVec2f target = OpenFrameworksVector(model_.tree_people[4 - model_.score]->GetPosition());
        const float range = target.x - model_.ball_body->GetPosition().x;
        const float speed = sqrt(range * gravity / sin(2.0 * ofDegToRad(angle[4 - model_.score])));
        const b2Vec2 velocity = Box2dVector(ofVec2f(1, 0).rotated(angle[4 - model_.score]) * speed);
        model_.ball_body->SetLinearVelocity(velocity);
        model_.ball_body->SetAngularVelocity(0.0);
        model_.bounces = 0;
        hit1.setPan(racket_position.x / half_court_length);
        hit2.setPan(racket_position.x / half_court_length);
        ofRandomuf() > 0.5 ? hit1.play() : hit2.play();
      }
    }
  }
}

void Scene4Controller::UpdateRackets() {
  model_.racket1 = Lerp(model_.racket1, model_.racket1_target, player_move_smooth_factor);
  if (keys[OF_KEY_LEFT] && model_.racket1_target.x > -half_court_length) {
    model_.racket1_target.x -= racket_speed * model_.time_scale;
  }
  if (keys[OF_KEY_RIGHT] && model_.racket1_target.x < -racket_speed * model_.time_scale - racket_radius) {
    model_.racket1_target.x += racket_speed * model_.time_scale;
  }
  RacketCollide(model_.racket1, racket1_low_hit_direction, 16.0, OF_KEY_LEFT, OF_KEY_RIGHT);
}
