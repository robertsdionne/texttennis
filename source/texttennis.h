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
  
  void keyPressed(int key);
  
  void keyReleased(int key);
  
  void mouseMoved(int x, int y);
  
  void mouseDragged(int x, int y, int button) {}
  
  void mousePressed(int x, int y, int button) {}
  
  void mouseReleased(int x, int y, int button) {}
  
  void windowResized(int w, int h) {}
  
  void dragEvent(ofDragInfo dragInfo) {}
  
  void gotMessage(ofMessage msg) {}
  
private:
  /**
   * Private member variables.
   */
  Model model;
  View view;
  Controller controller;
};

#endif  // TEXTTENNIS_H_
