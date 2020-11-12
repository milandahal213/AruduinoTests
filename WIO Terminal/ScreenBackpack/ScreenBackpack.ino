
#include "Graphwio.h"

Graphwio test(115200);
  
void setup() {

test.start();

}

void loop() {
 test.read_from_SPIKE();

 
 }
 
