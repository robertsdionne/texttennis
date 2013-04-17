#ifndef TEXTTENNIS_DIALOGUE_H_
#define TEXTTENNIS_DIALOGUE_H_

#include <deque>

#include "ofMain.h"

class Dialogue {
public:
  Dialogue();

  virtual ~Dialogue();

  class Event {
  public:
    enum class Type {
      CLEAR,
      MESSAGE,
      PAUSE,
      POP,
      SPEED
    };
    Event(Type type) : type(type) {}
    virtual ~Event() {}
    Type type;
  };

  class Clear : public Event {
  public:
    Clear() : Event(Event::Type::CLEAR) {}
    virtual ~Clear() {}
  };

  class Message : public Event {
  public:
    Message(const std::string &message, ofPoint position)
    : message(message), position(position), Event(Event::Type::MESSAGE) {}
    virtual ~Message() {}
    std::string message;
    ofPoint position;
  };

  class Pause : public Event {
  public:
    Pause(float duration) : duration(duration), Event(Event::Type::PAUSE) {}
    virtual ~Pause() {}
    float duration;
  };

  class Pop : public Event {
  public:
    Pop() : Event(Event::Type::POP) {}
    virtual ~Pop() {}
  };

  class Speed : public Event {
  public:
    Speed(float speed) : speed(speed), Event(Event::Type::SPEED) {}
    virtual ~Speed() {}
    float speed;
  };

  Dialogue &AddClear();

  Dialogue &AddMessage(const std::string &message, ofPoint position);

  Dialogue &AddPause(float duration);

  Dialogue &AddPop();

  Dialogue &AddSpeed(float speed);

  void Draw();

  bool IsDone() const;

  void Setup();

  void Update();

private:
  std::vector<Event *> events;
  float last_event_time, current_delay, speed;
  std::deque<Message *> last_messages;
  int event_index, message_index;
};

#endif  // TEXTTENNIS_DIALOGUE_H_
