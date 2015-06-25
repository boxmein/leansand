#include "leansand.h"
using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

streambuf* old_cerr;
streambuf* old_cout;

uint32_t* pixmap;

SDL_Event event;

LeanSandGame game;
LuaAPIManager luaGlobal;

// Stores the current UI composition (eg stuff to render, plus locations)
// The first element gets rendered on the bottom, the last gets rendered on top
vector<UIRect> uiComp;

bool quitted = false;

int lastFPSReport;
int oldTime;
int currTime;
int deltaTime;

int cleanup() {
  // Display ending time

  {
    time_t    actualTime;
    struct tm time_struct;
    char      buf[40];
    time(&actualTime);
    time_struct =  *localtime(&actualTime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &time_struct);
    cout << "cleaning up at " << buf << "\n";
  }

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

int main(int argc, char** argv) {

  // Redirect stdout / stderr to files

  ofstream new_cerr("stderr.txt");
  old_cerr = cerr.rdbuf();
  cerr.rdbuf(new_cerr.rdbuf());

  ofstream new_cout("stdout.txt");
  old_cout = cout.rdbuf();
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

  UIRect pixmapRect;
  // Tell SDL that pixmapRect will cover everything
  pixmapRect.location = NULL;
  pixmapRect.texture  = texture;

  uiComp.push_back(pixmapRect);

  try {
    pixmap = new uint32_t[WIDTH * HEIGHT];
  } catch (exception& e) {
    cerr << "Could not allocate " << WIDTH * HEIGHT << " pixels, crashing...\n";
    cerr << e.what() << endl;

    cerr.flush();
    return EXIT_FAILURE;
  }

  // Start running our script
  luaGlobal.runFile("autorun.lua");

  // report composition length
  cout << "UI composition is of length: " << uiComp.size() << "\n";

  // Begin game loop

  lastFPSReport = SDL_GetTicks();

  while (!quitted && game.isRunning()) {

    oldTime = currTime;
    currTime = SDL_GetTicks();

    deltaTime = currTime - oldTime;

    if (!game.isPaused()) {
      game.update(currTime + deltaTime, deltaTime);
      game.draw(pixmap);

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      SDL_UpdateTexture(texture, NULL, pixmap, WIDTH * sizeof(uint32_t));

      // TODO: Call update functions for other UI components

      for (vector<UIRect>::iterator it = uiComp.begin(); it != uiComp.end(); ++it) {
        SDL_RenderCopy(renderer, it->texture, NULL, it->location);
      }
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

    // Keep the delta time at around 16 ms at the fastest
    if (deltaTime < 16) {
      SDL_Delay(16 - deltaTime);
    }

    if (currTime - lastFPSReport >= 1000) {
      cout << "FPS: " << 1000/deltaTime << "\n";
      lastFPSReport = currTime;
    }
  }

  // End game loop; the game is quitting gracefully.

  return cleanup();
}

LUAAPI void luatest(const char* text) {
  cout << "it works: " << text << "\n";
}
