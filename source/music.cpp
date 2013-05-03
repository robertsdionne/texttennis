#include "music.h"
#include "ofsound.h"
#include "sound.h"

Music::Music()
: events(), event_index(0), playing(), queued(), garbage(),
  sounds(), transitions(), crossfading(true) {}

Music::~Music() {
  for (auto *event : events) {
    delete event;
  }
  events.clear();
}

bool Music::IsBlocked() const {
  for (auto entry : transitions) {
    if (entry.second) {
      return true;
    }
  }
  return false;
}

bool Music::IsBlocked(const std::string &transition) {
  if (transitions[transition]) {
    return true;
  } else {
    return false;
  }
}

bool Music::IsDone() const {
  return event_index == events.size();
}

void Music::PlaySoundEffect(const std::string &sound) {
  sounds[sound]->Play();
}

Music &Music::Song(const std::string &song, bool loop, float volume) {
  events.push_back(new SongEvent(song, loop, volume));
  return *this;
}

Music &Music::SoundEffect(const std::string &name, Sound &sound, bool loop) {
  events.push_back(new SoundEffectEvent(name, &sound, loop));
  return *this;
}

Music &Music::Transition(const std::string &transition) {
  events.push_back(new TransitionEvent(transition));
  return *this;
}

void Music::TriggerTransition(const std::string &transition) {
  transitions[transition] = false;
  if (crossfading) {
    crossfading = false;
    for (auto sound : playing) {
      sound->Stop();
      delete sound;
    }
    playing = queued;
    queued.clear();
  }
  crossfading = true;
}

void Music::Update() {
  if (!IsBlocked()) {
    Event *event = events[event_index];
    switch (event->type) {
      case Event::Type::SONG: {
        SongEvent *song = dynamic_cast<SongEvent *>(event);
        Sound *sound = new OfSound(song->song, true, true);
        sound->SetVolumeTarget(song->volume);
        queued.push_back(sound);
        break;
      }
      case Event::Type::SOUND_EFFECT: {
        SoundEffectEvent *sound_effect = dynamic_cast<SoundEffectEvent *>(event);
        sounds[sound_effect->name] = sound_effect->sound;
        break;
      }
      case Event::Type::TRANSITION: {
        TransitionEvent *transition = dynamic_cast<TransitionEvent *>(event);
        transitions[transition->transition] = true;
        for (auto sound : queued) {
          sound->Play();
        }
        break;
      }
      default:
        break;
    }
    event_index = (event_index + 1) % events.size();
  } else if (crossfading) {
    crossfading = false;
    for (auto sound : playing) {
      sound->Stop();
      garbage.push_back(sound);
    }
    for (auto sound : sounds) {
      sound.second->Stop();
    }
    playing = queued;
    queued.clear();

  }
  for (auto sound : playing) {
    if (sound) {
      sound->Update();
    }
  }
  for (auto sound : queued) {
    if (sound) {
      sound->Update();
    }
  }
  for (auto sound : garbage) {
    if (sound) {
      sound->Update();
    }
  }
  for (auto sound : sounds) {
    if (sound.second) {
      sound.second->Update();
    }
  }
  bool playing = false;
  for (auto sound : garbage) {
    if (sound && sound->IsPlaying()) {
      playing = true;
    }
  }
  if (!playing && garbage.size()) {
    for (auto sound : garbage) {
      if (sound) {
        delete sound;
      }
    }
    std::cout << "dumping garbage audio" << std::endl;
    garbage.clear();
  }
}
