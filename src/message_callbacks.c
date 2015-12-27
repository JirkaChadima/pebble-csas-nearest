#include "main.h"

static void (*model_changed)(Place place);

void message_callbacks_register(void (*callback)(Place place)) {
  model_changed = callback;
}

void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success");
}

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  Place nearest;
  Tuple *no_data_tuple = dict_find(iterator, KEY_NOT_FOUND);
  Tuple *dist_tuple = dict_find(iterator, KEY_DISTANCE);
  Tuple *direction_tuple = dict_find(iterator, KEY_DIRECTION);
  Tuple *address_tuple = dict_find(iterator, KEY_ADDRESS);
  Tuple *access_tuple = dict_find(iterator, KEY_ACCESS_TYPE);

  if (no_data_tuple) {
    nearest.empty = true;
  } else {
    nearest.empty = false;
    if (dist_tuple) {
      nearest.distance = dist_tuple->value->int32;
    }
    if (direction_tuple) {
      nearest.direction = direction_tuple->value->int32;
    }
    if (address_tuple) {
      nearest.address = address_tuple->value->cstring;
    }
    if (access_tuple) {
      nearest.access = access_tuple->value->cstring;
    }
  }
  model_changed(nearest);
}
