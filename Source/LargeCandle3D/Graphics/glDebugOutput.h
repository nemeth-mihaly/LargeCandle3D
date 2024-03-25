#pragma once

#include "LargeCandle3D/Vendor/glad/glad.h"

#include "LargeCandle3D/Core/PrimTypes.h"

extern void APIENTRY glDebugOutput(u32 source, u32 type, u32 ID, u32 severity, 
  i32 length, const char *pMessage, const void *pUserParam);