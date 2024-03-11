#pragma once

#include "LargeCandle3D/Core/PrimTypes.h"

//-----------------------------------------------
//
//-----------------------------------------------

//
// Interface class IKeyboardHandler
//

class IKeyboardHandler 
{
  public:
    virtual ~IKeyboardHandler() {}

    virtual bool VOnKeyDown(i32 key) = 0;
    virtual bool VOnKeyUp(i32 key) = 0;
};

//
// Interface class IMouseHandler
//

class IMouseHandler 
{
  public:
    virtual ~IMouseHandler() {}

    virtual bool VOnMouseMove(f32 x, f32 y) = 0;
    virtual bool VOnMouseButtonDown(i32 button) = 0;
    virtual bool VOnMouseButtonUp(i32 button) = 0;
};