#include <pebble.h>

static void (*bearing_changed)(int newBearing);

void compass_register_ui(void (*callback)(int newBearing)) {
  bearing_changed = callback;
}

void compass_handler(CompassHeadingData data) {
  static char s_buffer[32];

  switch(data.compass_status) {
    case CompassStatusCalibrating:
      APP_LOG(APP_LOG_LEVEL_INFO, "compass data calibrating");
      bearing_changed(TRIGANGLE_TO_DEG((int)data.true_heading));
      break;
    case CompassStatusCalibrated:
      APP_LOG(APP_LOG_LEVEL_INFO, "compass data calibrated");
      bearing_changed(TRIGANGLE_TO_DEG((int)data.true_heading));
      break;
    case CompassStatusDataInvalid:
    default:
      break;
  }
}