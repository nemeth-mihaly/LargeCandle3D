#include "LargeCandle3D/Graphics/glDebugOutput.h"

#include <stdio.h>

//
//  glDebugOutput()
//

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

extern void APIENTRY glDebugOutput(u32 source, u32 type, u32 ID, u32 severity, 
  i32 length, const char *pMessage, const void *pUserParam)
{
  // Ignore non-significant error/warning codes
  if(ID == 131169 
      || ID == 131185 
      || ID == 131218 
      || ID == 131204) 
    return; 

  printf("Debug Message: (%u): %s \n", ID, pMessage);

  switch (source)
  {
    case GL_DEBUG_SOURCE_API:             
      printf("  >> Source: API \n"); 
      break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      printf("  >> Source: Window System \n"); 
      break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      printf("  >> Source: Shader Compiler \n"); 
      break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:        
      printf("  >> Source: Third Party \n"); 
      break;

    case GL_DEBUG_SOURCE_APPLICATION:        
      printf("  >> Source: Application \n"); 
      break;

    case GL_DEBUG_SOURCE_OTHER:        
      printf("  >> Source: Other \n"); 
      break;
  }

  switch (type)
  {
    case GL_DEBUG_TYPE_ERROR:        
      printf("  >> Type: Error \n"); 
      break; 
    
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      printf("  >> Type: Deprecated Behaviour \n"); 
      break; 
    
    
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      printf("  >> Type: Undefined Behaviour \n"); 
      break; 
    
    case GL_DEBUG_TYPE_PORTABILITY:
      printf("  >> Type: Portability \n"); 
      break; 
    
    case GL_DEBUG_TYPE_PERFORMANCE:
      printf("  >> Type: Performance \n"); 
      break; 
    
    case GL_DEBUG_TYPE_MARKER:
      printf("  >> Type: Marker \n"); 
      break; 

    case GL_DEBUG_TYPE_PUSH_GROUP: 
      printf("  >> Type: Push Group \n"); 
      break; 
    
    case GL_DEBUG_TYPE_POP_GROUP:
      printf("  >> Type: Pop Group \n"); 
      break; 
    
    case GL_DEBUG_TYPE_OTHER:
      printf("  >> Type: Other \n"); 
      break; 
  }

  switch (severity)
  {
    case GL_DEBUG_SEVERITY_HIGH:
      printf("  >> Severity: High \n");
      break;

    case GL_DEBUG_SEVERITY_MEDIUM:
      printf("  >> Severity: Medium \n");
      break;
    
    case GL_DEBUG_SEVERITY_LOW:
      printf("  >> Severity: Low \n");
      break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
      printf("  >> Severity: Notification \n");
      break;
  }
}

#pragma GCC diagnostic pop