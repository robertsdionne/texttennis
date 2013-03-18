#include <Box2D/Box2D.h>

#include "constants.h"
#include "texttennis.h"

/**
 * Public method definitions.
 */
TextTennis::TextTennis()
: model(), view(), controller(model) {}

void TextTennis::setup() {
  view.Setup();
  controller.Setup();
}

void TextTennis::update() {
  controller.Update();
}

void TextTennis::draw() {
  view.Draw(model);
}

void TextTennis::keyPressed(int key) {
  controller.OnKeyPressed(key);
}

void TextTennis::keyReleased(int key) {
  controller.OnKeyReleased(key);
}

void TextTennis::mouseMoved(int x, int y) {
  controller.OnMouseMoved(x, y);
}