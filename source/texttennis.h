#ifndef TEXTTENNIS_H_
#define TEXTTENNIS_H_

#include <Box2D/Box2D.h>
#include <list>
#include <map>

#include "constants.h"
#include "controller.h"
#include "gameobject.h"
#include "gamestate.h"
#include "model.h"
#include "ofMain.h"
#include "view.h"

class TextTennis : public ofBaseApp {
public:
  /**
   * Public method declarations.
   */
  TextTennis();
  
  void setup();
  
  void update();
  
  void draw();
  
  void keyPressed(int key);
  
  void keyReleased(int key);
  
  void mouseMoved(int x, int y);
  
  void mouseDragged(int x, int y, int button) {}
  
  void mousePressed(int x, int y, int button) {}
  
  void mouseReleased(int x, int y, int button) {}
  
  void windowResized(int w, int h) {}
  
  void dragEvent(ofDragInfo dragInfo) {}
  
  void gotMessage(ofMessage msg) {}

private:
  /**
   * Private method declarations.
   */
  void CreateBall(ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f(),
                  float angle = kDefaultAngle, float angular_velocity = kDefaultAngularVelocity);
  
  void DestroyBall(b2Body *ball);
  
  void RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
                     float hit_mean, int key_left, int key_right);
  
  void UpdateRackets();
  
private:
  /**
   * Private member variables.
   */
  Model model;
  View view;
  Controller controller;
  
  std::map<int, bool> keys, previous_keys;
};

#endif  // TEXTTENNIS_H_
