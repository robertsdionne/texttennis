#ifndef TEXTTENNIS_SOUND_H_
#define TEXTTENNIS_SOUND_H_

#include "constants.h"
#include "ofMain.h"

class Sound {
public:
  virtual ~Sound() {}

  virtual bool IsPlaying() = 0;

  virtual void Play() = 0;

  virtual void SetVolumeTarget(float target) {
    volume_target = target;
  }

  virtual void Stop() = 0;

  virtual void Update() = 0;

protected:
  Sound() : volume_target(0.0) {}

  float volume_target;
};

#endif  // TEXTTENNIS_SOUND_H_
