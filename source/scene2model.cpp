#include "constants.h"
#include "scene2model.h"

Scene2Model::Scene2Model(ofPoint player_position)
: world(gravity_vector), ball_body(), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(player_position), racket1_target(player_position),
  score(), dialogue("weird4.wav") {}
