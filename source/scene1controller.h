#ifndef TEXTTENNIS_SCENE1CONTROLLER_H_
#define TEXTTENNIS_SCENE1CONTROLLER_H_

#include <map>

#include "constants.h"
#include "controller.h"
#include "ofMain.h"

class b2Body;
class Model;
class Scene1Model;
class TextTennis;

class Scene1Controller : public Controller {
public:
  Scene1Controller(TextTennis &scene_manager, Scene1Model &model);
  
  virtual ~Scene1Controller() {}

  virtual void Setup();

  virtual void Update();

  virtual Model &model();
  
private:
  void CreateBall(ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f(),
                  float angle = default_angle, float angular_velocity = default_angular_velocity);

  void CreateBorder();
  
  void CreateCourt();
  
  void CreateNet();
  
  void DestroyBall(b2Body *ball);
  
  bool MouseButtonIsPressed(int button);
  
  void RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
                     float hit_mean, int key_left, int key_right);
  
  void UpdateRackets();

private:
  Scene1Model &model_;
};

#endif  // TEXTTENNIS_SCENE1CONTROLLER_H_
