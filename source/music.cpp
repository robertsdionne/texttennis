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

void Music::TriggerTransition(const std::string &transition) {
  transitions[transition] = false;
  if (crossfading) {
    crossfading = false;
    for (auto sound : playing) {
      sound.player->stop();
      delete sound.player;
    }
    playing = queued;
    queued.clear();
  }
  crossfade = 0.0;
  crossfading = true;
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
        player->setVolume(0.0);
        player->play();
        Sound object;
        object.player = player;
        object.filename = song->song;
        queued.push_back(object);
        break;
      }
      case Event::Type::TRANSITION: {
        TransitionEvent *transition = dynamic_cast<TransitionEvent *>(event);
        transitions[transition->transition] = true;
        duration = transition->duration;
        for (auto sound : queued) {
          sound.player->play();
        }
        break;
      }
      default:
        break;
    }
    event_index = (event_index + 1) % events.size();
  } else if (crossfading) {
    for (auto sound : playing) {
      sound.player->setVolume(ofClamp(1.0 - crossfade, 0.0, 1.0));
    }
    for (auto sound : queued) {
      sound.player->setVolume(ofClamp(crossfade, 0.0, 1.0));
    }
    const float step = duration == 0 ? 1.0 : 1.0 / 60.0 / duration;
    if (crossfade < 1.0 - step) {
      crossfade += step;
    } else {
      crossfading = false;
      for (auto sound : playing) {
        sound.player->stop();
        delete sound.player;
      }
      playing = queued;
      queued.clear();
    }
  }
}
