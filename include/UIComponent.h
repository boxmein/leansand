#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <iostream>

#include <SDL2/SDL.h>

#include "UIRect.h"
#include "../3rd/LunaFive.cpp"


/**
  \brief A generic UI Component that will be accessible from Lua

  A UI component with a UIRect (controlling the position and texture), as well
  as a moveTo() and resize() function.
  \sa UIRect
*/
class UIComponent {
  private:
    UIRect uiRect;
  public:
    /**
      \brief Construct a new UIComponent.
      Construct a UIComponent with a preset position. This
      position can be changed later, of course, by the appropriate functions.
      \param ren the SDL_Renderer this component will be drawn into
      \param _x the X coordinate of the end location
      \param _y the Y coordinate of the end location
      \param _w the width of the texture
      \param _h the height of the texture
      \returns a UIComponent
      \sa moveTo(), resize()
    */
    UIComponent(SDL_Renderer* ren, int _x, int _y, int _w, int _h);
    UIComponent(lua_State *L);
    /**
      Free the texture associated with this component.
    */
    ~UIComponent();
    /**
      \brief Set the X and Y coordinates of this texture to _x and _y.
      \param _x the desired X coordinate
      \param _y the desired Y coordinate
    */
    void moveTo(int _x, int _y);
    int moveTo(lua_State *L);
    /**
      \brief Resize the inner texture.
      Resize the texture this component uses. This means recreating the texture,
      so avoid doing this a lot since it's hella expensive.
      \param ren the SDL Renderer used in the draw loop
      \param _w new width of the texture
      \param _h new height of the texture
    */
    void resize(SDL_Renderer* ren, int _w, int _h);
    int resize(lua_State *L);

    /**
      \brief return the UIRect to render
    */
    UIRect *getRect(/* fgt */);

    static const char className[];
    static const Luna<UIComponent>::PropertyType properties[];
    static const Luna<UIComponent>::FunctionType methods[];
};

#endif
