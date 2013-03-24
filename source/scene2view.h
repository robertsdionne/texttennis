#ifndef TEXTTENNIS_SCENE2VIEW_H_
#define TEXTTENNIS_SCENE2VIEW_H_

#include "ofMain.h"
#include "view.h"

class Scene2Model;

class Scene2View : public View {
public:
  Scene2View() {}
  
  virtual ~Scene2View() {}
  
  virtual void Setup() const;
  
  virtual void Draw(Model &model) const;
  
private:
  void DrawBall(ofVec2f position, float angle) const;
  
  void DrawCourt() const;
  
  void DrawFrameRate() const;
  
  void DrawNet() const;
  
  void DrawRacket(ofVec2f position) const;
};

#endif  // TEXTTENNIS_SCENE2VIEW_H_