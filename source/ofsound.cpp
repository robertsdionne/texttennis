#include "ofsound.h"

bool OfSound::IsPlaying() {
  return sound.getIsPlaying();
}

void OfSound::Play() {
  SetVolumeTarget(1.0);
  if (!IsPlaying()) {
    sound.play();
    std::cout << "Playing " << filename << std::endl;
  }
}

void OfSound::Stop() {
  SetVolumeTarget(0.0);
}

void OfSound::Update() {
  volume = ofLerp(volume, volume_target, sound_volume_rate);
  sound.setVolume(volume);
  if (sound.getIsPlaying() && volume < sound_volume_rate) {
    sound.stop();
  }
}
