#ifndef TEXTTENNIS_H_
#define TEXTTENNIS_H_

#include <Box2D/Box2D.h>
#include <tr1/functional>
#include <string>
#include <vector>

#include "constants.h"
#include "scene2controller.h"
#include "introduction.h"
#include "scene2model.h"
#include "ofMain.h"
#include "ofsound.h"
#include "ofxGui.h"
#include "loopset.h"
#include "music.h"
#include "scene.h"
#include "scene2view.h"
#include "transition.h"

class TextTennis : public ofBaseApp {
public:
  /**
   * Public method declarations.
   */
  TextTennis();

  virtual ~TextTennis();

  void NextScene();

  Music &GetMusic();

  void PreviousScene();

  void RestartScene();

  void ToggleSettings();
  
  void setup();
  
  void update();
  
  void draw();

private:
  void CreateScene();

  void DeleteCurrentScene();

  typedef std::tr1::function<Scene *(TextTennis &, ofPoint)> SceneFactoryFunction;

  std::vector<SceneFactoryFunction> scene_factory_functions;
  int scene_index;
  Scene *current_scene;
  Transition *transition;

  bool show_sliders;
  ofxPanel float_panel;
  ofxPanel int_panel;
  Music music;
  OfSound title_sound;
  OfSound tree1, tree2, tree3, tree4, tree5;
  LoopSet *opponents;
};

#endif  // TEXTTENNIS_H_
