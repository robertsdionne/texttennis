#include "constants.h"
#include "introductioncontroller.h"
#include "introductionmodel.h"
#include "texttennis.h"
#include "utilities.h"

IntroductionController::IntroductionController(TextTennis &scene_manager, IntroductionModel &model)
: Controller(scene_manager), model_(model) {}

IntroductionController::~IntroductionController() {}

void IntroductionController::Setup() {
  scene_manager.GetMusic().TriggerTransition("introduction");
}

void IntroductionController::Update() {
  if (AnyButtonPressed() || AnyKeyPressed()) {
    scene_manager.NextScene();
    return;
  }
  while (ofGetElapsedTimef() > model_.last_create_time + IntroductionModel::create_delay) {
    CreateBox(ofVec2f(1.0, court_height + 1 + ofRandomf()), ofVec2f(),
              ofRandomuf() * M_PI, ofRandomf() * 10.0);
    model_.last_create_time = ofGetElapsedTimef();
  }
  model_.world.Step(delta_time * 0.1, box2d_velocity_iterations, box2d_position_iterations);
  for (auto box = model_.boxes.begin(); box != model_.boxes.end(); ++box) {
    if ((*box)->GetPosition().x < -half_court_length) {
      (*box)->SetTransform((*box)->GetPosition() + b2Vec2(court_length, 0.0), (*box)->GetAngle());
    }
    if ((*box)->GetPosition().x > half_court_length) {
      (*box)->SetTransform((*box)->GetPosition() + b2Vec2(-court_length, 0.0), (*box)->GetAngle());
    }
    if ((*box)->GetPosition().y < -1.0) {
      (*box)->DestroyFixture((*box)->GetFixtureList());
      model_.world.DestroyBody(*box);
      model_.boxes.erase(box);
    }
  }
  Controller::Update();
}

Model &IntroductionController::model() {
  return model_;
}

void IntroductionController::CreateBox(ofVec2f position, ofVec2f velocity,
                                       float angle, float angular_velocity) {
  b2BodyDef box_definition;
  box_definition.type = b2_dynamicBody;
  box_definition.position.Set(position.x, position.y);
  box_definition.linearVelocity.Set(velocity.x, velocity.y);
  box_definition.angle = angle;
  box_definition.angularVelocity = angular_velocity;
  box_definition.linearDamping = linear_damping;
  box_definition.angularDamping = angular_damping;
  model_.boxes.push_back(model_.world.CreateBody(&box_definition));
  b2PolygonShape box_shape;
  box_shape.SetAsBox(0.25, 0.25);
  b2FixtureDef box_fixture_definition;
  box_fixture_definition.shape = &box_shape;
  box_fixture_definition.density = density;
  box_fixture_definition.restitution = 0.0;
  box_fixture_definition.friction = friction;
  model_.boxes.back()->CreateFixture(&box_fixture_definition);
}
