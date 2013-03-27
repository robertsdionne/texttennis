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
  void DrawBall(ofVec2f position, float angle) const;
  
  void DrawCourt() const;
  
  void DrawFrameRate() const;
  
  void DrawNet() const;
  
  void DrawRacket(ofVec2f position) const;

  void DrawTreePeople(Scene4Model &model) const;
};

#endif  // TEXTTENNIS_SCENE4VIEW_H_
