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
  ofTrueTypeFont font;
};

#endif  // TEXTTENNIS_SCENE5VIEW_H_
