#ifndef UIRECT_H
#define UIRECT_H

/**
  \brief Data structure for an UI rectangle

  This class is a combination of a SDL_Texture* containing the necessary data
  and a SDL_Rect* which defines its location on the screen.
*/
struct UIRect {
  /** A texture containing the image data for the UI rectangle */
  SDL_Texture* texture;
  /** The UI rectangle's location on screen. NULL to cover the entire screen. */
  SDL_Rect*    location;
};

typedef struct UIRect UIRect;

#endif
