#include "music.h"

Music::Music()
: events(), event_index(0), crossfade(0), duration(5.0),
  playing(), transitions(), crossfading(true) {}

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

Music &Music::Transition(const std::string &transition, float duration) {
  events.push_back(new TransitionEvent(transition, duration));
  return *this;
}

void Music::Trigger(const std::string &transition) {
  transitions[transition] = false;
  if (crossfading) {
    std::cout << crossfade << std::endl;
    for (auto sound : playing) {
      sound->setVolume(ofClamp(1.0 - crossfade, 0.0, 1.0));
    }
    for (auto sound : queued) {
      sound->setVolume(ofClamp(crossfade, 0.0, 1.0));
    }
    const float step = duration == 0 ? 1.0 : 1.0 / 60.0 / duration;
    if (crossfade < 1.0 - step) {
      crossfade += step;
    } else {
      std::cout << "stop" << std::endl;
      crossfading = false;
      for (auto sound : playing) {
        sound->stop();
        delete sound;
      }
      playing = queued;
      queued.clear();
    }
  }
  crossfade = 0.0;
  crossfading = true;
  for (auto sound : queued) {
    sound->setVolume(0.0);
    sound->play();
  }
}

void Music::Update() {
  if (!IsBlocked()) {
    Event *event = events[event_index];
    switch (event->type) {
      case Event::Type::SONG: {
        SongEvent *song = dynamic_cast<SongEvent *>(event);
        ofSoundPlayer *player = new ofSoundPlayer();
        player->loadSound(song->song, true);
        player->setLoop(song->loop);
        queued.push_back(player);
        break;
      }
      case Event::Type::TRANSITION: {
        TransitionEvent *transition = dynamic_cast<TransitionEvent *>(event);
        transitions[transition->transition] = true;
        duration = transition->duration;
        for (auto sound : queued) {
          sound->play();
        }
        break;
      }
      default:
        break;
    }
    event_index = (event_index + 1) % events.size();
  } else if (crossfading) {
    std::cout << crossfade << std::endl;
    for (auto sound : playing) {
      sound->setVolume(ofClamp(1.0 - crossfade, 0.0, 1.0));
    }
    for (auto sound : queued) {
      sound->setVolume(ofClamp(crossfade, 0.0, 1.0));
    }
    const float step = duration == 0 ? 1.0 : 1.0 / 60.0 / duration;
    if (crossfade < 1.0 - step) {
      crossfade += step;
    } else {
      std::cout << "stop" << std::endl;
      crossfading = false;
      for (auto sound : playing) {
        sound->stop();
        delete sound;
      }
      playing = queued;
      queued.clear();
    }
  }
}
