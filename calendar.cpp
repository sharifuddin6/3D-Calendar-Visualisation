#include "calendar.h"
#include <stdio.h>
#include <time.h>

Calendar::Calendar() { 
  // get datetime
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  printf("current datetime: %s\n", buf);

}
