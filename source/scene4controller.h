#ifndef TEXTTENNIS_SCENE4CONTROLLER_H_
#define TEXTTENNIS_SCENE4CONTROLLER_H_

#include <map>

#include "constants.h"
#include "controller.h"
#include "ofMain.h"

class b2Body;
class Model;
class Scene4Model;
class TextTennis;

class Scene4Controller : public Controller, b2ContactListener {
public:
  Scene4Controller(TextTennis &scene_manager, Scene4Model &model);

  virtual ~Scene4Controller();

  virtual void BeginContact(b2Contact* contact);

  virtual void Setup();

  virtual void Update();

  virtual Model &model();
  
private:
  void CreateBall(ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f(),
                  float angle = default_angle, float angular_velocity = default_angular_velocity);

  void CreateTreePeople();

  void CreateBorder();
  
  void CreateCourt();
  
  void CreateNet();
  
  void DestroyBall(b2Body *ball);
  
  bool MouseButtonIsPressed(int button);
  
  void RacketCollide(ofVec2f racket_position, ofVec2f hit_direction,
                     float hit_mean, int key_left, int key_right);
  
  void UpdateRackets();

private:
  Scene4Model &model_;
  std::string tree[5];
  ofSoundPlayer hit1, hit2;
  ofSoundPlayer bounce1, bounce2, bounce3, bounce4;
};

#endif  // TEXTTENNIS_SCENE4CONTROLLER_H_
