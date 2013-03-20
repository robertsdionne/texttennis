#include "constants.h"
#include "model.h"

Model::Model()
: world(param_gravity_vector), ball_body(), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(param_racket1_start_position), racket2(param_racket2_start_position),
  mouse_position(), states(), rewinding(false) {}
