#ifndef TEXTTENNIS_FLIPSCENEMODEL_H_
#define TEXTTENNIS_FLIPSCENEMODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "model.h"
#include "ofMain.h"

class FlipSceneModel : public Model {
public:
  FlipSceneModel();
  
  virtual ~FlipSceneModel() {}
  
public:
  float angle;
  int score;
};

#endif  // TEXTTENNIS_FLIPSCENEMODEL_H_
