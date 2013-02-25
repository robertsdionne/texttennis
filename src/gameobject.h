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
  
  ofVec2f velocity() const;
  
  void Accelerate(float dt);
  
  void Inertia();
  
  static constexpr float kFrameRate = 60.0;
  static constexpr float kDeltaTime = 1.0 / kFrameRate;
  
  float radius;
  float mass;
  ofVec2f position;
  ofVec2f previous_position;
  ofVec2f force;
};

#endif /* defined(__texttennis__gameobject__) */
