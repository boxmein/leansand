#include "UIComponent.h"
using namespace std;

UIComponent::UIComponent(SDL_Renderer* ren,
                         int _x, int _y, int _w, int _h) {
  this->moveTo(_x, _y);
  this->resize(ren, _w, _h);
}
UIComponent::UIComponent(lua_State *L) {
  cout << "in constructor\n";
}

void UIComponent::moveTo(int _x, int _y) {
  uiRect.location->x = _x;
  uiRect.location->y = _y;
}
int UIComponent::moveTo(lua_State *L) {
  cout << "in moveTo\n";
  return 0;
}

void UIComponent::resize(SDL_Renderer* ren, int _w, int _h) {
  uiRect.location->w = _w;
  uiRect.location->h = _h;

  if (uiRect.texture != 0) {
    SDL_DestroyTexture(uiRect.texture);
  }

  uiRect.texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_STREAMING, _w, _h);

  if (uiRect.texture == 0) {
    cerr << "new UI texture invalid - " << SDL_GetError();
  }
}
int UIComponent::resize(lua_State *L) {
  cout << "in resize\n";
  return 0;
}

UIComponent::~UIComponent() {
  SDL_DestroyTexture(uiRect.texture);
}


const char UIComponent::className[] = "UIComponent";
const Luna<UIComponent>::PropertyType UIComponent::properties[] = {
  {0, 0}
};
const Luna<UIComponent>::FunctionType UIComponent::methods[] = {
  {"moveTo", &UIComponent::moveTo},
  {"resize", &UIComponent::resize},
  {0, 0}
};
