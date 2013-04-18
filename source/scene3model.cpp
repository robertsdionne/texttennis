#include "constants.h"
#include "scene3model.h"

Scene3Model::Scene3Model()
: world(gravity_vector), ball_body(), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(racket1_start_position), opponent(racket2_start_position),
  racket1_target(racket1_start_position), opponent_target(racket2_start_position),
  score(0), angle(180.0), bounces(0), dialogue() {}
