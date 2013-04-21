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
  Scene4Model();
  
  virtual ~Scene4Model() {}
  
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
};

#endif  // TEXTTENNIS_SCENE4MODEL_H_
