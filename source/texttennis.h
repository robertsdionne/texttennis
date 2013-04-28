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

  void PlaySoundEffect(const std::string &sound);

  void PreviousScene();

  void RestartScene();

  void ToggleSettings();

  void TriggerTransition(const std::string &transition);
  
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
  OfSound tree1, tree2, tree3, tree4, tree5;
};

#endif  // TEXTTENNIS_H_
