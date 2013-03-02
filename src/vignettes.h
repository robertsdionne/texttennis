//
//  vignettes.h
//  texttennis
//
//  Created by Robert Dionne on 3/2/13.
//
//

#ifndef __texttennis__vignettes__
#define __texttennis__vignettes__

#include <map>

#include "ofMain.h"

class Vignettes : public ofBaseApp {
public:
  void setup();
  
  void update();
  
  void draw();
  
  void keyPressed(int key);
  
  void keyReleased(int key);
  
  void mouseMoved(int x, int y);
  
  void mouseDragged(int x, int y, int button);
  
  void mousePressed(int x, int y, int button);
  
  void mouseReleased(int x, int y, int button);
  
  void windowResized(int w, int h);
  
  void dragEvent(ofDragInfo dragInfo);
  
  void gotMessage(ofMessage msg);
  
private:
  std::map<int, bool> previous_keys;
  std::map<int, bool> keys;
};

#endif /* defined(__texttennis__vignettes__) */
