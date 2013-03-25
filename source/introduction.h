#ifndef TEXTTENNIS_INTRODUCTION_H_
#define TEXTTENNIS_INTRODUCTION_H_

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

#endif  // TEXTTENNIS_INTRODUCTION_H_
