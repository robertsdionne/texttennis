#ifndef TEXTTENNIS_INTERLUDE1_H_
#define TEXTTENNIS_INTERLUDE1_H_

#include <string>

#include "controller.h"
#include "fontdialogue.h"
#include "ofMain.h"
#include "model.h"
#include "scene.h"
#include "scene1model.h"

class Model;

class TextTennis;

class Interlude1 : public Scene, Controller {
public:
  Interlude1(TextTennis &scene_manager, ofPoint player_position,
             const std::string &text, const std::string &transition, float delay);

  virtual ~Interlude1();

  static Scene *Create(TextTennis &scene_manager, ofPoint player_position,
                       const std::string &text, const std::string &transition, float delay = 2.0);

  virtual void Draw();

  virtual void Setup();

  virtual void Update();

  virtual ofPoint GetPlayerPosition() {
    return player_position;
  }

  virtual Model &model();

private:
  Scene1Model model_;
  ofPoint player_position;
  std::string text, transition;
  Dialogue *dialogue;
  float delay;
  bool done;
};

#endif  // TEXTTENNIS_INTERLUDE1_H_
