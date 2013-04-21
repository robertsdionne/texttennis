#ifndef TEXTTENNIS_TRANSITION_H_
#define TEXTTENNIS_TRANSITION_H_

#include "ofMain.h"

class Transition {
public:
  Transition(ofImage &from, ofImage &to);

  virtual ~Transition() {}

  void Draw();
  
  bool IsDone();

  void Setup();

  void Update();

private:
  float HalfLambert(ofVec3f light, ofVec3f normal);

  ofImage from_top, from_bottom, to_top, to_bottom;
  float angle;
};

#endif  // TEXTTENNIS_TRANSITION_H_
