#ifndef TEXTTENNIS_SCENE_H_
#define TEXTTENNIS_SCENE_H_

#include "ofMain.h"

class Scene {
public:
  virtual ~Scene() {}

  virtual void Draw() = 0;

  virtual void Setup() = 0;

  virtual void Update() = 0;

  virtual ofPoint GetPlayerPosition() = 0;

protected:
  Scene() {}
};

#endif  // TEXTTENNIS_SCENE_H_
