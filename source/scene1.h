#ifndef TEXTTENNIS_SCENE1_H_
#define TEXTTENNIS_SCENE1_H_

#include "scene2controller.h"
#include "scene2model.h"
#include "scene.h"
#include "scene2view.h"

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
  Scene2Model model;
  Scene2View view;
  Scene2Controller controller;
};

#endif  // TEXTTENNIS_SCENE1_H_
