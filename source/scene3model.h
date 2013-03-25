#ifndef TEXTTENNIS_SCENE3MODEL_H_
#define TEXTTENNIS_SCENE3MODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "model.h"
#include "ofMain.h"

class Scene3Model : public Model {
public:
  Scene3Model();
  
  virtual ~Scene3Model() {}
  
public:
  b2World world;

  b2Body *ball_body, *court_body, *border_body, *net_body;
  
  ofVec2f racket1, opponent;

  float score;

  int bounces;
};

#endif  // TEXTTENNIS_SCENE3MODEL_H_
