#ifndef TEXTTENNIS_SCENE4MODEL_H_
#define TEXTTENNIS_SCENE4MODEL_H_

#include <Box2D/Box2D.h>
#include <deque>
#include <list>

#include "dialogue.h"
#include "model.h"
#include "ofMain.h"

class Scene4Model : public Model {
public:
  Scene4Model(ofPoint player_position);
  
  virtual ~Scene4Model() {}

  struct Particle {
    ofVec2f position, velocity;
    float angle, angular_velocity, life;
  };
  
public:
  b2World world;
  b2Body *ball_body, *court_body, *border_body, *net_body;
  b2Body *tree_people[5];
  
  ofVec2f racket1;
  ofVec2f racket1_target;

  int score;

  int bounces;
  float time_scale;
  bool reset_ball;

  std::deque<ofPoint> ball_trail, noise;
  std::deque<float> time_scales;

  std::vector<ofPoint> points;
  Dialogue dialogue;

  bool done = false;
  bool rising[5] = {false, false, false, false, false};
  float heights[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

  std::vector<Particle> particles;
};

#endif  // TEXTTENNIS_SCENE4MODEL_H_
