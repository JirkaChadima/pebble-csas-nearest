#include "main.h"
#include "layers.h"

static Window * main_window;
static TextLayer * splash_layer;

static Window * detail_window;
static TextLayer * address_layer;
static TextLayer * distance_layer;
static TextLayer * direction_layer;
static TextLayer * hours_layer;

static char distance_buffer[8];
static char direction_buffer[8];

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  splash_layer = create_splash_layer(bounds);
  layer_add_child(window_layer, text_layer_get_layer(splash_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(splash_layer);
}

static Window * main_window_init() {
  Window * window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  return window;
}

static void detail_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  address_layer = create_address_layer(bounds);
  distance_layer = create_distance_layer(bounds);
  direction_layer = create_direction_layer(bounds);
  hours_layer = create_hours_layer(bounds);
  layer_add_child(window_layer, text_layer_get_layer(address_layer));
  layer_add_child(window_layer, text_layer_get_layer(distance_layer));
  layer_add_child(window_layer, text_layer_get_layer(hours_layer));
  layer_add_child(window_layer, text_layer_get_layer(direction_layer));
}

static void detail_window_unload(Window *window) {
  text_layer_destroy(address_layer);
  text_layer_destroy(distance_layer);
  text_layer_destroy(direction_layer);
  text_layer_destroy(hours_layer);
}

static Window * detail_window_init() {
  Window * window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = detail_window_load,
    .unload = detail_window_unload
  });
  return window;
}

static void detail_window_set_place(Place place) {
  if (!detail_window) {
    detail_window = detail_window_init();
  }
  text_layer_set_text(address_layer, place.address);
  snprintf(distance_buffer, sizeof(distance_buffer), "%d m", place.distance);
  text_layer_set_text(distance_layer, distance_buffer);
  snprintf(direction_buffer, sizeof(direction_buffer), "%d", place.direction);
  text_layer_set_text(direction_layer, direction_buffer);
  text_layer_set_text(hours_layer, place.hours);
}

void ui_model_changed_callback(Place place) {
  if(place.empty) {
    text_layer_set_text(splash_layer, "No ATM nearby");
  } else {
    window_stack_push(detail_window, true);
    detail_window_set_place(place);
  }
}

void ui_init() {
  main_window = main_window_init();
  detail_window = detail_window_init();
  window_stack_push(main_window, true);
}

void ui_destroy() {
  window_destroy(main_window);
  window_destroy(detail_window);
}
