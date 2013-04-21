#ifndef TEXTTENNIS_SCENE5CONTROLLER_H_
#define TEXTTENNIS_SCENE5CONTROLLER_H_

#include <map>

#include "constants.h"
#include "controller.h"
#include "ofMain.h"

class Model;
class Scene5Model;
class TextTennis;

class Scene5Controller : public Controller {
public:
  Scene5Controller(TextTennis &scene_manager, Scene5Model &model);

  virtual ~Scene5Controller() {}

  virtual void Setup();

  virtual void Update();

  virtual Model &model();

private:
  Scene5Model &model_;
};

#endif  // TEXTTENNIS_SCENE5CONTROLLER_H_
