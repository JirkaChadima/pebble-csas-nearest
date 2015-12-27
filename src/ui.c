#include "main.h"
#include "layers.h"

static Window * window;
static TextLayer * splash_layer;

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  splash_layer = create_splash_layer(bounds);
  layer_add_child(window_layer, text_layer_get_layer(splash_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(splash_layer);
}

Window * loading_window_init() {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  return window;
}

void ui_model_changed_callback(Place place) {
  if(place.empty) {
    text_layer_set_text(splash_layer, "No ATM nearby");
  } else {
    APP_LOG(APP_LOG_LEVEL_INFO, "callback called");
  }
}

void ui_init() {
  window = loading_window_init();
  window_stack_push(window, true);
}

void ui_destroy() {
  window_destroy(window);
}
