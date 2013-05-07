#include <algorithm>

#include "dialogue.h"

Dialogue::Dialogue()
: events(), last_event_time(), current_delay(), speed(1.0),
  event_index(), message_index(), positions(), messages(),
  last_message_label(), barriers(), background(0, 0, 0, 32), foreground(0, 0, 0, 255),
  click(), font_size(12.0), muted(false), punctuation_delay(0.75) {
  click.loadSound("type2.wav");
  click.setMultiPlay(true);
}

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

Dialogue &Dialogue::FontSize(float font_size) {
  events.push_back(new FontSizeEvent(font_size));
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

Dialogue &Dialogue::Mute() {
  events.push_back(new MuteEvent(true));
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

Dialogue &Dialogue::PunctuationDelay(float duration) {
  events.push_back(new PunctuationDelayEvent(duration));
  return *this;
}

void Dialogue::SetFontSize(float font_size) {
  this->font_size = font_size;
}

void Dialogue::SetPosition(const std::string &label, ofPoint position) {
  positions[label] = position;
}

Dialogue &Dialogue::Speed(float speed) {
  events.push_back(new SpeedEvent(speed));
  return *this;
}

Dialogue &Dialogue::Then(std::tr1::function<void()> then) {
  events.push_back(new ThenEvent(then));
  return *this;
}

void Dialogue::Trigger(const std::string &barrier) {
  barriers[barrier] = false;
}

Dialogue &Dialogue::Unmute() {
  events.push_back(new MuteEvent(false));
  return *this;
}

void Dialogue::Draw() {
  for (auto element : messages) {
    if (element.first != last_message_label) {
      if (positions.find(element.first) != positions.end()) {
        DrawString(element.second->message, positions[element.first]);
      }
    } else {
      if (positions.find(last_message_label) != positions.end()) {
        DrawString(element.second->message.substr(0, message_index), positions[element.first]);
      }
    }
  }
}

void Dialogue::DrawString(const std::string &message, ofPoint position) {
  ofDrawBitmapStringHighlight(message, position, background, foreground);
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
        if (!muted) {
          click.setSpeed(ofRandom(0.8, 1.2));
          click.setVolume(ofRandom(0.8, 1.0));
          click.setPan(-1.0 + 2.0 * positions[last_message_label].x / ofGetWidth());
          click.play();
        }
        message_index += 1;
        float delay = 0.0;
        char character = messages[last_message_label]->message[message_index];
        if (character == '.' || character == '!' || character == '?') {
          delay = punctuation_delay;
          message_index += 1;
        } else if (character == ',' || character == ';' || character == ':') {
          delay = punctuation_delay / 4.0;
          message_index += 1;
        }
        current_delay = 2.0 * ofRandomuf() / speed + delay;
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
            case Event::Type::FONT_SIZE: {
              FontSizeEvent *font_size_event = dynamic_cast<FontSizeEvent *>(event);
              SetFontSize(font_size_event->font_size);
              break;
            }
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
            case Event::Type::MUTE: {
              MuteEvent *mute = dynamic_cast<MuteEvent *>(event);
              muted = mute->muted;
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
            case Event::Type::PUNCTUATION_DELAY: {
              PunctuationDelayEvent *punctuation_delay_event =
                  dynamic_cast<PunctuationDelayEvent *>(event);
              punctuation_delay = punctuation_delay_event->duration;
              break;
            }
            case Event::Type::SPEED: {
              SpeedEvent *new_speed = dynamic_cast<SpeedEvent *>(event);
              speed = new_speed->speed;
              break;
            }
            case Event::Type::THEN: {
              ThenEvent *then_event = dynamic_cast<ThenEvent *>(event);
              then_event->then();
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

bool Dialogue::IsBlocked(const std::string &barrier) {
  if (barriers[barrier]) {
    return true;
  } else {
    return false;
  }
}
