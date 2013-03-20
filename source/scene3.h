#ifndef TEXTTENNIS_SCENE3_H_
#define TEXTTENNIS_SCENE3_H_

#include "controller.h"
#include "model.h"
#include "scene.h"
#include "view.h"

class TextTennis;

class Scene3 : public Scene {
public:
  Scene3(TextTennis &scene_manager);

  virtual ~Scene3();

  static Scene *Create(TextTennis &scene_manager);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

private:
  Model model;
  View view;
  Controller controller;
};

#endif  // TEXTTENNIS_SCENE3_H_
