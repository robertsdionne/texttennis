#ifndef TEXTTENNIS_H_
#define TEXTTENNIS_H_

#include <Box2D/Box2D.h>
#include <tr1/functional>
#include <vector>

#include "constants.h"
#include "controller.h"
#include "gameobject.h"
#include "gamestate.h"
#include "introduction.h"
#include "model.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "scene.h"
#include "view.h"

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

  ofxPanel float_panel;
};

#endif  // TEXTTENNIS_H_
