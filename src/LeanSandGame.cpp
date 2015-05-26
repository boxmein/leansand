#include "LeanSandGame.h"
using namespace std;

unsigned int milliseconds = 0;
/**
  \brief Modifies the pixmap to set a pixel a color

  \param pixmap a 32-bit integer map of HEIGHT * WIDTH dimensions
                (like the one passed into LeanSandGame::draw() )
  \param x The x coordinate of the pixel
  \param y The y coordinate of the pixel
  \param rgba The RGBA8888 composed color integer
  \sa rgba()
*/
void setPixel(uint32_t* pixmap, int x, int y, int rgba) {
  pixmap[(y * WIDTH) + x] = rgba;
}

/**
  \brief Composes a RGBA8888 colour integer out of separate components.

  The RGBA8888 format uses four bytes to represent a red-green-blue-alpha color,
  which means that composition and decomposition is essential.

  \param r The red component (0..255)
  \param g The green component (0..255)
  \param b The blue component (0..255)
  \param a The transparency (0 = transparent, 255 = opaque)
*/
uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  return (r << 24) | (g << 16) | (b << 8) | a;
}

void LeanSandGame::draw(uint32_t* pixmap) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      setPixel(pixmap, x, y, rgba(x % 255, y % 255, milliseconds % 255, 255));
    }
  }
}

void LeanSandGame::update(unsigned int millis, unsigned int deltaTime) {
  milliseconds = millis;
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
