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
  struct Trail {
    Trail() : position(), text(nullptr) {}
    ofVec2f position;
    const char *text;
  };
  
  GameState(GameObject ball, bool collided_with_net, ofVec2f racket1, const std::list<Trail> &trail);
  
  virtual ~GameState();
  
  std::list<GameObject> balls;
  ofVec2f racket1;
  std::list<Trail> trail;
};

#endif /* defined(__texttennis__gamestate__) */
