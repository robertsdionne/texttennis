#include "constants.h"
#include "model.h"

Model::Model()
: world(kGravityVector), ball_body(), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(kRacket1StartPosition), racket2(kRacket2StartPosition),
  mouse_position(), states(), rewinding(false) {}
