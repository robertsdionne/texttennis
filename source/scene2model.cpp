#include "constants.h"
#include "scene2model.h"

Scene2Model::Scene2Model()
: world(gravity_vector), ball_body(), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(racket1_start_position) {}
