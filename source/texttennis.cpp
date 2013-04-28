#include <Box2D/Box2D.h>

#include "constants.h"
#include "introduction.h"
#include "parameter.h"
#include "scene.h"
#include "scene1.h"
#include "scene2.h"
#include "scene3.h"
#include "scene4.h"
#include "scene5.h"
#include "slider.h"
#include "texttennis.h"

/**
 * Public method definitions.
 */
TextTennis::TextTennis()
: scene_factory_functions(), scene_index(0), current_scene(nullptr),
  show_sliders(false), float_panel(), int_panel(), transition(nullptr),
  tree1("tree1.wav", false, true),
  tree2("tree2.wav", false, true),
  tree3("tree3.wav", false, true),
  tree4("tree4.wav", false, true),
  tree5("tree5.wav", false, true),
  opponents(nullptr) {
  scene_factory_functions.push_back(Introduction::Create);
  scene_factory_functions.push_back(Scene1::Create);
  scene_factory_functions.push_back(Scene3::Create);
  scene_factory_functions.push_back(Scene4::Create);
  scene_factory_functions.push_back(Scene2::Create);
  scene_factory_functions.push_back(Scene5::Create);
}

TextTennis::~TextTennis() {
  for (int i = 0; i < float_panel.getNumControls(); ++i) {
    delete float_panel.getControl(i);
  }
  float_panel.clear();
  for (int i = 0; i < int_panel.getNumControls(); ++i) {
    delete int_panel.getControl(i);
  }
  int_panel.clear();
  delete opponents;
}

void TextTennis::setup() {
  std::vector<std::string> loops;
  loops.push_back("low_snd.wav");
  loops.push_back("arpeg_1.wav");
  loops.push_back("arpeg_2.wav");
  loops.push_back("arpeg_3.wav");
  loops.push_back("arpeg_4.wav");
  loops.push_back("speak_1.wav");
  loops.push_back("speak_2.wav");
  loops.push_back("speak_3.wav");
  opponents = new LoopSet(loops);
  music.Song("intro_loop.wav").Transition("scene1")
      .Song("main_theme.wav").Transition("scene3")
      .SoundEffect("opponents", *opponents).Transition("scene4")
      .SoundEffect("tree1", tree1).SoundEffect("tree2", tree2).SoundEffect("tree3", tree3)
      .SoundEffect("tree4", tree4).SoundEffect("tree5", tree5)
      .Song("treeloop1.wav", true).Song("treeloop2.wav", true).Song("treeloop3.wav", true).Transition("scene2")
      .Song("scene02_lows.wav").Song("scene02_highs.wav").Transition("scene5").Transition("introduction");
  ofSetFrameRate(60.0);
  CreateScene();
  float_panel.setup("float parameters");
  for (auto parameter : Parameter<float>::GetParameters()) {
    float_panel.add(new Slider<float>(parameter));
  }
  int_panel.setup("int parameters", "settings.xml",
                  float_panel.getPosition().x + float_panel.getWidth() + 1);
  for (auto parameter : Parameter<int>::GetParameters()) {
    int_panel.add(new Slider<int>(parameter));
  }
}

void TextTennis::update() {
  music.Update();
  if (transition && !transition->IsDone()) {
    transition->Update();
  } else if (current_scene) {
    current_scene->Update();
  }
}

void TextTennis::draw() {
  if (transition && !transition->IsDone()) {
    transition->Draw();
  } else if (current_scene) {
    current_scene->Draw();
  }
  if (show_sliders) {
    ofSetRectMode(OF_RECTMODE_CORNER);
    float_panel.draw();
    int_panel.draw();
  }
}

void TextTennis::NextScene() {
  scene_index = (scene_index + 1) % scene_factory_functions.size();
  CreateScene();
}

Music &TextTennis::GetMusic() {
  return music;
}

void TextTennis::PreviousScene() {
//  scene_index = (scene_index + scene_factory_functions.size() - 1) % scene_factory_functions.size();
//  CreateScene();
}

void TextTennis::RestartScene() {
  CreateScene();
}

void TextTennis::ToggleSettings() {
  show_sliders = !show_sliders;
}

void TextTennis::CreateScene() {
  ofPoint player_position;
  bool needs_transition = current_scene;
  if (current_scene) {
    player_position = current_scene->GetPlayerPosition();
  } else {
    player_position = racket1_start_position.GetValue();
  }
  ofImage from;
  if (current_scene) {
    from = current_scene->DrawImage();
  }
  DeleteCurrentScene();
  current_scene = scene_factory_functions[scene_index](*this, player_position);
  current_scene->Setup();
  current_scene->Update();
  ofImage to = current_scene->DrawImage();
  if (needs_transition) {
    if (transition) {
      delete transition;
      transition = nullptr;
    }
    transition = new Transition(from, to);
    transition->Setup();
  } else if (transition) {
    delete transition;
    transition = nullptr;
  }
}

void TextTennis::DeleteCurrentScene() {
  if (current_scene) {
    delete current_scene;
    current_scene = nullptr;
  }
}
