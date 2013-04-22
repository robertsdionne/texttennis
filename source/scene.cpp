#include "constants.h"
#include "scene.h"

ofImage Scene::DrawImage() {
  fbo.allocate(window_width, window_height);
  fbo.begin();
  Draw();
  fbo.end();
  ofImage image;
  image.allocate(window_width, window_height, ofImageType::OF_IMAGE_COLOR_ALPHA);
  fbo.readToPixels(image.getPixelsRef());
  image.reloadTexture();
  return image;
}
