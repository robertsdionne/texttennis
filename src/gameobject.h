//
//  gameobject.h
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#ifndef __texttennis__gameobject__
#define __texttennis__gameobject__

#include <iostream>
#include "ofMain.h"

class GameObject {
public:
  GameObject(float radius = 1.0, float mass = 1.0, ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f());
  
  virtual ~GameObject();
  
  void Accelerate(float dt);
  void Inertia();
  
  float radius;
  float mass;
  ofVec2f position;
  ofVec2f previous_position;
  ofVec2f force;
};

#endif /* defined(__texttennis__gameobject__) */
