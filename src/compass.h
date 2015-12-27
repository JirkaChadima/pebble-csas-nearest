#include <pebble.h>

void compass_register_ui(void (*callback)(int newBearing));

void compass_handler(CompassHeadingData data);