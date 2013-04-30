#ifndef TEXTTENNIS_FONTDIALOGUE_H_
#define TEXTTENNIS_FONTDIALOGUE_H_

#include "dialogue.h"
#include "ofMain.h"

class FontDialogue : public Dialogue {
public:
  FontDialogue();

  virtual ~FontDialogue();

  virtual void SetFontSize(float font_size);

private:
  virtual void DrawString(const std::string &message, ofPoint position);

private:
  ofTrueTypeFont font;
};

#endif  // TEXTTENNIS_FONTDIALOGUE_H_
