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
  
  static constexpr const char *kMessageBounce = "Bounce";
  static constexpr const char *kMessageNet = "Net";
  static constexpr const char *kMessageOut = "Out";
  static constexpr const char *kMessageStrongVolley = "Strong Volley";
  static constexpr const char *kMessageVolley = "Volley";
  static constexpr const char *kMessageWeakVolley = "Weak Volley";
  
private:
  static const b2Vec2 kGravityVector;
  static constexpr int kBox2dVelocityIterations = 8;
  static constexpr int kBox2dPositionIterations = 3;
  static constexpr float kBallMass = 0.056;
  static constexpr float kBallRadius = 2.0 * 0.03429;
  static constexpr float kCourtLength = 23.78;
  static constexpr float kCourtThickness = 0.5;
  static constexpr float kDamping = 0.6;
  static constexpr float kDrag = 0.1 * kBallMass;
  static constexpr float kGravity = 9.81;
  static constexpr float kHitMean = 0.16;
  static constexpr float kHitVariance = 0.08;
  static constexpr long kMaxBalls = 500;
  static constexpr float kNetHeight = 0.914;
  static constexpr float kNetThickness = kBallRadius;
  static constexpr float kRacketRadius = 2.0 * 0.1155;
  static constexpr float kRacketSpeed = 0.1;
  static constexpr int kTrailSize = 700;
  
  void RacketCollide();
  void SetViewTransform();
  ofVec2f TransformPosition(ofVec2f position);
  ofVec2f TransformPositionInverse(ofVec2f position);
  float TransformSize(float size);
  void UpdateRackets();
  
  Console console;
  
  b2World world;
  b2BodyDef ball_body_definition;
  std::list<b2Body *> ball_body;
  b2CircleShape ball_shape;
  b2FixtureDef ball_fixture_definition;
  b2Fixture *ball_fixture;
  
  b2BodyDef court_body_definition;
  b2Body *court_body;
  b2PolygonShape court_shape;
  b2FixtureDef court_fixture_definition;
  b2Fixture *court_fixture;
  
  b2BodyDef net_body_definition;
  b2Body *net_body;
  b2EdgeShape net_shape;
  b2FixtureDef net_fixture_definition;
  b2Fixture *net_fixture;
  
  b2BodyDef border_body_definition;
  b2Body *border_body;
  b2ChainShape border_shape;
  b2FixtureDef border_fixture_definition;
  b2Fixture *border_fixture;
  
  bool show_console;
  bool show_text;
  bool use_ai;
  ofVec2f racket1;
  ofVec2f mouse_position;
  std::map<int, bool> previous_keys;
  std::map<int, bool> keys;
};
