//
//  gameobject.h
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#ifndef __texttennis__gameobject__
#define __texttennis__gameobject__

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

#endif /* defined(__texttennis__gameobject__) */
