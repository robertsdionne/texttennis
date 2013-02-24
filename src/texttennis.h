#pragma once

#include <list>
#include <map>

#include "gameobject.h"
#include "ofMain.h"

class TextTennis : public ofBaseApp {
public:
  void setup();
  
  void update();
  
  void draw();
  
  void keyPressed(int key);
  
  void keyReleased(int key);
  
  void mouseMoved(int x, int y);
  
  void mouseDragged(int x, int y, int button);
  
  void mousePressed(int x, int y, int button);
  
  void mouseReleased(int x, int y, int button);
  
  void windowResized(int w, int h);
  
  void dragEvent(ofDragInfo dragInfo);
  
  void gotMessage(ofMessage msg);
  
private:
  void SetViewTransform();
  
  static constexpr float kTennisBallMass = 0.056;
  static constexpr float kTennisBallRadius = 0.03429;
  
  GameObject ball;
  std::map<int, bool> previous_keys;
  std::map<int, bool> keys;
};
