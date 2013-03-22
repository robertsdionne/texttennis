#include "slider.h"
#include "ofGraphics.h"
#include "parameter.h"

template<typename T>
Slider<T>::Slider(Parameter<T> *parameter, float width, float height) : parameter(parameter) {
  b = ofRectangle(0, 0, width, height);
  currentFrame = ofGetFrameNum();
  bGuiActive = false;
  ofRegisterMouseEvents(this);
}

template<typename T>
void Slider<T>::mouseMoved(ofMouseEventArgs &args){
}

template<typename T>
void Slider<T>::mousePressed(ofMouseEventArgs &args){
  setValue(args.x, args.y, true);
}

template<typename T>
void Slider<T>::mouseDragged(ofMouseEventArgs & args){
  setValue(args.x, args.y, false);
}

template<typename T>
void Slider<T>::mouseReleased(ofMouseEventArgs & args){
  bGuiActive = false;
}

template<typename T>
void Slider<T>::draw(){
  ofPushStyle();
  ofPushMatrix();

  currentFrame = ofGetFrameNum();
  ofFill();
  ofSetColor(backgroundColor);
  ofRect(b);

  ofTranslate(b.x, b.y);
  float valAsPct = ofMap( *parameter, parameter->min, parameter->max, 0, b.width-2, true );
  ofEnableAlphaBlending();
  ofSetColor(fillColor);
  ofRect(1, 1, valAsPct, b.height-2);

  ofTranslate(0, b.height / 2 + 4);
  ofSetColor(textColor);
  ofDrawBitmapString(parameter->GetName(), textPadding, 0);
  std::string valStr = ofToString(T(*parameter));
  ofDrawBitmapString(valStr, b.width - textPadding - valStr.length() * 8, 0);

  ofPopMatrix();
  ofPopStyle();
}

template<typename T>
void Slider<T>::setValue(float mx, float my, bool bCheck){
  if( ofGetFrameNum() - currentFrame > 1 ){
    bGuiActive = false;
    return;
  }
  if( bCheck ){
    if( b.inside(mx, my) ){
      bGuiActive = true;
    }else{
      bGuiActive = false;
    }
  }
  if( bGuiActive ){
    *parameter = ofMap(mx, b.x, b.x + b.width, parameter->min, parameter->max, true);
  }
}

template class Slider<int>;
template class Slider<float>;
