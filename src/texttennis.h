#pragma once

#include <Box2D/Box2D.h>
#include <list>
#include <map>

#include "console.h"
#include "gameobject.h"
#include "gamestate.h"
#include "ofMain.h"

class TextTennis : public ofBaseApp {
public:
  TextTennis();
  
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
  
  static constexpr int kWindowWidth = 1024;
  static constexpr int kWindowHeight = 768;
  
private:
  static constexpr float kFrameRate = 60.0;
  static constexpr float kDeltaTime = 1.0 / kFrameRate;
  
  static constexpr float kAngularDamping = 0.1;
  static constexpr int kBox2dVelocityIterations = 8;
  static constexpr int kBox2dPositionIterations = 3;
  static constexpr float kBallMass = 0.056;
  static constexpr float kBallRadius = 2.0 * 0.03429;
  static constexpr float kCourtLength = 23.78;
  static constexpr float kCourtThickness = 0.5;
  static constexpr float kDrag = 0.1 * kBallMass;
  static const b2Vec2 kGravityVector;
  static constexpr float kGravity = 9.81;
  static constexpr float kHitMean = 0.20;
  static constexpr float kHitVariance = 0.08;
  static constexpr float kLinearDamping = 0.1;
  static constexpr long kMaxBalls = 500;
  static constexpr float kNetHeight = 0.914;
  static constexpr float kNetThickness = kBallRadius;
  static constexpr float kRacketRadius = 2.0 * 0.1155;
  static constexpr float kRacketSpeed = 0.1;
  static constexpr int kTrailSize = 700;
  static const ofMatrix4x4 kViewMatrix;
  static const ofMatrix4x4 kViewMatrixInverse;
  
  void CreateBall(ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f(),
                  float angle = 0.0, float angular_velocity = 0.0);
  void CreateBorder();
  void CreateCourt();
  void CreateNet();
  void RacketCollide();
  void UpdateRackets();
  
  Console console;
  
  b2World world;
  
  std::list<b2Body *> ball_body;
  b2CircleShape ball_shape;
  b2Fixture *ball_fixture;
  
  b2Body *court_body;
  b2PolygonShape court_shape;
  b2Fixture *court_fixture;
  
  b2Body *net_body;
  b2EdgeShape net_shape;
  b2Fixture *net_fixture;
  
  b2Body *border_body;
  b2ChainShape border_shape;
  b2Fixture *border_fixture;
  
  bool show_console;
  bool show_text;
  bool use_ai;
  ofVec2f racket1;
  ofVec2f mouse_position;
  std::list<GameState> states;
  std::map<int, bool> previous_keys;
  std::map<int, bool> keys;
};
