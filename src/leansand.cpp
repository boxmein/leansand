#include "leansand.h"

int main (int argc, char** argv) {
  SDL_Window* window;

  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("leansand v" VERSION,
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            WIDTH, HEIGHT,
                            SDL_WINDOW_OPENGL);

  if (window == NULL) {
    cerr << "Could not create a window: " << SDL_GetError() << endl;
    return EXIT_FAILURE;
  }


  SDL_Delay(3000);

  SDL_DestroyWindow(window);

  SDL_Quit();
  return EXIT_SUCCESS;
}
