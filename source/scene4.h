#ifndef TEXTTENNIS_SCENE4_H_
#define TEXTTENNIS_SCENE4_H_

#include "scene4controller.h"
#include "scene4model.h"
#include "scene.h"
#include "scene4view.h"

class TextTennis;

class Scene4 : public Scene {
public:
  Scene4(TextTennis &scene_manager, ofPoint player_position);

  virtual ~Scene4();

  static Scene *Create(TextTennis &scene_manager, ofPoint player_position);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

  virtual ofPoint GetPlayerPosition() {
    return model.racket1;
  }

private:
  Scene4Model model;
  Scene4View view;
  Scene4Controller controller;
};

#endif  // TEXTTENNIS_SCENE4_H_
