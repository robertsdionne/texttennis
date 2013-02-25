//
//  gamestate.h
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#ifndef __texttennis__gamestate__
#define __texttennis__gamestate__

#include <iostream>

#include "gameobject.h"
#include "ofMain.h"

class GameState {
public:
  GameState(GameObject ball, ofVec2f racket1, ofVec2f racket2, const std::list<ofVec2f> &trail);
  
  virtual ~GameState();
  
  GameObject ball;
  ofVec2f racket1;
  ofVec2f racket2;
  std::list<ofVec2f> trail;
};

#endif /* defined(__texttennis__gamestate__) */