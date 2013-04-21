#ifndef TEXTTENNIS_INTRODUCTION_H_
#define TEXTTENNIS_INTRODUCTION_H_

#include "constants.h"
#include "introductioncontroller.h"
#include "introductionmodel.h"
#include "introductionview.h"
#include "ofMain.h"
#include "scene.h"

class TextTennis;

class Introduction : public Scene {
public:
  Introduction(TextTennis &scene_manager);

  virtual ~Introduction();

  static Scene *Create(TextTennis &scene_manager, ofPoint player_position);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

  virtual ofPoint GetPlayerPosition() {
    return racket1_start_position.GetValue();
  }

private:
  IntroductionModel model;
  IntroductionView view;
  IntroductionController controller;
};

#endif  // TEXTTENNIS_INTRODUCTION_H_
