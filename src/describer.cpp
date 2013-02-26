//
//  describer.cpp
//  texttennis
//
//  Created by Robert Dionne on 2/25/13.
//
//

#include <sstream>

#include "describer.h"
#include "texttennis.h"

Describer::Describer() {}

Describer::~Describer() {}

std::string Describer::Describe(const GameState &state) const {
  std::stringstream out;
  out << "The ball is in your ";
  if (state.balls.front().position.x > 0) {
    out << "opponent's ";
  }
  out << "side of the court. ";
  out << "The ball is moving ";
  if ((state.balls.front().position - state.balls.front().previous_position).dot(
      (state.balls.front().position - state.racket1)) < 0) {
    out << "towards you. ";
  } else {
    out << "away from you. ";
  }
  int index = 0;
  int bounces = 0;
  bool volley = false;
  for (auto i = state.trail.rbegin(); i != state.trail.rend(); ++i) {
    if (i->text == TextTennis::kMessageBounce) {
      ++bounces;
    } else if (i->text == TextTennis::kMessageVolley || i->text == TextTennis::kMessageWeakVolley
               || i->text == TextTennis::kMessageStrongVolley) {
      volley = true;
      break;
    }
  }
  if (bounces) {
    out << "The ball bounced " << bounces << " times";
    if (volley) {
      out << " since the last volley. ";
    } else {
      out << ". ";
    }
  }
  return out.str();
}
