#ifndef TEXTTENNIS_INTRODUCTIONVIEW_H_
#define TEXTTENNIS_INTRODUCTIONVIEW_H_

#include "view.h"

class IntroductionView {
public:
  IntroductionView() {}

  virtual ~IntroductionView() {}

  virtual void Setup() const;

  virtual void Draw(Model &model) const;

private:
  void DrawBox(ofVec2f position, float angle) const;
};

#endif  // TEXTTENNIS_INTRODUCTIONVIEW_H_
