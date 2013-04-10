#ifndef TEXTTENNIS_FLIPSCENEVIEW_H_
#define TEXTTENNIS_FLIPSCENEVIEW_H_

#include "ofMain.h"
#include "view.h"

class FlipSceneModel;
class Model;

class FlipSceneView : public View {
public:
  FlipSceneView() {}
  
  virtual ~FlipSceneView() {}
  
  virtual void Setup() override;
  
  virtual void Draw(Model &model) override;

private:
  float HalfLambert(ofVec3f light, ofVec3f normal);

  ofImage top[10];
  ofImage bottom[10];
};

#endif  // TEXTTENNIS_FLIPSCENEVIEW_H_
