#ifndef TEXTTENNIS_SCENE1MODEL_H_
#define TEXTTENNIS_SCENE1MODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "dialogue.h"
#include "model.h"
#include "ofMain.h"

class Scene1Model : public Model {
public:
  Scene1Model();
  
  virtual ~Scene1Model() {}
  
public:
  b2World world;
  b2Body *ball_body, *court_body, *border_body, *net_body;
  
  ofVec2f racket1, racket2;
  ofVec2f racket1_target, racket2_target;
  ofVec2f racket2_velocity;

  float scene_start_time;
  float rotation;
  float title;

  Dialogue dialogue;
};

#endif  // TEXTTENNIS_SCENE1MODEL_H_
