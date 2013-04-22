#include "constants.h"
#include "scene1model.h"

Scene1Model::Scene1Model()
: world(b2Vec2(0, 0)), ball_body(nullptr), court_body(nullptr), net_body(nullptr),
  border_body(nullptr), racket1(racket1_start_position), racket2(racket2_start_position),
  racket1_target(racket1_start_position), racket2_target(racket2_start_position), dialogue(),
  title(0.0), frozen(true), fallen(false), flipped(false), player_released(false),
  title_started(false), rotating(false), platform(0.0), platform_appearing(false) {}
