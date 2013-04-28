#include "loopset.h"

bool LoopSet::IsPlaying() {
  bool playing = false;
  for (auto sound : sounds) {
    playing |= sound->IsPlaying();
  }
  return playing;
}

void LoopSet::Play(float volume_target) {
  SetVolumeTarget(volume_target);
  int index = 0;
  for (auto sound : sounds) {
    sound->Play(volume_target * volume_targets[index++]);
  }
}

void LoopSet::SetVolumeTargets(const std::vector<float> &new_volume_targets) {
  int index = 0;
  for (auto volume : new_volume_targets) {
    if (index < volume_targets.size()) {
      volume_targets[index] = new_volume_targets[index];
    } else {
      volume_targets[index] = 0.0;
    }
    index++;
  }
}

void LoopSet::Stop() {
  SetVolumeTarget(0.0);
}

void LoopSet::Update() {
  int index = 0;
  for (auto sound : sounds) {
    sound->SetVolumeTarget(volume_target * volume_targets[index++]);
    sound->Update();
  }
}
