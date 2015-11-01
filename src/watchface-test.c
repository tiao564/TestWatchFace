#include <pebble.h>

//Global pointers
static Window *s_main_window;
static TextLayer *s_time_layer;

static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

static GFont s_time_font;
  
static void main_window_load(Window *window);

static void main_window_unload(Window *window); 

static void init();

static void deinit();

static void tick_handler(struct tm *tick_time, TimeUnits units_changed);

static void update_time();
////////
//Main//
////////
int main(void){
  init();
  app_event_loop(); //Lets watch face wait for system events until exit.
  deinit();
}



//////////////
//Functions //
//////////////
  //////////////
  //Initiation//
  //////////////
static void init(){
  //Create main window element and assign to pointer
  s_main_window = window_create();

  window_set_background_color(s_main_window, GColorBlack);
  //Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window,
    (WindowHandlers){
    .load = main_window_load,
    .unload = main_window_unload
    }    
    );

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  //Show the window on the watch, with animated=true
  window_stack_push(s_main_window, true);
}

static void deinit(){
  // Destroy Window
  window_destroy(s_main_window);
}

  ///////////////////
  //Window handlers//
  ///////////////////
static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  
  
  ////////////
  //Creation//
  ////////////
  
  // Create the TextLayer with specific bounds
  s_time_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));
  
    // Create GBitmap
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);

  // Create BitmapLayer to display the GBitmap
  s_background_layer = bitmap_layer_create(bounds);

  // Set the bitmap onto the layer and add to the window
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
  
  
  // Set font to custom font
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_48));
  
  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  //text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_font(s_time_layer, s_time_font); //See line 64
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

static void main_window_unload(Window *window){
  text_layer_destroy(s_time_layer);
  fonts_unload_custom_font(s_time_font);
  gbitmap_destroy(s_background_bitmap);
  //gbitmap_layer_destroy(s_background_layer);
  
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  update_time();
}

static void update_time(){
  //Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  //Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
          "%H:%M" : "%I:%M", tick_time);
  
  //Display this time on the TextLayer
  text_layer_set_text(s_time_layer, s_buffer);
}