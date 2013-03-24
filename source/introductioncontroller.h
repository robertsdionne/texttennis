#ifndef TEXTTENNIS_INTRODUCTIONCONTROLLER_H_
#define TEXTTENNIS_INTRODUCTIONCONTROLLER_H_

#include "controller.h"

class IntroductionModel;

class IntroductionController : public Controller {
public:
  IntroductionController(TextTennis &scene_manager, IntroductionModel &model);

  virtual ~IntroductionController() {};

  virtual void Setup() override;

  virtual void Update() override;

  virtual Model &model();

private:
  void CreateBox(ofVec2f position = ofVec2f(), ofVec2f velocity = ofVec2f(),
                 float angle = default_angle, float angular_velocity = default_angular_velocity);

private:
  IntroductionModel &model_;
};

#endif  // TEXTTENNIS_INTRODUCTIONCONTROLLER_H_
