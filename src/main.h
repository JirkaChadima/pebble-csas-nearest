#include <pebble.h>

#define KEY_DISTANCE 0
#define KEY_DIRECTION 1
#define KEY_ADDRESS 2
#define KEY_ACCESS_TYPE 3
#define KEY_NOT_FOUND 4

#ifndef MAIN_DEFINED
#define MAIN_DEFINED

typedef struct Arrow {
  int direction;
} Arrow;

typedef struct Place {
  bool empty;
  int distance;
  int direction;
  char * address;
  char * hours;
} Place;

#endif