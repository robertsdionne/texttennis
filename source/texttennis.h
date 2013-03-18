#ifndef TEXTTENNIS_H_
#define TEXTTENNIS_H_

#include <Box2D/Box2D.h>
#include <list>
#include <map>

#include "console.h"
#include "constants.h"
#include "controller.h"
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

private:
  /**
   * Private method declarations.
   */
  void CreateBall(ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f(),
                  float angle = kDefaultAngle, float angular_velocity = kDefaultAngularVelocity);
  
  void CreateBorder();
  
  void CreateCourt();
  
  void CreateNet();
  
  void DestroyBall(b2Body *ball);
  
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
  Controller controller;
  
  
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

#endif  // TEXTTENNIS_H_
