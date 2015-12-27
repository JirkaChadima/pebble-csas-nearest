#include "main.h"

TextLayer * create_splash_layer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 74, bounds.size.w, 50));
  text_layer_set_background_color(layer, GColorWhite);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_text(layer, "Loading...");
  text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  return layer;
}