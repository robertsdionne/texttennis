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

  class ClearEvent : public Event {
  public:
    ClearEvent() : Event(Event::Type::CLEAR) {}
    virtual ~ClearEvent() {}
  };

  class MessageEvent : public Event {
  public:
    MessageEvent(const std::string &message, ofPoint position)
    : message(message), position(position), Event(Event::Type::MESSAGE) {}
    virtual ~MessageEvent() {}
    std::string message;
    ofPoint position;
  };

  class PauseEvent : public Event {
  public:
    PauseEvent(float duration) : duration(duration), Event(Event::Type::PAUSE) {}
    virtual ~PauseEvent() {}
    float duration;
  };

  class PopEvent : public Event {
  public:
    PopEvent() : Event(Event::Type::POP) {}
    virtual ~PopEvent() {}
  };

  class SpeedEvent : public Event {
  public:
    SpeedEvent(float speed) : speed(speed), Event(Event::Type::SPEED) {}
    virtual ~SpeedEvent() {}
    float speed;
  };

  Dialogue &Clear();

  Dialogue &Message(const std::string &message, ofPoint position);

  Dialogue &Pause(float duration);

  Dialogue &Pop();

  Dialogue &Speed(float speed);

  void Draw();

  bool IsDone() const;

  void Setup();

  void Update();

private:
  std::vector<Event *> events;
  float last_event_time, current_delay, speed;
  std::deque<MessageEvent *> last_messages;
  int event_index, message_index;
};

#endif  // TEXTTENNIS_DIALOGUE_H_
