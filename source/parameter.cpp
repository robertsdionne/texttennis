#include <Box2D/Box2D.h>
#include <vector>

#include "ofMain.h"
#include "parameter.h"

template<>
std::vector<Parameter<b2Vec2> *> Parameter<b2Vec2>::parameters;

template <>
std::vector<Parameter<float> *> Parameter<float>::parameters;

template <>
std::vector<Parameter<int> *> Parameter<int>::parameters;

template<>
std::vector<Parameter<ofVec2f> *> Parameter<ofVec2f>::parameters;
