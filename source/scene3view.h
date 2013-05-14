#ifndef TEXTTENNIS_SCENE3VIEW_H_
#define TEXTTENNIS_SCENE3VIEW_H_

#include "ofMain.h"
#include "view.h"

class Scene3Model;

class Scene3View : public View {
public:
  Scene3View();
  
  virtual ~Scene3View() {}
  
  virtual void Setup() override;
  
  virtual void Draw(Model &model) override;
  
private:
  void DrawBall(Scene3Model &model, ofVec2f position, float angle, bool inverted = false) const;
  
  void DrawCourt() const;
  
  void DrawFrameRate() const;
  
  void DrawNet() const;

  void DrawOpponent(const Scene3Model &model) const;
  
  void DrawRacket(ofVec2f position, bool inverted = false) const;

private:
  float HalfLambert(ofVec3f light, ofVec3f normal);

  ofImage top[10];
  ofImage bottom[10];
  ofImage left[10];
  
  ofTrueTypeFont font;
};

#endif  // TEXTTENNIS_SCENE3VIEW_H_
