#include <Box2D/Box2D.h>

#include "introductionmodel.h"
#include "parameter.h"

DEFINE_PARAMETER_RANGE(float, IntroductionModel::create_delay, 0.1, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, IntroductionModel::gravity, 9.81, -10.0, 10.0);
DEFINE_PARAMETER(b2Vec2, IntroductionModel::gravity_vector, b2Vec2(0, -IntroductionModel::gravity));

IntroductionModel::IntroductionModel()
: Model(), world(gravity_vector), boxes(), last_create_time() {}
