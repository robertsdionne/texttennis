#ifndef WITCHBALL_UTILITIES_H_
#define WITCHBALL_UTILITIES_H_

#include <Box2D/Box2D.h>

#include "ofMain.h"

/**
 * Gets the int value of a C++11 enum class.
 */
template <typename T>
int EnumValue(T enum_value) {
  return static_cast<int>(enum_value);
}

/**
 * Creates a b2Vec2 from an ofVec2f.
 */
b2Vec2 Box2dVector(ofVec2f openframeworks_vector);

/**
 * Linearly interpolates a b2Vec2 "from" to a b2Vec2 "to" by the amount "t".
 */
b2Vec2 Lerp(b2Vec2 from, b2Vec2 to, float t);

/**
 * Linearly interpolates an ofVec2f "from" to an ofVec2f "to" by the amount "t".
 */
ofVec2f Lerp(ofVec2f from, ofVec2f to, float t);

/**
 * Creates an ofVec2f from a b2Vec2.
 */
ofVec2f OpenFrameworksVector(b2Vec2 box2d_vector);

#endif  // WITCHBALL_UTILITIES_H_
