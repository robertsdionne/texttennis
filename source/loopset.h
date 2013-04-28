#ifndef TEXTTENNIS_LOOPSET_H_
#define TEXTTENNIS_LOOPSET_H_

#include "ofsound.h"
#include "sound.h"

class LoopSet : public Sound {
public:
  LoopSet(const std::vector<std::string> &sound_names) : volume_targets(), sounds() {
    for (auto sound : sound_names) {
      sounds.push_back(new OfSound(sound, true, true));
      volume_targets.push_back(0.0);
    }
  }

  virtual ~LoopSet() {
    for (auto sound : sounds) {
      delete sound;
    }
    sounds.clear();
  }

  virtual bool IsPlaying();

  virtual void Play(float volume_target = 1.0);

  virtual void SetVolumeTargets(const std::vector<float> &new_volume_targets);

  virtual void Stop();

  virtual void Update();

private:
  std::vector<float> volume_targets;
  std::vector<OfSound *> sounds;
};

#endif  // TEXTTENNIS_LOOPSET_H_
