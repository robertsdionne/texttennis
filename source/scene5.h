#ifndef TEXTTENNIS_SCENE5_H_
#define TEXTTENNIS_SCENE5_H_

#include "ofMain.h"
#include "scene5controller.h"
#include "scene5model.h"
#include "scene.h"
#include "scene5view.h"

class TextTennis;

class Scene5 : public Scene {
public:
  Scene5(TextTennis &scene_manager);

  virtual ~Scene5();

  static Scene *Create(TextTennis &scene_manager, ofPoint player_position);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

  virtual ofPoint GetPlayerPosition() {
    return racket1_start_position.GetValue();
  }

private:
  Scene5Model model;
  Scene5View view;
  Scene5Controller controller;
};

#endif  // TEXTTENNIS_SCENE5_H_
