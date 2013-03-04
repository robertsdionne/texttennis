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
  
public:
  /**
   * Public constant declarations.
   */
  static constexpr int kHalfWindowWidth = 512;
  
  static constexpr int kWindowWidth = 2 * kHalfWindowWidth;
  
  static constexpr int kWindowHeight = 768;
  
private:
  /**
   * Private constant declarations.
   */
  static constexpr int OF_KEY_TAB = '\t';
  
  static constexpr float kAngularDamping = 0.1;
  
  static constexpr float kBallCartoonFactor = 2.0;
  
  static constexpr float kBallMass = 0.056;
  
  static constexpr float kBallRadius = kBallCartoonFactor * 0.03429;
  
  static constexpr int kBox2dVelocityIterations = 8;
  
  static constexpr int kBox2dPositionIterations = 3;
  
  static constexpr float kCourtLength = 23.78;
  
  static constexpr float kCourtThickness = 0.5;
  
  static constexpr float kDefaultAngle = 0.0;
  
  static constexpr float kDefaultAngularVelocity = 0.0;
  
  static constexpr float kDeltaTime = 1.0 / 60.0;
  
  static constexpr float kDrag = 0.1 * kBallMass;
  
  static constexpr float kFrameRate = 1.0 / kDeltaTime;
  
  static constexpr float kGravity = 9.81;
  
  static const b2Vec2 kGravityVector;
  
  static constexpr float kHalfCourtLength = kCourtLength / 2.0;
  
  static constexpr float kHitMean = 0.20;
  
  static constexpr float kHitVariance = 0.08;
  
  static constexpr float kLinearDamping = 0.1;
  
  static constexpr long kMaxBalls = 500;
  
  static constexpr float kNetHeight = 0.914;
  
  static constexpr float kNetThickness = kBallRadius;
  
  static const ofVec2f kRacket1StartPosition;
  
  static constexpr float kRacketRadius = kBallCartoonFactor * 0.1155;
  
  static constexpr float kRacketSpeed = 0.1;
  
  static constexpr int kTrailSize = 700;
  
  static const ofMatrix4x4 kViewMatrix;
  
  static const ofMatrix4x4 kViewMatrixInverse;
  
private:
  /**
   * Private method declarations.
   */
  void CreateBall(ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f(),
                  float angle = kDefaultAngle, float angular_velocity = kDefaultAngularVelocity);
  
  void CreateBorder();
  
  void CreateCourt();
  
  void CreateNet();
  
  void DrawBall(ofVec2f position, float angle);
  
  void DrawCourt();
  
  void DrawNet();
  
  void DrawRacket(ofVec2f position);
  
  void RacketCollide();
  
  void UpdateRackets();
  
private:
  /**
   * Private member variables.
   */
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
