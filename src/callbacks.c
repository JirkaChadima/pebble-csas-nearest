#include <main.h>

static char temperature_buffer[8];
static char conditions_buffer[32];
static char weather_layer_buffer[32];

static TextLayer *s_weather_layer;

void init_callbacks(TextLayer *layer) {
  s_weather_layer = layer;
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
  Tuple *temp_tuple = dict_find(iterator, KEY_TEMPERATURE);
  Tuple *cond_tuple = dict_find(iterator, KEY_CONDITIONS);

  if (temp_tuple && cond_tuple) {
    snprintf(temperature_buffer, sizeof(temperature_buffer), "%dC", (int)temp_tuple->value->int32);
    snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", cond_tuple->value->cstring);
    snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", temperature_buffer, conditions_buffer);
    text_layer_set_text(s_weather_layer, weather_layer_buffer);
  }
}