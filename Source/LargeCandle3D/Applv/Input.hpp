#pragma once

/*-------------------------------------------------------------------------
 *  Input.hpp
 *-----------------------------------------------------------------------*/

/*
 *  IKeyboardHandler
 */
class IKeyboardHandler 
{
  public:
    virtual ~IKeyboardHandler() {}

    virtual bool VOnKeyDown(int key) = 0;
    virtual bool VOnKeyUp(int key) = 0;
};

/*
 *  IMouseHandler
 */
class IMouseHandler 
{
  public:
    virtual ~IMouseHandler() {}

    virtual bool VOnMouseMove(float x, float y) = 0;
    virtual bool VOnMouseButtonDown(int button) = 0;
    virtual bool VOnMouseButtonUp(int button) = 0;
};