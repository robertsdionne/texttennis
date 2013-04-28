#include "music.h"
#include "ofsound.h"
#include "sound.h"

Music::Music()
: events(), event_index(0), playing(), transitions(), crossfading(true) {}

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

Music &Music::Song(const std::string &song, bool loop) {
  events.push_back(new SongEvent(song, loop));
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
        sound->Play();
        queued.push_back(sound);
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
    for (auto sound : playing) {
      //sound->SetVolumeTarget(ofClamp(1.0 - crossfade, 0.0, 1.0));
    }
    for (auto sound : queued) {
      //sound->SetVolumeTarget(ofClamp(crossfade, 0.0, 1.0));
    }
//    const float step = duration == 0 ? 1.0 : 1.0 / 60.0 / duration;
//    if (crossfade < 1.0 - step) {
//      crossfade += step;
//    } else {
      crossfading = false;
      for (auto sound : playing) {
        sound->Stop();
        garbage.push_back(sound);
      }
      playing = queued;
      queued.clear();
//    }
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
