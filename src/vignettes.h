//
//  vignettes.h
//  texttennis
//
//  Created by Robert Dionne on 3/2/13.
//
//

#ifndef __texttennis__vignettes__
#define __texttennis__vignettes__

#include <map>

#include "ofMain.h"
#include "man.h"

class Vignettes : public ofBaseApp {
public:
  void setup();
  
  void update();
  
  void draw();
  
  void keyPressed(int key);
  
  void keyReleased(int key);
  
  void mouseMoved(int x, int y);
  
  void mouseDragged(int x, int y, int button);
  
  void mousePressed(int x, int y, int button);
  
  void mouseReleased(int x, int y, int button);
  
  void windowResized(int w, int h);
  
  void dragEvent(ofDragInfo dragInfo);
  
  void gotMessage(ofMessage msg);
  
private:
  static constexpr float kFadeInDuration = 40.0;
  static constexpr int kFrameRate = 60;
  static constexpr float kMaxAlpha = 255.0;
  static constexpr float kAlphaDelta = kMaxAlpha / kFrameRate / kFadeInDuration;
  
  static constexpr const char *kCliffsideFilename = "../../assets/cliffside.png";
  static constexpr const char *kCrossroadsFilename = "../../assets/crossroads.png";
  static constexpr const char *kInsanityMusicFilename = "../../assets/insanity_music.mp3";
  static constexpr const char *kManLeft0Filename = "../../assets/man_0l.png";
  static constexpr const char *kManLeft1Filename = "../../assets/man_1l.png";
  static constexpr const char *kManLeft2Filename = "../../assets/man_2l.png";
  static constexpr const char *kManRight0Filename = "../../assets/man_0r.png";
  static constexpr const char *kManRight1Filename = "../../assets/man_1r.png";
  static constexpr const char *kManRight2Filename = "../../assets/man_2r.png";
  static constexpr const char *kSignpostFilename = "../../assets/signpost.png";
  static constexpr const char *kUbuntuRegular = "../../assets/Ubuntu-R.ttf";
  static constexpr const char *kUbuntuMonoRegular = "../../assets/UbuntuMono-R.ttf";
  
  static constexpr const char *kVignetteText = R"(It is an autumn morning and you awake. You are crazy.
You look at the sky and the ground both. You're getting up.
Walking.
  
Nothing is destroyed--things are gradually given shape--
they are evolved and turned into other energy.
  
There is no logic of destination--predestination is a dump truck.
  
You are recycling.)";
  
  bool increase_background;
  float background;
  float background_alpha;
  long text_cursor;
  Man man;
  ofImage image_cliffside;
  ofImage image_crossroads;
  ofImage image_man_left_0;
  ofImage image_man_left_1;
  ofImage image_man_left_2;
  ofImage image_man_right_0;
  ofImage image_man_right_1;
  ofImage image_man_right_2;
  ofImage image_signpost;
  ofSoundPlayer sound_insanity_music;
  ofTrueTypeFont font_ubuntu_regular;
  ofTrueTypeFont font_ubuntu_mono_regular;
  std::map<int, bool> previous_keys;
  std::map<int, bool> keys;
};

#endif /* defined(__texttennis__vignettes__) */
