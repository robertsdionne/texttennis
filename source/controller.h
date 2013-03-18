#ifndef TEXTTENNIS_CONTROLLER_H_
#define TEXTTENNIS_CONTROLLER_H_

#include <map>

class Controller {
public:
  Controller();
  
  virtual ~Controller() {}
  
  void OnKeyPressed(int key);
  
  void OnKeyReleased(int key);
  
  void OnMouseDragged(int x, int y, int button);
  
  void OnMouseMoved(int x, int y);
  
  void OnMousePressed(int x, int y, int button);
  
  void OnMouseReleased(int x, int y, int button);
  
  void Update();
  
private:
  bool MouseButtonIsPressed(int button);
  
private:
  std::map<int, bool> buttons, keys, previous_buttons, previous_keys;
};

#endif  // TEXTTENNIS_CONTROLLER_H_
