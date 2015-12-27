#include "main.h"

TextLayer * create_splash_layer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 74, bounds.size.w, 50));
  text_layer_set_background_color(layer, GColorWhite);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_text(layer, "Loading...");
  text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  return layer;
}

TextLayer * create_address_layer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 72, bounds.size.w, 50));
  text_layer_set_background_color(layer, GColorWhite);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(layer, "...");
  return layer;
}

TextLayer * create_distance_layer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 120, bounds.size.w, 30));
  text_layer_set_background_color(layer, GColorWhite);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text(layer, "...");
  return layer;
}

TextLayer * create_direction_layer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 20, bounds.size.w, 20));
  text_layer_set_background_color(layer, GColorWhite);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_text(layer, "...");
  return layer;
}

TextLayer * create_hours_layer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 52, bounds.size.w, 20));
  text_layer_set_background_color(layer, GColorWhite);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_text(layer, "...");
  return layer;
}