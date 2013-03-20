#include <Box2D/Box2D.h>

#include "constants.h"
#include "texttennis.h"

/**
 * Public method definitions.
 */
TextTennis::TextTennis() : scene() {}

void TextTennis::setup() {
  scene.Setup();
}

void TextTennis::update() {
  scene.Update();
}

void TextTennis::draw() {
  scene.Draw();
}
