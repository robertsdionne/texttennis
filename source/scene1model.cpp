#include "constants.h"
#include "scene1model.h"

Scene1Model::Scene1Model()
: world(gravity_vector), ball_body(), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(racket1_start_position), racket2(racket2_start_position),
  states(), rewinding(false) {}
