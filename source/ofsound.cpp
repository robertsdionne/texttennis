#include "ofsound.h"

bool OfSound::IsPlaying() {
  return sound.getIsPlaying() && volume >= sound_volume_rate;
}

void OfSound::Play(float volume_target) {
  SetVolumeTarget(volume_target);
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
}
