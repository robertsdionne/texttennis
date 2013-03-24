#ifndef __texttennis__introduction__
#define __texttennis__introduction__

#include "introductioncontroller.h"
#include "introductionmodel.h"
#include "scene.h"
#include "introductionview.h"

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
  IntroductionModel model;
  IntroductionView view;
  IntroductionController controller;
};

#endif /* defined(__texttennis__introduction__) */
