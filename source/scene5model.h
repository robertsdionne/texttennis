#ifndef TEXTTENNIS_SCENE5MODEL_H_
#define TEXTTENNIS_SCENE5MODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "dialogue.h"
#include "model.h"
#include "ofMain.h"

class Scene5Model : public Model {
public:
  Scene5Model();
  
  virtual ~Scene5Model() {}

  Dialogue dialogue;
};

#endif  // TEXTTENNIS_SCENE5MODEL_H_
