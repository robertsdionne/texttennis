#ifndef TEXTTENNIS_SCENE1VIEW_H_
#define TEXTTENNIS_SCENE1VIEW_H_

#include "ofMain.h"
#include "view.h"

class Scene1Model;

class Scene1View : public View {
public:
  Scene1View() {}
  
  virtual ~Scene1View() {}
  
  virtual void Setup() override;
  
  virtual void Draw(Model &model) override;
  
private:
  void DrawBall(ofVec2f position, float angle) const;
  
  void DrawCourt(Scene1Model &model) const;
  
  void DrawFrameRate() const;
  
  void DrawNet(Scene1Model &model) const;
  
  void DrawRacket(ofVec2f position) const;

  float H01(float t) const;

  ofImage bg[4];
  ofImage spiral;
};

#endif  // TEXTTENNIS_SCENE1VIEW_H_
