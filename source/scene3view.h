#ifndef TEXTTENNIS_SCENE3VIEW_H_
#define TEXTTENNIS_SCENE3VIEW_H_

#include "ofMain.h"
#include "view.h"

class Scene3Model;

class Scene3View : public View {
public:
  Scene3View() {}
  
  virtual ~Scene3View() {}
  
  virtual void Setup() const;
  
  virtual void Draw(Model &model) const;
  
private:
  void DrawBall(ofVec2f position, float angle) const;
  
  void DrawCourt() const;
  
  void DrawFrameRate() const;
  
  void DrawNet() const;
  
  void DrawRacket(ofVec2f position) const;
};

#endif  // TEXTTENNIS_SCENE3VIEW_H_
