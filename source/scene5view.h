#ifndef TEXTTENNIS_SCENE5VIEW_H_
#define TEXTTENNIS_SCENE5VIEW_H_

#include "ofMain.h"
#include "view.h"

class Scene5Model;

class Scene5View : public View {
public:
  Scene5View();
  
  virtual ~Scene5View() {}
  
  virtual void Setup() override;
  
  virtual void Draw(Model &model) override;
  
private:
  void DrawBall(ofVec2f position, float angle) const;
  
  void DrawCourt() const;
  
  void DrawFrameRate() const;
  
  void DrawNet() const;
  
  void DrawRacket(ofVec2f position) const;

private:
  ofTrueTypeFont font;
};

#endif  // TEXTTENNIS_SCENE5VIEW_H_
