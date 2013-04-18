#include "dialogue.h"

Dialogue::Dialogue()
: events(), last_event_time(), current_delay(), speed(1.0),
  last_messages(), event_index(), message_index() {}

Dialogue::~Dialogue() {
  for (auto *event : events) {
    delete event;
  }
  events.clear();
}

Dialogue &Dialogue::Clear() {
  events.push_back(new ClearEvent());
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

Dialogue &Dialogue::Pop() {
  events.push_back(new PopEvent());
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

void Dialogue::Draw() {
  if (last_messages.size()) {
    for (int i = 0; i < last_messages.size() - 1; ++i) {
      if (last_messages[i] && positions.find(last_messages[i]->label) != positions.end()) {
        ofSetColor(ofColor::black);
        ofDrawBitmapString(last_messages[i]->message, positions[last_messages[i]->label]);
      }
    }
    if (last_messages.back() && positions.find(last_messages.back()->label) != positions.end()) {
      ofSetColor(ofColor::black);
      ofDrawBitmapString(last_messages.back()->message.substr(0, message_index), positions[last_messages.back()->label]);
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
    if (last_messages.size() && message_index < last_messages.back()->message.size()) {
      message_index += 1;
      current_delay = 2.0 * ofRandomuf() / speed;
      last_event_time = ofGetElapsedTimef();
    } else {
      if (event_index < events.size()) {
        Event *event = events[event_index];
        current_delay = 0;
        switch (event->type) {
          case Event::Type::MESSAGE: {
            MessageEvent *message = dynamic_cast<MessageEvent *>(event);
            last_messages.push_back(message);
            message_index = 0;
            break;
          }
          case Event::Type::PAUSE: {
            PauseEvent *pause = dynamic_cast<PauseEvent *>(event);
            current_delay = pause->duration;
            break;
          }
          case Event::Type::POP:
            last_messages.pop_front();
            break;
          case Event::Type::POSITION: {
            PositionEvent *position_event = dynamic_cast<PositionEvent *>(event);
            positions[position_event->label] = position_event->position;
            break;
          }
          case Event::Type::CLEAR:
            last_messages.clear();
            break;
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
