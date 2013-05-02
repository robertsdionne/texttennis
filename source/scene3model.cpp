#include "constants.h"
#include "scene3model.h"

Scene3Model::Scene3Model(ofPoint player_position)
: world(gravity_vector), ball_body(), extra_balls(), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(player_position), opponent(racket2_start_position),
  racket1_target(player_position), opponent_target(racket2_start_position),
  score(0), angle(180.0), bounces(0), dialogue(), ball_in_play(false), opponent_visible(false),
  opponent_index(0), served(false), time_slowed(false) {}
