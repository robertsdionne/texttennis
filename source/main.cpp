#include "constants.h"
#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "texttennis.h"

int main() {
  ofAppGlutWindow window;
  window.setGlutDisplayString("rgba double depth alpha samples>=4");
  ofSetupOpenGL(&window, param_window_width, param_window_height, OF_WINDOW);
  ofRunApp(new TextTennis());
}
