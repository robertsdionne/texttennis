#include "constants.h"
#include "scene4model.h"

Scene4Model::Scene4Model()
: world(gravity_vector), ball_body(), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(racket1_start_position), opponent(racket2_start_position),
  score(), bounces(0) {}
