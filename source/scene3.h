#ifndef TEXTTENNIS_SCENE3_H_
#define TEXTTENNIS_SCENE3_H_

#include "ofMain.h"
#include "scene3controller.h"
#include "scene3model.h"
#include "scene.h"
#include "scene3view.h"

class TextTennis;

class Scene3 : public Scene {
public:
  Scene3(TextTennis &scene_manager, ofPoint player_position);

  virtual ~Scene3();

  static Scene *Create(TextTennis &scene_manager, ofPoint player_position);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

  virtual ofPoint GetPlayerPosition() {
    return model.racket1;
  }

private:
  Scene3Model model;
  Scene3View view;
  Scene3Controller controller;
};

#endif  // TEXTTENNIS_SCENE3_H_
