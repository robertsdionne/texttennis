#ifndef TEXTTENNIS_INTRODUCTIONVIEW_H_
#define TEXTTENNIS_INTRODUCTIONVIEW_H_

#include "ofMain.h"
#include "view.h"

class IntroductionView {
public:
  IntroductionView();

  virtual ~IntroductionView() {}

  virtual void Setup() const;

  virtual void Draw(Model &model);

private:
  void DrawBox(ofVec2f position, float angle) const;

  ofImage background;
};

#endif  // TEXTTENNIS_INTRODUCTIONVIEW_H_
