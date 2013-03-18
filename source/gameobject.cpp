#include "gameobject.h"

GameObject::GameObject(ofVec2f position, ofVec2f velocity, float angle, float angular_velocity)
: position(position), velocity(velocity), angle(angle), angular_velocity(angular_velocity) {}
