#ifndef Graphics_h
#define Graphics_h

#include "Arduino.h"

class Graphics
{
  public:
    Graphics();
    String ExGraph(int func,String request);
    String _ret;
    
};

#endif
