#ifndef TEXTTENNIS_DIALOGUE_H_
#define TEXTTENNIS_DIALOGUE_H_

#include <deque>
#include <map>
#include <vector>

#include "ofMain.h"

class Dialogue {
public:
  Dialogue();

  virtual ~Dialogue();

  class Event {
  public:
    enum class Type {
      BARRIER,
      CLEAR,
      MESSAGE,
      PAUSE,
      POSITION,
      SPEED
    };
    Event(Type type) : type(type) {}
    virtual ~Event() {}
    Type type;
  };

  class BarrierEvent : public Event {
  public:
    BarrierEvent(const std::string &barrier) : Event(Event::Type::BARRIER), barrier(barrier) {}
    virtual ~BarrierEvent() {}
    std::string barrier;
  };

  class ClearEvent : public Event {
  public:
    ClearEvent() : Event(Event::Type::CLEAR) {}
    virtual ~ClearEvent() {}
  };

  class MessageEvent : public Event {
  public:
    MessageEvent(const std::string &message, const std::string &label)
    : Event(Event::Type::MESSAGE), message(message), label(label) {}
    virtual ~MessageEvent() {}
    std::string message;
    std::string label;
  };

  class PauseEvent : public Event {
  public:
    PauseEvent(float duration) : Event(Event::Type::PAUSE), duration(duration) {}
    virtual ~PauseEvent() {}
    float duration;
  };

  class PositionEvent : public Event {
  public:
    PositionEvent(const std::string &label, ofPoint position)
    : Event(Event::Type::POSITION), label(label), position(position) {}
    virtual ~PositionEvent() {}
    std::string label;
    ofPoint position;
  };

  class SpeedEvent : public Event {
  public:
    SpeedEvent(float speed) : Event(Event::Type::SPEED), speed(speed) {}
    virtual ~SpeedEvent() {}
    float speed;
  };

  Dialogue &Barrier(const std::string &barrier);

  Dialogue &Clear();

  Dialogue &Message(const std::string &message, const std::string &label);

  Dialogue &Pause(float duration);

  Dialogue &Position(const std::string &message, ofPoint position);

  Dialogue &Speed(float speed);

  void Trigger(const std::string &barrier);

  void Draw();

  bool IsDone() const;

  void Setup();

  void Update();

private:
  bool IsBlocked() const;

private:
  std::vector<Event *> events;
  float last_event_time, current_delay, speed;
  int event_index, message_index;
  std::map<std::string, ofPoint> positions;
  std::map<std::string, MessageEvent *> messages;
  std::string last_message_label;
  std::map<std::string, bool> barriers;
};

#endif  // TEXTTENNIS_DIALOGUE_H_
