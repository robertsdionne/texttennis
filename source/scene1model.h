#ifndef TEXTTENNIS_SCENE1MODEL_H_
#define TEXTTENNIS_SCENE1MODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "gamestate.h"
#include "model.h"
#include "ofMain.h"

class Scene1Model : public Model {
public:
  Scene1Model();
  
  virtual ~Scene1Model() {}
  
public:
  b2World world;
  
  std::list<b2Body *> ball_body;
  
  b2Body *court_body, *border_body, *net_body;
  
  ofVec2f racket1, racket2;
  
  std::list<GameState> states;
};

#endif  // TEXTTENNIS_SCENE1MODEL_H_
