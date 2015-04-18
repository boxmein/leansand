#include "leansand.h"

int main (int argc, char** argv) {
  SDL_Window* window;

  std::ofstream new_cerr("stderr.txt");
  std::streambuf* old_cerr = cerr.rdbuf();
  cerr.rdbuf(new_cerr.rdbuf());

  std::ofstream new_cout("stdout.txt");
  std::streambuf* old_cout = cout.rdbuf();
  cout.rdbuf(new_cout.rdbuf());

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


  cout.flush();
  cerr.flush();

  cout.rdbuf(old_cout);
  cerr.rdbuf(old_cerr);

  SDL_Quit();
  return EXIT_SUCCESS;
}
