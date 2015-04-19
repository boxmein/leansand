#include "leansand.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
uint32_t* pixmap;

SDL_Event event;

LeanSandGame game;

#define FPS_TH 16
int lastFrames[FPS_TH];
int lastFramesPos = 0;

bool quitted = false;
unsigned int currTime;
unsigned int deltaTime;

int main (int argc, char** argv) {

  // Redirect stdout / stderr to files

  std::ofstream new_cerr("stderr.txt");
  std::streambuf* old_cerr = cerr.rdbuf();
  cerr.rdbuf(new_cerr.rdbuf());

  std::ofstream new_cout("stdout.txt");
  std::streambuf* old_cout = cout.rdbuf();
  cout.rdbuf(new_cout.rdbuf());

  // TODO: do things with command-line arguments

  cout << "leansand v" VERSION << "\n";

  // Display starting time

  {
    time_t    actualTime;
    struct tm time_struct;
    char      buf[40];
    time(&actualTime);
    time_struct =  *localtime(&actualTime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &time_struct);
    cout << "starting at " << buf << "\n";
  }

  // Startup SDL

  SDL_Init(SDL_INIT_VIDEO);
  currTime = SDL_GetTicks();

  window = SDL_CreateWindow("leansand v" VERSION,
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            WIDTH, HEIGHT,
                            SDL_WINDOW_OPENGL);

  if (window == NULL) {
    cerr << "Could not create a window: " << SDL_GetError() << endl;
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Configure renderer

  // These let us go fullscreen later on and still render at WIDTH x HEIGHT
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

  // Create our screen texture

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

  try {
    pixmap = new uint32_t[WIDTH * HEIGHT];
  } catch (exception& e) {
    cerr << "Could not allocate " << WIDTH * HEIGHT << " pixels, crashing...\n";
    cerr << e.what() << endl;

    cerr.flush();
    return EXIT_FAILURE;
  }

  // Begin game loop

  while (!quitted && game.isRunning()) {

    deltaTime = SDL_GetTicks() - currTime;

    if (!game.isPaused()) {
      game.update(currTime + deltaTime, deltaTime);
      game.draw(pixmap);

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      SDL_UpdateTexture(texture, NULL, pixmap, WIDTH * sizeof(uint32_t));
      SDL_RenderCopy(renderer, texture, NULL, NULL);
    }


    SDL_RenderPresent(renderer);


    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quitted = true;
          break;

        case SDL_KEYDOWN:
          game.onKeyDown( (SDL_KeyboardEvent*) &event );
          break;
      }
    }

    // Give the user 10 ms per tick to keep a nice 60 fps
    //SDL_Delay((1000/TARGET_FPS) - 10);

    currTime = SDL_GetTicks();
    lastFrames[lastFramesPos] = SDL_GetTicks();
    lastFramesPos = (lastFramesPos + 1) % FPS_TH;
    int totalDiff = 0, i;
    for(i = lastFramesPos; i < lastFramesPos + FPS_TH - 1; i++)
      totalDiff += lastFrames[(i + 1) % FPS_TH] - lastFrames[i % FPS_TH];
      printf("FPS: %.0f, Delta: %.3f\n",FPS_TH * 1000.0f / totalDiff, totalDiff / (float)FPS_TH);

  }

  // End game loop; the game is quitting gracefully.

  SDL_DestroyWindow(window);

  cout.flush();
  cerr.flush();

  // Reset redirected buffers

  cout.rdbuf(old_cout);
  cerr.rdbuf(old_cerr);

  // And done!
  SDL_Quit();
  return EXIT_SUCCESS;
}
