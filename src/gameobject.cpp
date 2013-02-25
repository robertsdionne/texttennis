//
//  gameobject.cpp
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#include "gameobject.h"

constexpr float GameObject::kDeltaTime;
constexpr float GameObject::kFrameRate;

GameObject::GameObject(float radius, float mass, ofVec2f position, ofVec2f velocity)
: radius(radius), mass(mass), position(position), previous_position(position - velocity / kFrameRate) {}

GameObject::~GameObject() {}

ofVec2f GameObject::velocity() const {
  return (position - previous_position) * kFrameRate;
}

void GameObject::Accelerate(float dt) {
  position += force / mass * dt * dt;
  force = ofVec2f();
}

void GameObject::Inertia() {
  ofVec2f new_position = position * 2.0 - previous_position;
  previous_position = position;
  position = new_position;
}
