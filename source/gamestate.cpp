#include <list>

#include "gamestate.h"

GameState::GameState(ofVec2f racket1, ofVec2f racket2)
: balls(), racket1(racket1), racket2(racket2) {}

GameState::~GameState() {}
