#ifndef TEXTTENNIS_MUSIC_H_
#define TEXTTENNIS_MUSIC_H_

#include <map>
#include <string>
#include <vector>

#include "ofMain.h"

class Sound;

class Music {
public:
  Music();
  virtual ~Music();

  class Event {
  public:
    enum class Type {
      SONG,
      SOUND_EFFECT,
      TRANSITION
    };
    Event(Type type) : type(type) {}
    virtual ~Event() {}
    Type type;
  };

  class SongEvent : public Event {
  public:
    SongEvent(const std::string &song, bool loop, float volume)
    : Event(Event::Type::SONG), song(song), loop(loop), volume(volume) {}
    virtual ~SongEvent() {}
    std::string song;
    bool loop;
    float volume;
  };

  class SoundEffectEvent : public Event {
  public:
    SoundEffectEvent(const std::string &name, Sound *sound, bool loop)
    : Event(Event::Type::SOUND_EFFECT), name(name), sound(sound), loop(loop) {}
    virtual ~SoundEffectEvent() {}
    std::string name;
    Sound *sound;
    bool loop;
  };

  class TransitionEvent : public Event {
  public:
    TransitionEvent(const std::string &transition)
    : Event(Event::Type::TRANSITION), transition(transition) {}
    virtual ~TransitionEvent() {}
    std::string transition;
  };

  template <typename T>
  T *GetSoundEffect(const std::string &sound) {
    return dynamic_cast<T *>(sounds[sound]);
  }

  bool IsBlocked() const;

  bool IsBlocked(const std::string &barrier);

  bool IsDone() const;

  void PlaySoundEffect(const std::string &sound);

  Music &Song(const std::string &song, bool loop = true, float volume = 1.0);

  Music &SoundEffect(const std::string &name, Sound &sound, bool loop = false);

  Music &Transition(const std::string &transition);

  void TriggerTransition(const std::string &transition);

  void Update();

private:
  std::vector<Event *> events;
  int event_index;
  std::vector<Sound *> playing, queued, garbage;
  std::map<std::string, Sound *> sounds;
  std::map<std::string, bool> transitions;
  bool crossfading;
};

#endif  // TEXTTENNIS_MUSIC_H_
