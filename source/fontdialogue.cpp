#include "fontdialogue.h"

FontDialogue::FontDialogue() : Dialogue(), font() {
  font.loadFont("UbuntuMono-R.ttf", font_size);
}

FontDialogue::~FontDialogue() {}

void FontDialogue::SetFontSize(float font_size) {
  this->font_size = font_size;
  font.loadFont("UbuntuMono-R.ttf", this->font_size);
}

void FontDialogue::DrawString(const std::string &message, ofPoint position) {
  ofSetColor(foreground);
  font.drawString(message, position.x, position.y);
}
