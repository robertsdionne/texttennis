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
  
  std::list<b2Body *> ball_body;
  
  b2Body *court_body, *border_body, *net_body;
  
  ofVec2f racket1;

  float score;
};

#endif  // TEXTTENNIS_SCENE3MODEL_H_
