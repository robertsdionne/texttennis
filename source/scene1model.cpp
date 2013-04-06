#include "constants.h"
#include "scene1model.h"

Scene1Model::Scene1Model()
: world(gravity_vector), ball_body(nullptr), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(racket1_start_position), racket2(racket2_start_position),
  racket1_target(racket1_start_position), racket2_target(racket2_start_position) {}
