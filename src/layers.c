#include "main.h"

static GPath *arrow_path = NULL;
static const GPathInfo ARROW_PATH_INFO = {
  .num_points = 7,
  .points = (GPoint []) {
    {-5, -12}, {5, -12}, {5, 0}, {10, 0}, {0, 12}, {-10, 0}, {-5, 0}
  }
};

TextLayer * create_address_layer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 72, bounds.size.w, 50));
  text_layer_set_background_color(layer, GColorWhite);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(layer, "Loading...");
  return layer;
}

TextLayer * create_distance_layer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 130, bounds.size.w, 30));
  text_layer_set_background_color(layer, GColorWhite);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text(layer, "");
  return layer;
}

static void redraw_direction_arrow(Layer *layer, GContext *ctx) {
  Arrow* arrow = (Arrow*) layer_get_data(layer);
  if (!arrow->direction) {
    return;
  }
  gpath_rotate_to(arrow_path, TRIG_MAX_ANGLE / 360 * arrow->direction);

  graphics_context_set_fill_color(ctx, GColorBlack);
  gpath_draw_filled(ctx, arrow_path);
}

Layer * create_direction_layer(GRect bounds) {
  Layer *layer = layer_create_with_data(GRect(0, 20, bounds.size.w, 30), sizeof(Arrow));
  layer_set_update_proc(layer, redraw_direction_arrow);
  arrow_path = gpath_create(&ARROW_PATH_INFO);
  GRect layer_bounds = layer_get_bounds(layer);
  gpath_move_to(arrow_path, grect_center_point(&layer_bounds));
  return layer;
}

TextLayer * create_hours_layer(GRect bounds) {
  TextLayer *layer = text_layer_create(GRect(0, 52, bounds.size.w, 20));
  text_layer_set_background_color(layer, GColorWhite);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  text_layer_set_text(layer, "");
  return layer;
}