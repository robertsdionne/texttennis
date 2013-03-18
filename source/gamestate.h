#ifndef TEXTTENNIS_GAMESTATE_H_
#define TEXTTENNIS_GAMESTATE_H_

#include <list>

#include "gameobject.h"
#include "ofMain.h"

class GameState {
public:
  GameState(ofVec2f racket1 = ofVec2f(), ofVec2f racket2 = ofVec2f());
  
  virtual ~GameState();
  
  std::list<GameObject> balls;
  ofVec2f racket1;
  ofVec2f racket2;
};

#endif  // TEXTTENNIS_GAMESTATE_H_
