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
static int watch_direction;
static int place_direction;

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

static void write_direction_to_ui() {
  if (!detail_window || !direction_layer || !watch_direction || !place_direction) {
    return;
  }
  int new_direction = ((place_direction - watch_direction) + 360) % 360;
  snprintf(direction_buffer, sizeof(direction_buffer), "%d", new_direction);
  text_layer_set_text(direction_layer, direction_buffer);
}

static void detail_window_set_place(Place place) {
  if (!detail_window) {
    detail_window = detail_window_init();
  }
  text_layer_set_text(address_layer, place.address);
  snprintf(distance_buffer, sizeof(distance_buffer), "%d m", place.distance);
  place_direction = place.direction;
  text_layer_set_text(distance_layer, distance_buffer);
  text_layer_set_text(hours_layer, place.hours);
  write_direction_to_ui();
}

void ui_model_changed_callback(Place place) {
  if(place.empty) {
    text_layer_set_text(splash_layer, "No ATM nearby");
  } else {
    window_stack_push(detail_window, true);
    detail_window_set_place(place);
  }
}

void ui_bearing_changed_callback(int new_direction) {
  watch_direction = new_direction;
  write_direction_to_ui();
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
