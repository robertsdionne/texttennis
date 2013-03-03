//
//  gamestate.h
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#ifndef __texttennis__gamestate__
#define __texttennis__gamestate__

#include <list>

#include "gameobject.h"
#include "ofMain.h"

class GameState {
public:
  GameState();
  
  GameState(ofVec2f racket1);
  
  virtual ~GameState();
  
  std::list<GameObject> balls;
  ofVec2f racket1;
};

#endif /* defined(__texttennis__gamestate__) */
