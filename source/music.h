#ifndef TEXTTENNIS_MUSIC_H_
#define TEXTTENNIS_MUSIC_H_

#include <map>
#include <string>
#include <vector>

#include "ofMain.h"

class Music {
public:
  Music();
  virtual ~Music();

  struct Sound {
    std::string filename;
    ofSoundPlayer *player;
  };

  class Event {
  public:
    enum class Type {
      SONG,
      TRANSITION
    };
    Event(Type type) : type(type) {}
    virtual ~Event() {}
    Type type;
  };

  class SongEvent : public Event {
  public:
    SongEvent(const std::string &song, bool loop)
    : Event(Event::Type::SONG), song(song), loop(loop) {}
    virtual ~SongEvent() {}
    std::string song;
    bool loop;
  };

  class TransitionEvent : public Event {
  public:
    TransitionEvent(const std::string &transition, float duration)
    : Event(Event::Type::TRANSITION), transition(transition), duration(duration) {}
    virtual ~TransitionEvent() {}
    std::string transition;
    float duration;
  };

  bool IsBlocked() const;

  bool IsBlocked(const std::string &barrier);

  bool IsDone() const;

  Music &Song(const std::string &song, bool loop = false);

  Music &Transition(const std::string &transition, float duration = 5.0);

  void Trigger(const std::string &transition);

  void Update();

private:
  std::vector<Event *> events;
  int event_index;
  float crossfade, duration;
  std::vector<Sound> playing, queued;
  std::map<std::string, bool> transitions;
  bool crossfading;
};

#endif  // TEXTTENNIS_MUSIC_H_
