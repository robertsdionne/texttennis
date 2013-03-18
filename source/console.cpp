#include "console.h"
#include "ofMain.h"

Console::Console() : lines() {}

Console::~Console() {}

void Console::Draw() const {
  float y_coordinate = 0;
  for (auto &line : lines) {
    y_coordinate += kLineSpacing;
    ofDrawBitmapString(line, 0, y_coordinate);  }
}

void Console::Log(const std::string &line) {
  lines.push_back(line);
  if (lines.size() > kLineCount) {
    lines.pop_front();
  }
}
