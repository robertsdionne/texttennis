//
//  gamestate.cpp
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#include "gamestate.h"

GameState::GameState(GameObject ball, bool collided_with_net, ofVec2f racket1, ofVec2f racket2, const std::list<Trail> &trail)
: ball(ball), racket1(racket1), racket2(racket2), trail(trail), collided_with_net(collided_with_net) {}

GameState::~GameState() {}
