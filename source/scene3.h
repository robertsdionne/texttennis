#ifndef TEXTTENNIS_SCENE3_H_
#define TEXTTENNIS_SCENE3_H_

#include "scene2controller.h"
#include "scene2model.h"
#include "scene.h"
#include "scene2view.h"

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
  Scene2Model model;
  Scene2View view;
  Scene2Controller controller;
};

#endif  // TEXTTENNIS_SCENE3_H_
