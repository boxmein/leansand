#include "UIComponent.h"

UIComponent::UIComponent(SDL_Renderer* renderer,
                         int _x, int _y, int _w, int _h) {
  this->moveTo(_x, _y);
  this->resize(renderer, _w, _h);
}

void UIComponent::moveTo(int _x, int _y) {
  uiRect.location.x = _x;
  uiRect.location.y = _y;
}

void UIComponent::resize(SDL_Renderer* renderer, int _w, int _h) {
  uiRect.location.w = _w;
  uiRect.location.h = _h;

  if (uiRect.texture != 0) {
    SDL_DestroyTexture(uiRect.texture);
  }

  uiRect.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_STREAMING, _w, _h);

  if (uiRect.texture == 0) {
    cerr << "new UI texture invalid - " << SDL_GetError();
  }
}

UIComponent::~UIComponent() {
  SDL_DestroyTexture(uiRect.texture);
}
