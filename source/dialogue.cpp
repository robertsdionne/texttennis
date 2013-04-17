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

Dialogue &Dialogue::AddClear() {
  events.push_back(new Clear());
  return *this;
}

Dialogue &Dialogue::AddMessage(const std::string &message, ofPoint position) {
  events.push_back(new Message(message, position));
  return *this;
}

Dialogue &Dialogue::AddPause(float duration) {
  events.push_back(new Pause(duration));
  return *this;
}

Dialogue &Dialogue::AddPop() {
  events.push_back(new Pop());
  return *this;
}

Dialogue &Dialogue::AddSpeed(float speed) {
  events.push_back(new Speed(speed));
  return *this;
}

void Dialogue::Draw() {
  if (last_messages.size()) {
    for (int i = 0; i < last_messages.size() - 1; ++i) {
      if (last_messages[i]) {
        ofSetColor(ofColor::black);
        ofDrawBitmapString(last_messages[i]->message, last_messages[i]->position);
      }
    }
    if (last_messages.back()) {
      ofSetColor(ofColor::black);
      ofDrawBitmapString(last_messages.back()->message.substr(0, message_index), last_messages.back()->position);
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
        if (event->type == Event::Type::MESSAGE) {
          Message *message = dynamic_cast<Message *>(event);
          last_messages.push_back(message);
          message_index = 0;
        } else if (event->type == Event::Type::PAUSE) {
          Pause *pause = dynamic_cast<Pause *>(event);
          current_delay = pause->duration;
        } else if (event->type == Event::Type::POP) {
          last_messages.pop_front();
        } else if (event->type == Event::Type::CLEAR) {
          last_messages.clear();
        } else {
          Speed *new_speed = dynamic_cast<Speed *>(event);
          speed = new_speed->speed;
        }
        event_index += 1;
        last_event_time = ofGetElapsedTimef();
      }
    }
  }
}
