#include "LC3/Applv/Application.h"

int main()
{  
  Application     app;
  
  if (app.Initialize())
    app.Run();

  app.Shutdown();

  return 0;
}