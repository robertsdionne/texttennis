#ifndef TEXTTENNIS_SCENE2_H_
#define TEXTTENNIS_SCENE2_H_

#include "controller.h"
#include "model.h"
#include "scene.h"
#include "view.h"

class TextTennis;

class Scene2 : public Scene {
public:
  Scene2(TextTennis &scene_manager);

  virtual ~Scene2();

  static Scene *Create(TextTennis &scene_manager);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

private:
  Model model;
  View view;
  Controller controller;
};

#endif  // TEXTTENNIS_SCENE2_H_
