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
  
  void DrawCourt() const;
  
  void DrawFrameRate() const;
  
  void DrawNet() const;
  
  void DrawRacket(ofVec2f position) const;

  float H01(float t);
};

#endif  // TEXTTENNIS_SCENE1VIEW_H_
