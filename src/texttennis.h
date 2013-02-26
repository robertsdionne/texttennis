#pragma once

#include <list>
#include <map>

#include "console.h"
#include "gameobject.h"
#include "gamestate.h"
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
  
  static constexpr const char *kMessageBounce = "Bounce";
  static constexpr const char *kMessageNet = "Net";
  static constexpr const char *kMessageOut = "Out";
  static constexpr const char *kMessageStrongVolley = "Strong Volley";
  static constexpr const char *kMessageVolley = "Volley";
  static constexpr const char *kMessageWeakVolley = "Weak Volley";
  
private:
  static constexpr float kBallMass = 0.056;
  static constexpr float kBallRadius = 2.0 * 0.03429;
  static constexpr float kCourtLength = 23.78;
  static constexpr float kCourtThickness = 0.5;
  static constexpr float kDamping = 0.6;
  static constexpr float kDrag = 0.1;
  static constexpr float kGravity = 9.81 / 2.0;
  static constexpr float kHitMean = 0.7;
  static constexpr float kHitVariance = 0.2;
  static constexpr float kNetHeight = 0.914;
  static constexpr float kNetThickness = kBallRadius;
  static constexpr float kRacketRadius = 2.0 * 0.1155;
  static constexpr float kRacketSpeed = 0.2;
  static constexpr int kTrailSize = 700;
  
  void Accelerate(float dt);
  void BorderCollide();
  void BorderCollidePreserveImpulse();
  void Collide(bool preserve_impulse);
  void Collide(bool preserve_impulse, GameObject &ball0, GameObject &ball1);
  void Damping();
  void DrawTrail(const std::list<GameState::Trail> &trail);
  void Gravity();
  void Inertia();
  void NetCollide();
  void NetCollidePreserveImpulse();
  void RacketCollide();
  void RacketCollidePreserveImpulse();
  void SetViewTransform();
  ofVec2f TransformPosition(ofVec2f position);
  float TransformSize(float size);
  void UpdateRackets();
  
  Console console;
  bool show_console;
  bool show_text;
  bool use_ai;
  std::list<GameState> states;
  std::map<int, bool> previous_keys;
  std::map<int, bool> keys;
};
