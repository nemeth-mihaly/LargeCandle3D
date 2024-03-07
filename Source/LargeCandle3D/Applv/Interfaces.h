#pragma once

#include "LargeCandle3D/Core/PrimTypes.h"

class IKeyboardHandler 
{
  public:
    virtual ~IKeyboardHandler() {}
    virtual bool VOnKeyDown(i32 keyCode) = 0;
    virtual bool VOnKeyUp(i32 keyCode) = 0;
};

class IMouseHandler 
{
  public:
    virtual ~IMouseHandler() {}
    virtual bool VOnMouseMove(f32 x, f32 y) = 0;
    virtual bool VOnMouseButtonDown(i32 buttonCode) = 0;
    virtual bool VOnMouseButtonUp(i32 buttonCode) = 0;
};