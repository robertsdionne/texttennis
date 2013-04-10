#ifndef TEXTTENNIS_FLIPSCENE_H_
#define TEXTTENNIS_FLIPSCENE_H_

#include "flipscenecontroller.h"
#include "flipscenemodel.h"
#include "scene.h"
#include "flipsceneview.h"

class TextTennis;

class FlipScene : public Scene {
public:
  FlipScene(TextTennis &scene_manager);

  virtual ~FlipScene();

  static Scene *Create(TextTennis &scene_manager);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

private:
  FlipSceneModel model;
  FlipSceneView view;
  FlipSceneController controller;
};

#endif  // TEXTTENNIS_FLIPSCENE_H_
