#ifndef TEXTTENNIS_SCENE4VIEW_H_
#define TEXTTENNIS_SCENE4VIEW_H_

#include "ofMain.h"
#include "view.h"

class Scene4Model;

class Scene4View : public View {
public:
  Scene4View();
  
  virtual ~Scene4View() {}
  
  virtual void Setup() override;
  
  virtual void Draw(Model &model) override;
  
private:
  void DrawBall(Scene4Model &model, ofVec2f position, float angle);
  
  void DrawCourt() const;
  
  void DrawFrameRate() const;
  
  void DrawNet() const;
  
  void DrawRacket(ofVec2f position) const;

  void DrawParticles (Scene4Model &model);

  void DrawTreePeople(Scene4Model &model) const;

  float H01(float t) const;

  ofImage background;
  ofImage trees[5];
};

#endif  // TEXTTENNIS_SCENE4VIEW_H_
