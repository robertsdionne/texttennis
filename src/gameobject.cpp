//
//  gameobject.cpp
//  texttennis
//
//  Created by Robert Dionne on 2/24/13.
//
//

#include "gameobject.h"

GameObject::GameObject(ofVec2f position, ofVec2f velocity, float angle, float angular_velocity)
: position(position), velocity(velocity), angle(angle), angular_velocity(angular_velocity) {}

GameObject::~GameObject() {}
