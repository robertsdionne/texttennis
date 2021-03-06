#ifndef TEXTTENNIS_SCENE2VIEW_H_
#define TEXTTENNIS_SCENE2VIEW_H_

#include "ofMain.h"
#include "view.h"

class Scene2Model;

class Scene2View : public View {
public:
  Scene2View();
  
  virtual ~Scene2View() {}
  
  virtual void Setup() override;
  
  virtual void Draw(Model &model) override;
  
private:
  void DrawBall(Scene2Model &model, ofVec2f position, float radius, float angle) const;
  
  void DrawCourt() const;
  
  void DrawFrameRate() const;
  
  void DrawNet() const;
  
  void DrawRacket(ofVec2f position) const;

private:
  ofImage bg;
  ofTrueTypeFont font;
};

#endif  // TEXTTENNIS_SCENE2VIEW_H_
