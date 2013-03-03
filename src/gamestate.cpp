//
//  gamestate.cpp
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#include <list>

#include "gamestate.h"

GameState::GameState()
: balls(), racket1() {}

GameState::GameState(ofVec2f racket1)
: balls(), racket1(racket1) {}

GameState::~GameState() {}
