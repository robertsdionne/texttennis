//
//  man.h
//  texttennis
//
//  Created by Robert Dionne on 3/2/13.
//
//

#ifndef __texttennis__man__
#define __texttennis__man__

#include "ofMain.h"

class Man {
public:
  Man();
  
  Man(ofImage &image_man_left_0, ofImage &image_man_left_1, ofImage &image_man_left_2,
      ofImage &image_man_right_0, ofImage &image_man_right_1, ofImage &image_man_right_2, ofVec2f position);
  
  virtual ~Man() {}
  
  void Draw() const;
  
  void Stop();
  
  void Walk(ofVec2f distance);
  
private:
  static constexpr long kWalkRate = 10;
  
  long index;
  bool walking_right;
  ofVec2f position;
  std::vector<ofImage *> left;
  std::vector<ofImage *> right;
};

#endif /* defined(__texttennis__man__) */
