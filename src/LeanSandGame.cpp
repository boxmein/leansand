#include "leansand.h"

void LeanSandGame::draw(uint32_t* pixmap) {

}

void LeanSandGame::update(unsigned int millis, unsigned int deltaTime) {

}

void LeanSandGame::onKeyDown(SDL_KeyboardEvent* keyboardEvent) {
  SDL_Keysym key = keyboardEvent->keysym;

  switch (key.scancode) {
    case SDL_SCANCODE_SPACE:
      paused = !paused;
      break;
    case SDL_SCANCODE_ESCAPE:
      cout << "escape pressed, exiting game...\n";
      running = !running;
      break;
  }
}

bool LeanSandGame::isRunning() {
  return running;
}

bool LeanSandGame::isPaused() {
  return paused;
}

LeanSandGame::LeanSandGame() {
  running = true;
  paused = false;
}

LeanSandGame::~LeanSandGame() {

}
