//
//  gamestate.cpp
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#include "gamestate.h"

GameState::GameState(GameObject ball, ofVec2f racket1, ofVec2f racket2, const std::list<ofVec2f> &trail)
: ball(ball), racket1(racket1), racket2(racket2), trail(trail) {}

GameState::~GameState() {}
