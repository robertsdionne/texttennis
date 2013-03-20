#ifndef TEXTTENNIS_SCENE1_H_
#define TEXTTENNIS_SCENE1_H_

#include "controller.h"
#include "model.h"
#include "scene.h"
#include "view.h"

class Scene1 : public Scene {
public:
  Scene1();

  virtual ~Scene1();

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

private:
  Model model;
  View view;
  Controller controller;
};

#endif  // TEXTTENNIS_SCENE1_H_
