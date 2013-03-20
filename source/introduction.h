#ifndef __texttennis__introduction__
#define __texttennis__introduction__

#include "controller.h"
#include "model.h"
#include "scene.h"
#include "view.h"

class TextTennis;

class Introduction : public Scene {
public:
  Introduction(TextTennis &scene_manager);

  virtual ~Introduction();

  static Scene *Create(TextTennis &scene_manager);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

private:
  Model model;
  View view;
  Controller controller;
};

#endif /* defined(__texttennis__introduction__) */
