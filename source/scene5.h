#ifndef TEXTTENNIS_SCENE5_H_
#define TEXTTENNIS_SCENE5_H_

#include "controller.h"
#include "model.h"
#include "scene.h"
#include "view.h"

class TextTennis;

class Scene5 : public Scene {
public:
  Scene5(TextTennis &scene_manager);

  virtual ~Scene5();

  static Scene *Create(TextTennis &scene_manager);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

private:
  Model model;
  View view;
  Controller controller;
};

#endif  // TEXTTENNIS_SCENE5_H_
