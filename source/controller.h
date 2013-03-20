#ifndef TEXTTENNIS_CONTROLLER_H_
#define TEXTTENNIS_CONTROLLER_H_

#include <map>

#include "constants.h"
#include "ofMain.h"

class b2Body;
class Model;

class Controller {
public:
  Controller(Model &model);
  
  virtual ~Controller() {}

  void Setup();

  void Update();
  
  void keyPressed(ofKeyEventArgs &event);
  
  void keyReleased(ofKeyEventArgs &event);
  
  void mouseDragged(ofMouseEventArgs &event);
  
  void mouseMoved(ofMouseEventArgs &event);
  
  void mousePressed(ofMouseEventArgs &event);
  
  void mouseReleased(ofMouseEventArgs &event);
  
private:
  void CreateBall(ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f(),
                  float angle = param_default_angle, float angular_velocity = param_default_angular_velocity);

  void CreateBorder();
  
  void CreateCourt();
  
  void CreateNet();
  
  void DestroyBall(b2Body *ball);
  
  bool MouseButtonIsPressed(int button);
  
  void RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
                     float hit_mean, int key_left, int key_right);
  
  void UpdateRackets();
  
private:
  Model &model;
  std::map<int, bool> buttons, keys, previous_buttons, previous_keys;
};

#endif  // TEXTTENNIS_CONTROLLER_H_