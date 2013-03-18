#ifndef TEXTTENNIS_VIEW_H_
#define TEXTTENNIS_VIEW_H_

#include "ofMain.h"

class Model;

class View {
public:
  View() {}
  
  virtual ~View() {}
  
  void Setup();
  
  void Draw(Model &model) const;
  
private:
  void DrawBall(ofVec2f position, float angle) const;
  
  void DrawCourt() const;
  
  void DrawFrameRate() const;
  
  void DrawNet() const;
  
  void DrawRacket(ofVec2f position) const;
};

#endif  // TEXTTENNIS_VIEW_H_
