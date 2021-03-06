#ifndef TEXTTENNIS_SCENE2MODEL_H_
#define TEXTTENNIS_SCENE2MODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "dialogue.h"
#include "model.h"
#include "ofMain.h"

class Scene2Model : public Model {
public:
  Scene2Model(ofPoint player_position);
  
  virtual ~Scene2Model() {}
  
public:
  b2World world;
  
  std::list<b2Body *> ball_body;
  
  b2Body *court_body, *border_body, *net_body;
  
  ofVec2f racket1;
  ofVec2f racket1_target;

  float score, inverse_score;
  
  Dialogue dialogue;
};

#endif  // TEXTTENNIS_SCENE2MODEL_H_
