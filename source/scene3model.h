#ifndef TEXTTENNIS_SCENE3MODEL_H_
#define TEXTTENNIS_SCENE3MODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "fontdialogue.h"
#include "model.h"
#include "ofMain.h"

class Scene3Model : public Model {
public:
  Scene3Model(ofPoint player_position);
  
  virtual ~Scene3Model() {}
  
public:
  b2World world;
  b2Body *ball_body, *court_body, *border_body, *net_body, *eight_body;
  std::vector<b2Body *> extra_balls;
  
  ofVec2f racket1, opponent;
  ofVec2f racket1_target, opponent_target;

  int score;

  int bounces;

  float angle;

  FontDialogue dialogue;

  bool ball_in_play, opponent_visible;

  int opponent_index;
  bool served, time_slowed;

  int glass_hits = 0;
  float glass = 0.0;
  float last_hit = 0.0;

  bool eight_on_left_side = false;

  struct Trail {
    ofPoint position;
    const char *text;
  };

  std::deque<Trail> ball_trail;

  float nerd_energy = 1.0;
};

#endif  // TEXTTENNIS_SCENE3MODEL_H_
