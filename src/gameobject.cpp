//
//  gameobject.cpp
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#include "gameobject.h"

GameObject::GameObject(float radius, float mass, ofVec2f position, ofVec2f velocity)
: radius(radius), mass(mass), position(position), previous_position(position - velocity / ofGetFrameRate()) {}

GameObject::~GameObject() {}

void GameObject::Accelerate(float dt) {
  position += force / mass * dt * dt;
  force = ofVec2f();
}

void GameObject::Inertia() {
  ofVec2f new_position = 2.0 * position - previous_position;
  previous_position = position;
  position = new_position;
}
