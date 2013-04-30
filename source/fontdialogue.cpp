#include "fontdialogue.h"

FontDialogue::FontDialogue() : Dialogue(), font() {
  font.loadFont("UbuntuMono-R.ttf", 32);
}

FontDialogue::~FontDialogue() {}

void FontDialogue::DrawString(const std::string &message, ofPoint position) {
  ofSetColor(foreground);
  font.drawString(message, position.x, position.y);
}
