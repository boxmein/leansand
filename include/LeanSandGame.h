#ifndef LEANSANDGAME_H
#define LEANSANDGAME_H

/**
  \brief A class containing game state and draw/update methods.

  This class contains two important methods, draw() and update(), which directly
  draw onto a SDL_Window. Other than that, it provides a few functions for
  paused / running state.

*/
class LeanSandGame {
  public:

    /**
      \brief Has the game not been quitted yet?

      This function returns whether or not the game is still running. When the
      instance stops returning true for this, the game quits gracefully.
      \return Whether or not the game has been quitted yet
    */
    bool isRunning();

    /**
      \brief Is the game currently paused?

      This function returns whether the game is currently paused. While the game
      is paused, no screen refreshes and game updates are performed.
      \return Whether or not the game is paused
    */
    bool isPaused();

    /**
      \brief Draws the current frame into the pixel map

      This function draws the current frame into the pixel map, but does not
      update the game state. This is done in another function.

      \param texture The pixel map to draw into (RGBA8888 format)
                     (index it by texture[y * WIDTH + x])
      \sa update()
    */
    void draw(uint32_t* texture);

    /**
      \brief Updates the game state

      This function performs any changes needed to display the next frame in the
      draw() call. This includes game object ticks as well as anything else
      necessary.

      \param currTime Milliseconds since the game was launched
      \param deltaTime Milliseconds since the last game tick
    */
    void update(unsigned int currTime, unsigned int deltaTime);

    /**
      \brief Handles key-down events

      \param keyEvent the key-down event that occurred
    */
    void onKeyDown(SDL_KeyboardEvent* keyEvent);

    LeanSandGame();
    ~LeanSandGame();

  private:
    /**
      \brief Whether or not the game is "running" currently.
      \sa isRunning()
    */
    bool running;
    /**
      \brief Whether or not the game is paused.
      \sa isPaused()
    */
    bool paused;
};

#endif
