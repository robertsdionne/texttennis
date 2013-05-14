#include "constants.h"
#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "texttennis.h"

int main() {
  ofAppGlutWindow window;
  window.setGlutDisplayString("rgba double depth alpha samples>=4");
  ofSetupOpenGL(&window, window_width, window_height, OF_FULLSCREEN);
  ofRunApp(new TextTennis());
}
