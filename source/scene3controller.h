#ifndef TEXTTENNIS_SCENE3CONTROLLER_H_
#define TEXTTENNIS_SCENE3CONTROLLER_H_

#include <map>

#include "constants.h"
#include "controller.h"
#include "ofMain.h"

class b2Body;
class Model;
class Scene3Model;
class TextTennis;

class Scene3Controller : public Controller {
public:
  Scene3Controller(TextTennis &scene_manager, Scene3Model &model);

  virtual ~Scene3Controller() {}

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
  Scene3Model &model_;
};

#endif  // TEXTTENNIS_SCENE3CONTROLLER_H_
