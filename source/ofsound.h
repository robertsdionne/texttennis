#ifndef TEXTTENNIS_OFSOUND_H_
#define TEXTTENNIS_OFSOUND_H_

#include <string>

#include "sound.h"

class OfSound : public Sound {
public:
  OfSound(const std::string &filename, bool loop = false, bool stream = false)
  : filename(filename), sound(), volume(0.0) {
    sound.loadSound(filename, stream);
    sound.setVolume(0.0);
    sound.setLoop(loop);
  }

  virtual ~OfSound() {}

  virtual bool IsPlaying();

  virtual void Play();

  virtual void Stop();

  virtual void Update();

private:
  std::string filename;
  ofSoundPlayer sound;
  float volume;
};

#endif  // TEXTTENNIS_OFSOUND_H_
