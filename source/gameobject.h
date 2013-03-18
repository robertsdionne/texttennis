#ifndef TEXTTENNIS_GAMEOBJECT_H_
#define TEXTTENNIS_GAMEOBJECT_H_

#include "ofMain.h"

class GameObject {
public:
  GameObject(ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f(), float angle = 0.0, float angular_velocity = 0.0);
  
  virtual ~GameObject() {}
  
  ofVec2f position;
  ofVec2f velocity;
  float angle;
  float angular_velocity;
};

#endif  // TEXTTENNIS_GAMEOBJECT_H_
