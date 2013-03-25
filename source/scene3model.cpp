#include "constants.h"
#include "scene3model.h"

Scene3Model::Scene3Model()
: world(gravity_vector), ball_body(), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(racket1_start_position), opponent(racket2_start_position),
  score(), bounces(0) {}
