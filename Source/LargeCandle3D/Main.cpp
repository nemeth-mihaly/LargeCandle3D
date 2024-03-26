#include "LargeCandle3D/Applv/Application.hpp"

int main()
{  
  Application app;
  
  if (app.Initialize(1280, 720, "LargeCandle3D"))
  {
    app.Run();
  }

  app.Shutdown();

  return 0;
}