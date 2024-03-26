#pragma once

#include <stdint.h>
#include "Vendor/glad/glad.h"

/*-------------------------------------------------------------------------
 *  DebugOutput.hpp
 *-----------------------------------------------------------------------*/

/*
 *  glDebugOutput
 */
extern void APIENTRY glDebugOutput(uint32_t source, uint32_t type, uint32_t ID, uint32_t severity, 
  int length, const char *pMessage, const void *pUserParam);