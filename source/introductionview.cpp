#include "constants.h"
#include "introductionmodel.h"
#include "introductionview.h"
#include "model.h"
#include "utilities.h"

void IntroductionView::Setup() const {
  ofSetFrameRate(frame_rate);
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofBackground(ofColor::white);
}

void IntroductionView::Draw(Model &model) const {
  IntroductionModel &introduction_model = dynamic_cast<IntroductionModel &>(model);
  ofSetRectMode(OF_RECTMODE_CENTER);
  ofPushMatrix();
  ofMultMatrix(view_matrix);
  for (auto box : introduction_model.boxes) {
    DrawBox(OpenFrameworksVector(box->GetPosition()), box->GetAngle());
  }
  ofPopMatrix();
}

void IntroductionView::DrawBox(ofVec2f position, float angle) const {
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(position.x, position.y);
  ofRotateZ(ofRadToDeg(angle));
  ofSetColor(ofColor::black);
  ofRect(ofPoint(), 0.5, 0.5);
  ofPopMatrix();
  ofPopStyle();
}
