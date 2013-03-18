#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "texttennis.h"

int main() {
  ofAppGlutWindow window;
  window.setGlutDisplayString("rgba double depth alpha samples>=4");
  ofSetupOpenGL(&window, TextTennis::kWindowWidth, TextTennis::kWindowHeight, OF_WINDOW);
  ofRunApp(new TextTennis());
}
