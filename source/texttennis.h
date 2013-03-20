#ifndef TEXTTENNIS_H_
#define TEXTTENNIS_H_

#include <Box2D/Box2D.h>
#include <list>
#include <map>

#include "constants.h"
#include "controller.h"
#include "gameobject.h"
#include "gamestate.h"
#include "model.h"
#include "ofMain.h"
#include "scene1.h"
#include "view.h"

class TextTennis : public ofBaseApp {
public:
  /**
   * Public method declarations.
   */
  TextTennis();
  
  void setup();
  
  void update();
  
  void draw();

private:
  Scene1 scene;
};

#endif  // TEXTTENNIS_H_
