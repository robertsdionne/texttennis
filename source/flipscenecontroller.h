#ifndef TEXTTENNIS_FLIPSCENECONTROLLER_H_
#define TEXTTENNIS_FLIPSCENECONTROLLER_H_

#include <map>

#include "constants.h"
#include "controller.h"
#include "ofMain.h"

class b2Body;
class Model;
class FlipSceneModel;
class TextTennis;

class FlipSceneController : public Controller {
public:
  FlipSceneController(TextTennis &scene_manager, FlipSceneModel &model);
  
  virtual ~FlipSceneController();

  virtual void Setup();

  virtual void Update();

  virtual Model &model();

private:
  FlipSceneModel &model_;
};

#endif  // TEXTTENNIS_FLIPSCENECONTROLLER_H_
