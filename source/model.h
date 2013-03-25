#ifndef TEXTTENNIS_MODEL_H_
#define TEXTTENNIS_MODEL_H_

#include "constants.h"
#include "ofMain.h"

class Model {
public:
  virtual ~Model() {}

  ofVec2f mouse_position;

protected:
  Model() : mouse_position(0.0, court_height) {}
};

#endif  // TEXTTENNIS_MODEL_H_
