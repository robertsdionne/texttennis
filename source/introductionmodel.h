#ifndef TEXTTENNIS_INTRODUCTIONMODEL_H_
#define TEXTTENNIS_INTRODUCTIONMODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "dialogue.h"
#include "model.h"
#include "parameter.h"

class IntroductionModel : public Model {
public:
  IntroductionModel();

  virtual ~IntroductionModel() {};

public:
  b2World world;

  std::list<b2Body *> boxes;

  float last_create_time;

  Dialogue dialogue;

public:
  static Parameter<float> create_delay;
  static Parameter<float> gravity;
  static Parameter<b2Vec2> gravity_vector;
};

#endif  // TEXTTENNIS_INTRODUCTIONMODEL_H_
