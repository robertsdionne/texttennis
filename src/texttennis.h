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
  static constexpr float kCourtLength = 23.78;
  static constexpr float kDamping = 0.9;
  static constexpr float kGravity = 9.81;
  static constexpr float kTennisBallMass = 0.056;
  static constexpr float kTennisBallRadius = 2.0 * 0.03429;
  
  void Accelerate(float dt);
  void BorderCollide();
  void BorderCollidePreserveImpulse();
  void Damping();
  void Gravity();
  void Inertia();
  void SetViewTransform();
  ofVec2f TransformPosition(ofVec2f position);
  float TransformSize(float size);
  
  GameObject ball;
  std::map<int, bool> previous_keys;
  std::map<int, bool> keys;
};
