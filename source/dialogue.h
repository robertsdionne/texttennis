#ifndef TEXTTENNIS_DIALOGUE_H_
#define TEXTTENNIS_DIALOGUE_H_

#include <deque>
#include <map>
#include <tr1/functional>
#include <vector>

#include "ofMain.h"

class Dialogue {
public:
  Dialogue();

  virtual ~Dialogue();

  class Event {
  public:
    enum class Type {
      BACKGROUND,
      BARRIER,
      CLEAR,
      FONT_SIZE,
      FOREGROUND,
      MESSAGE,
      MUTE,
      PAUSE,
      POSITION,
      SPEED,
      THEN
    };
    Event(Type type) : type(type) {}
    virtual ~Event() {}
    Type type;
  };

  class BackgroundEvent : public Event {
  public:
    BackgroundEvent(ofColor color) : Event(Event::Type::BACKGROUND), color(color) {}
    virtual ~BackgroundEvent() {}
    ofColor color;
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

  class FontSizeEvent : public Event {
  public:
    FontSizeEvent(float font_size) : Event(Event::Type::FONT_SIZE), font_size(font_size) {}
    virtual ~FontSizeEvent() {}
    float font_size;
  };

  class ForegroundEvent : public Event {
  public:
    ForegroundEvent(ofColor color) : Event(Event::Type::FOREGROUND), color(color) {}
    virtual ~ForegroundEvent() {}
    ofColor color;
  };

  class MessageEvent : public Event {
  public:
    MessageEvent(const std::string &message, const std::string &label)
    : Event(Event::Type::MESSAGE), message(message), label(label) {}
    virtual ~MessageEvent() {}
    std::string message;
    std::string label;
  };

  class MuteEvent : public Event {
  public:
    MuteEvent(bool muted) : Event(Event::Type::MUTE), muted(muted) {}
    virtual ~MuteEvent() {}
    bool muted;
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

  class ThenEvent : public Event {
  public:
    ThenEvent(std::tr1::function<void()> then) : Event(Event::Type::THEN), then(then) {}
    virtual ~ThenEvent() {}
    std::tr1::function<void()> then;
  };

  Dialogue &Background(ofColor color);

  Dialogue &Barrier(const std::string &barrier);

  Dialogue &Clear();

  Dialogue &FontSize(float font_size);

  Dialogue &Foreground(ofColor color);

  Dialogue &Message(const std::string &message, const std::string &label);

  Dialogue &Mute();

  Dialogue &Pause(float duration);

  Dialogue &Position(const std::string &label, ofPoint position);

  virtual void SetFontSize(float font_size);

  void SetPosition(const std::string &label, ofPoint position);

  Dialogue &Speed(float speed);

  Dialogue &Then(std::tr1::function<void()> then);

  void Trigger(const std::string &barrier);

  Dialogue &Unmute();

  void Draw();

  bool IsDone() const;

  void Setup();

  void Update();

  bool IsBlocked() const;

  bool IsBlocked(const std::string &barrier);

private:
  virtual void DrawString(const std::string &message, ofPoint position);

protected:
  std::vector<Event *> events;
  float last_event_time, current_delay, speed;
  int event_index, message_index;
  std::map<std::string, ofPoint> positions;
  std::map<std::string, MessageEvent *> messages;
  std::string last_message_label;
  std::map<std::string, bool> barriers;
  ofColor background, foreground;
  ofSoundPlayer click;
  float font_size;
  bool muted;
};

#endif  // TEXTTENNIS_DIALOGUE_H_
