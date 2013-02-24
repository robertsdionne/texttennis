#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "texttennis.h"

constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;

int main() {
  ofAppGlutWindow window;
  ofSetupOpenGL(&window, kWindowWidth, kWindowHeight, OF_WINDOW);
  ofRunApp(new TextTennis());
}
