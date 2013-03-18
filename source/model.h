#ifndef TEXTTENNIS_MODEL_H_
#define TEXTTENNIS_MODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "gamestate.h"
#include "ofMain.h"

class Model {
public:
  Model();
  
  virtual ~Model() {}
  
public:
  b2World world;
  
  std::list<b2Body *> ball_body;
  
  b2Body *court_body, *border_body, *net_body;
  
  ofVec2f racket1, racket2, mouse_position;
  
  std::list<GameState> states;
};

#endif  // TEXTTENNIS_MODEL_H_
