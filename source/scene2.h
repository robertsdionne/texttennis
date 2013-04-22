#ifndef TEXTTENNIS_SCENE2_H_
#define TEXTTENNIS_SCENE2_H_

#include "ofMain.h"
#include "scene2controller.h"
#include "scene2model.h"
#include "scene.h"
#include "scene2view.h"

class TextTennis;

class Scene2 : public Scene {
public:
  Scene2(TextTennis &scene_manager, ofPoint player_position);

  virtual ~Scene2();

  static Scene *Create(TextTennis &scene_manager, ofPoint player_position);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

  virtual ofPoint GetPlayerPosition() {
    return model.racket1;
  }

private:
  Scene2Model model;
  Scene2View view;
  Scene2Controller controller;
};

#endif  // TEXTTENNIS_SCENE2_H_
