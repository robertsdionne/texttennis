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
  static constexpr int kHalfWindowWidth = 720;
  
  static constexpr int kWindowWidth = 2 * kHalfWindowWidth;
  
  static constexpr int kWindowHeight = 900;
  
private:
  /**
   * Private constant declarations.
   */
  static constexpr float kAngularDamping = 0.1;
  
  static constexpr float kAngularVelocity = 100.0;
  
  static constexpr float kBallCartoonFactor = 1.0;
  
  static const ofVec2f kBallInitialPosition;
  
  static constexpr float kBallMass = 0.056;
  
  static constexpr float kBallRadius = kBallCartoonFactor * 0.03429;
  
  static constexpr int kBox2dVelocityIterations = 8;
  
  static constexpr int kBox2dPositionIterations = 3;
  
  static constexpr float kCeilingHeight = 100.0;
  
  static constexpr float kCourtLength = 23.78;
  
  static constexpr float kCourtThickness = 0.5;
  
  static constexpr float kDefaultAngle = 0.0;
  
  static constexpr float kDefaultAngularVelocity = 0.0;
  
  static constexpr float kDeltaTime = 1.0 / 60.0;
  
  static constexpr float kDensity = kBallMass / M_PI / kBallRadius / kBallRadius;
  
  static constexpr float kFrameRate = 1.0 / kDeltaTime;
  
  static constexpr float kFriction = 0.3;
  
  static constexpr float kGravity = 9.81;
  
  static const b2Vec2 kGravityVector;
  
  static constexpr float kHalfCourtLength = kCourtLength / 2.0;
  
  static constexpr float kHalfCourtThickness = kCourtThickness / 2.0;
  
  static constexpr float kHalfNetThickness = kBallRadius / 2.0;
  
  static constexpr float kHighHitMean = 10.0;
  
  static constexpr float kHitVariance = 0.05;
  
  static constexpr float kLinearDamping = 0.1;
  
  static constexpr float kLowHitMean = 13.0;
  
  static constexpr long kMaxBalls = 500;
  
  static constexpr float kNetHeight = 0.914;
  
  static constexpr float kNetThickness = kBallRadius;
  
  static const ofVec2f kRacket1HighHitDirection;
  
  static const ofVec2f kRacket1LowHitDirection;
  
  static const ofVec2f kRacket1StartPosition;
  
  static const ofVec2f kRacket2HighHitDirection;
  
  static const ofVec2f kRacket2LowHitDirection;
  
  static const ofVec2f kRacket2StartPosition;
  
  static constexpr float kRacketRadius = kBallCartoonFactor * 0.1155;
  
  static constexpr float kRacketSpeed = 0.15;
  
  static constexpr float kRestitution = 0.728;
  
  static constexpr int kSaveEveryNFrames = 2;
  
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
  
  void DrawFrameRate();
  
  void DrawNet();
  
  void DrawRacket(ofVec2f position);
  
  void RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
                     float hit_mean, int key_left, int key_right);
  
  void UpdateRackets();
  
private:
  /**
   * Private member variables.
   */
  Console console;
  
  
  b2World world;
  
  
  std::list<b2Body *> ball_body;
  
  b2Body *court_body, *border_body, *net_body;
  
  b2CircleShape ball_shape;
  
  b2PolygonShape court_shape;
  
  b2EdgeShape net_shape;
  
  b2ChainShape border_shape;
  
  b2Fixture *ball_fixture, *court_fixture, *net_fixture, *border_fixture;
  
  
  ofVec2f racket1, racket2, mouse_position;
  
  std::list<GameState> states;
  
  std::map<int, bool> keys, previous_keys;
};
