#ifndef __texttennis__introduction__
#define __texttennis__introduction__

#include "scene2controller.h"
#include "scene2model.h"
#include "scene.h"
#include "scene2view.h"

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
  Scene2Model model;
  Scene2View view;
  Scene2Controller controller;
};

#endif /* defined(__texttennis__introduction__) */
