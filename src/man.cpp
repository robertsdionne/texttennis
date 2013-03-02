//
//  man.cpp
//  texttennis
//
//  Created by Robert Dionne on 3/2/13.
//
//

#include "ofMain.h"
#include "man.h"

Man::Man()
: index(0), walking_right(true), position(), left(), right() {}

Man::Man(ofImage &image_man_left_0, ofImage &image_man_left_1, ofImage &image_man_left_2,
        ofImage &image_man_right_0, ofImage &image_man_right_1, ofImage &image_man_right_2, ofVec2f position)
: index(0), walking_right(true), position(position), left(), right() {
  left.push_back(&image_man_left_0);
  left.push_back(&image_man_left_1);
  left.push_back(&image_man_left_0);
  left.push_back(&image_man_left_2);
  right.push_back(&image_man_right_0);
  right.push_back(&image_man_right_1);
  right.push_back(&image_man_right_0);
  right.push_back(&image_man_right_2);
}

void Man::Draw() const {
  ofSetColor(ofColor::white);
  ofImage *const image = (walking_right ? right : left)[index];
  image->draw(position, 2 * image->getWidth(), 2 * image->getHeight());
}

void Man::Stop() {
  index = 0;
}

void Man::Walk(ofVec2f distance) {
  if (ofGetFrameNum() % kWalkRate == 0) {
    index = (index + 1) % right.size();
  }
  if (distance.x > 0) {
    walking_right = true;
  }
  if (distance.x < 0) {
    walking_right = false;
  }
  position += distance;
}
