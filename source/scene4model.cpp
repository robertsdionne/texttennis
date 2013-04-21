#include "constants.h"
#include "scene4model.h"

Scene4Model::Scene4Model()
: world(gravity_vector), ball_body(), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), tree_people(), racket1(racket1_start_position),
  racket1_target(racket1_start_position), score(0), bounces(0), time_scale(1.0), reset_ball(false),
  points(), dialogue(), ball_trail() {}
