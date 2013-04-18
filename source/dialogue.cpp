#include <algorithm>

#include "dialogue.h"

Dialogue::Dialogue()
: events(), last_event_time(), current_delay(), speed(1.0),
  event_index(), message_index(), positions(), messages(),
  last_message_label(), barriers(), background(0, 0, 0, 0), foreground(0, 0, 0, 255) {}

Dialogue::~Dialogue() {
  for (auto *event : events) {
    delete event;
  }
  events.clear();
}

Dialogue &Dialogue::Background(ofColor color) {
  events.push_back(new BackgroundEvent(color));
  return *this;
}

Dialogue &Dialogue::Barrier(const std::string &barrier) {
  events.push_back(new BarrierEvent(barrier));
  return *this;
}

Dialogue &Dialogue::Clear() {
  events.push_back(new ClearEvent());
  return *this;
}

Dialogue &Dialogue::Foreground(ofColor color) {
  events.push_back(new ForegroundEvent(color));
  return *this;
}

Dialogue &Dialogue::Message(const std::string &message, const std::string &label) {
  events.push_back(new MessageEvent(message, label));
  return *this;
}

Dialogue &Dialogue::Pause(float duration) {
  events.push_back(new PauseEvent(duration));
  return *this;
}

Dialogue &Dialogue::Position(const std::string &label, ofPoint position) {
  events.push_back(new PositionEvent(label, position));
  return *this;
}

Dialogue &Dialogue::Speed(float speed) {
  events.push_back(new SpeedEvent(speed));
  return *this;
}

void Dialogue::Trigger(const std::string &barrier) {
  barriers[barrier] = false;
}

void Dialogue::Draw() {
  for (auto element : messages) {
    if (element.first != last_message_label) {
      if (positions.find(element.first) != positions.end()) {
        ofSetColor(ofColor::black);
        ofDrawBitmapStringHighlight(element.second->message,
                                    positions[element.first], background, foreground);
      }
    } else {
      if (positions.find(last_message_label) != positions.end()) {
        ofSetColor(ofColor::black);
        ofDrawBitmapStringHighlight(element.second->message.substr(0, message_index),
                                    positions[element.first], background, foreground);
      }
    }
  }
}

bool Dialogue::IsDone() const {
  return event_index == events.size();
}

void Dialogue::Setup() {
  last_event_time = ofGetElapsedTimef();
  event_index = 0;
  message_index = 0;
}


void Dialogue::Update() {
  if (ofGetElapsedTimef() > last_event_time + current_delay) {
    if (!IsBlocked()) {
      if (messages.size() && message_index < messages[last_message_label]->message.size()) {
        message_index += 1;
        current_delay = 2.0 * ofRandomuf() / speed;
        last_event_time = ofGetElapsedTimef();
      } else {
        if (event_index < events.size()) {
          Event *event = events[event_index];
          current_delay = 0;
          switch (event->type) {
            case Event::Type::BACKGROUND: {
              BackgroundEvent *background_event = dynamic_cast<BackgroundEvent *>(event);
              background = background_event->color;
              break;
            }
            case Event::Type::BARRIER: {
              BarrierEvent *barrier = dynamic_cast<BarrierEvent *>(event);
              barriers[barrier->barrier] = true;
              break;
            }
            case Event::Type::CLEAR:
              messages.clear();
              break;
            case Event::Type::FOREGROUND: {
              ForegroundEvent *foreground_event = dynamic_cast<ForegroundEvent *>(event);
              foreground = foreground_event->color;
              break;
            }
            case Event::Type::MESSAGE: {
              MessageEvent *message = dynamic_cast<MessageEvent *>(event);
              messages[message->label] = message;
              last_message_label = message->label;
              message_index = 0;
              break;
            }
            case Event::Type::PAUSE: {
              PauseEvent *pause = dynamic_cast<PauseEvent *>(event);
              current_delay = pause->duration;
              break;
            }
            case Event::Type::POSITION: {
              PositionEvent *position_event = dynamic_cast<PositionEvent *>(event);
              positions[position_event->label] = position_event->position;
              break;
            }
            case Event::Type::SPEED: {
              SpeedEvent *new_speed = dynamic_cast<SpeedEvent *>(event);
              speed = new_speed->speed;
              break;
            }
            default:
              break;
          }
          event_index += 1;
          last_event_time = ofGetElapsedTimef();
        }
      }
    }
  }
}

bool Dialogue::IsBlocked() const {
  for (auto entry : barriers) {
    if (entry.second) {
      return true;
    }
  }
  return false;
}
