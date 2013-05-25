#include "interlude1.h"
#include "loopset.h"
#include "texttennis.h"

Interlude1::Interlude1(TextTennis &scene_manager, ofPoint player_position,
                       const std::string &text, const std::string &transition, float delay)
: Controller(scene_manager), player_position(player_position),
  model_(), text(text), transition(transition), delay(delay), done(false) {
    if (transition == "scene1") {
      dialogue = new Dialogue();
    } else {
      dialogue = new FontDialogue();
    }
  ofRegisterKeyEvents(static_cast<Controller *>(this));
  ofRegisterMouseEvents(static_cast<Controller *>(this));
}

Interlude1::~Interlude1() {
  if (dialogue) {
    delete dialogue;
    dialogue = nullptr;
  }
  ofUnregisterKeyEvents(static_cast<Controller *>(this));
  ofUnregisterMouseEvents(static_cast<Controller *>(this));
}

Scene *Interlude1::Create(TextTennis &scene_manager, ofPoint player_position,
                          const std::string &text, const std::string &transition, float delay) {
  return new Interlude1(scene_manager, player_position, text, transition, delay);
}

void Interlude1::Draw() {
  ofBackground(ofColor::black);
  ofSetColor(ofColor::white);
  dialogue->Draw();
}

void Interlude1::Setup() {
  if (transition == "scene1") {
    dialogue
    ->Position("spot", ofPoint(100, 100))
    .Foreground(ofColor::white)
    .Background(ofColor(0, 0, 0, 0))
    .Speed(20.0)    .Message(text, "spot").Pause(delay).Then([this] () {
      done = true;
    });
  } else {
    dialogue
    ->Position("spot", ofPoint(100, 100))
    .FontSize(32.0)
    .Speed(5.0)
    .Foreground(ofColor::white)
    .Message(text, "spot").Pause(delay).Then([this] () {
      done = true;
    });
  }
  scene_manager.GetMusic().TriggerTransition(transition);
}

void Interlude1::Update() {
  if (done) {
    scene_manager.NextScene();
    return;
  }
  dialogue->Update();
  if (transition == "scene3" && scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")
      && !scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->IsPlaying()) {
    std::vector<float> volume_targets;
    volume_targets.push_back(0.1); //bass sound
    volume_targets.push_back(0.5); //high arpeg v1
    volume_targets.push_back(0.0); //high arpeg v2
    volume_targets.push_back(0.0); //low arpeg v1
    volume_targets.push_back(0.0); //low arpeg v2
    volume_targets.push_back(0.0); //words 1
    volume_targets.push_back(0.0); //words 2
    volume_targets.push_back(0.0); //words 3
    scene_manager.GetMusic().GetSoundEffect<LoopSet>("opponents")->SetVolumeTargets(volume_targets);
    scene_manager.GetMusic().PlaySoundEffect("opponents");
  }
  Controller::Update();
}

Model &Interlude1::model() {
  return model_;
}
