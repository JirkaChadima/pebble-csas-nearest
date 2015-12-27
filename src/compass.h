#include <pebble.h>

void compass_register_ui(void (*callback)(int new_direction));

void compass_handler(CompassHeadingData data);