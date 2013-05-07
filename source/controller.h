#ifndef TEXTTENNIS_CONTROLLER_H_
#define TEXTTENNIS_CONTROLLER_H_

#include <map>

#include "constants.h"
#include "ofMain.h"

class Model;
class TextTennis;

class Controller {
public:
  virtual ~Controller() {}

  virtual bool AnyButtonPressed();

  virtual bool AnyKeyPressed();

  virtual void Setup() = 0;

  virtual void Update();

  virtual void keyPressed(ofKeyEventArgs &event);

  virtual void keyReleased(ofKeyEventArgs &event);

  virtual void mouseDragged(ofMouseEventArgs &event);

  virtual void mouseMoved(ofMouseEventArgs &event);

  virtual void mousePressed(ofMouseEventArgs &event);

  virtual void mouseReleased(ofMouseEventArgs &event);

  virtual Model &model() = 0;

protected:
  Controller(TextTennis &scene_manager);

  TextTennis &scene_manager;
  std::map<int, bool> buttons, keys, previous_buttons, previous_keys;
};

#endif  // TEXTTENNIS_CONTROLLER_H_
