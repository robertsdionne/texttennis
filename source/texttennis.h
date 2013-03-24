#ifndef TEXTTENNIS_H_
#define TEXTTENNIS_H_

#include <Box2D/Box2D.h>
#include <tr1/functional>
#include <vector>

#include "constants.h"
#include "scene2controller.h"
#include "introduction.h"
#include "scene2model.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "scene.h"
#include "scene2view.h"

class TextTennis : public ofBaseApp {
public:
  /**
   * Public method declarations.
   */
  TextTennis();

  virtual ~TextTennis();

  void NextScene();

  void PreviousScene();

  void RestartScene();

  void ToggleSettings();
  
  void setup();
  
  void update();
  
  void draw();

private:
  void CreateScene();

  void DeleteCurrentScene();

  typedef std::tr1::function<Scene *(TextTennis &)> SceneFactoryFunction;

  std::vector<SceneFactoryFunction> scene_factory_functions;
  int scene_index;
  Scene *current_scene;

  bool show_sliders;
  ofxPanel float_panel;
  ofxPanel int_panel;
};

#endif  // TEXTTENNIS_H_
