#ifndef TEXTTENNIS_MODEL_H_
#define TEXTTENNIS_MODEL_H_

#include "ofMain.h"

class Model {
public:
  virtual ~Model() {}

  ofVec2f mouse_position;

protected:
  Model() : mouse_position() {}
};

#endif  // TEXTTENNIS_MODEL_H_
