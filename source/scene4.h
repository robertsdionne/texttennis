#ifndef TEXTTENNIS_SCENE4_H_
#define TEXTTENNIS_SCENE4_H_

#include "controller.h"
#include "model.h"
#include "scene.h"
#include "view.h"

class TextTennis;

class Scene4 : public Scene {
public:
  Scene4(TextTennis &scene_manager);

  virtual ~Scene4();

  static Scene *Create(TextTennis &scene_manager);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

private:
  Model model;
  View view;
  Controller controller;
};

#endif  // TEXTTENNIS_SCENE4_H_
