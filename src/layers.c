#include <main.h>

TextLayer * createTimeLayer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 58, bounds.size.w, 50));
  text_layer_set_background_color(layer, GColorClear);
  text_layer_set_text_color(layer, GColorBlack);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_text(layer, "00:00");
  text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  return layer;
}

TextLayer * createWeatherLayer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 125, bounds.size.w, 25));
  text_layer_set_background_color(layer, GColorClear);
  text_layer_set_text_color(layer, GColorBlack);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_text(layer, "Loading...");
  return layer;
}