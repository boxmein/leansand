#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "leansand.h"

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
      \param renderer the SDL_Renderer this component will be drawn into
      \param _x the X coordinate of the end location
      \param _y the Y coordinate of the end location
      \param _w the width of the texture
      \param _h the height of the texture
      \returns a UIComponent
      \sa moveTo(), resize()
    */
    UIComponent(SDL_Renderer* renderer, int _x, int _y, int _w, int _h);
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
    /**
      \brief Resize the inner texture.
      Resize the texture this component uses. This means recreating the texture,
      so avoid doing this a lot since it's hella expensive.
      \param renderer the SDL Renderer used in the draw loop
      \param _w new width of the texture
      \param _h new height of the texture
    */
    void resize(SDL_Renderer* renderer, int _w, int _h);

    /**
      \brief return the UIRect to render
    */
    UIRect *getRect(/* fgt */);
};

#endif