#ifndef TEXTTENNIS_CONTROLLER_H_
#define TEXTTENNIS_CONTROLLER_H_

#include <map>

#include "constants.h"

class Model;

class Controller {
public:
  Controller(Model &model);
  
  virtual ~Controller() {}
  
  void OnKeyPressed(int key);
  
  void OnKeyReleased(int key);
  
  void OnMouseDragged(int x, int y, int button);
  
  void OnMouseMoved(int x, int y);
  
  void OnMousePressed(int x, int y, int button);
  
  void OnMouseReleased(int x, int y, int button);
  
  void Setup();
  
  void Update();
  
private:
  void CreateBall(ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f(),
                  float angle = kDefaultAngle, float angular_velocity = kDefaultAngularVelocity);

  void CreateBorder();
  
  void CreateCourt();
  
  void CreateNet();
  
  bool MouseButtonIsPressed(int button);
  
private:
  Model &model;
  std::map<int, bool> buttons, keys, previous_buttons, previous_keys;
};

#endif  // TEXTTENNIS_CONTROLLER_H_
