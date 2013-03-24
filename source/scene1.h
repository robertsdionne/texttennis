#ifndef TEXTTENNIS_SCENE1_H_
#define TEXTTENNIS_SCENE1_H_

#include "scene1controller.h"
#include "scene1model.h"
#include "scene.h"
#include "scene1view.h"

class TextTennis;

class Scene1 : public Scene {
public:
  Scene1(TextTennis &scene_manager);

  virtual ~Scene1();

  static Scene *Create(TextTennis &scene_manager);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

private:
  Scene1Model model;
  Scene1View view;
  Scene1Controller controller;
};

#endif  // TEXTTENNIS_SCENE1_H_
