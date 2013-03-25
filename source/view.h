#ifndef TEXTTENNIS_VIEW_H_
#define TEXTTENNIS_VIEW_H_

class Model;

class View {
public:
  virtual ~View() {}

  virtual void Setup() = 0;

  virtual void Draw(Model &model) = 0;

protected:
  View() {}
};

#endif  // TEXTTENNIS_VIEW_H_
