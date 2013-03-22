#ifndef TEXTTENNIS_SLIDER_H_
#define TEXTTENNIS_SLIDER_H_

#include <string>

#include "ofxBaseGui.h"
#include "parameter.h"

template<typename T>
class Slider : public ofxBaseGui {
  friend class ofPanel;

public:
  Slider() {}
  Slider(Parameter<T> *parameter, float width = defaultWidth, float height = defaultHeight);

  virtual void mouseMoved(ofMouseEventArgs &args);
  virtual void mousePressed(ofMouseEventArgs &args);
  virtual void mouseDragged(ofMouseEventArgs &args);
  virtual void mouseReleased(ofMouseEventArgs &args);

  virtual void saveToXml(ofxXmlSettings &xml) {};
  virtual void loadFromXml(ofxXmlSettings &xml) {};

  void draw();

  Parameter<T> *parameter;

protected:
  void setValue(float mx, float my, bool bCheck);
};

#endif  // TEXTTENNIS_SLIDER_H_
