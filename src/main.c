#include "main.h"
#include "ui.h"
#include "compass.h"
#include "message_callbacks.h"

static void init(void) {
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  compass_service_subscribe(compass_handler);
  compass_service_set_heading_filter(TRIG_MAX_ANGLE / 36);

  ui_init();
  message_callbacks_register_ui(ui_model_changed_callback);
}

static void deinit() {
  ui_destroy();
}

int main() {
  init();
  app_event_loop();
  deinit();
}