//
//  gamestate.cpp
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#include "gamestate.h"

GameState::GameState(GameObject ball, bool collided_with_net, ofVec2f racket1, const std::list<Trail> &trail)
: balls(), racket1(racket1), trail(trail) {
  balls.push_back(ball);
}

GameState::~GameState() {}
