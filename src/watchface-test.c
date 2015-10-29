#include <pebble.h>

//Global pointers
static Window *s_main_window;   //Static means only for within this file
static TextLayer *s_text_layer;

static void main_window_load(Window *window);

static void main_window_unload(Window *window); 

static void init();

static void deinit();

int main(void){
  init();
  app_event_loop(); //Lets watch face wait for system events until exit.
  deinit();
}



//////////////
//Functions //
/////////////
static void init(){
  //Create main window element and assign to pointer
  s_main_window = window_create();

  //Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window,
    (WindowHandlers){
    .load = main_window_load,
    .unload = main_window_unload
    }    
    );

  //Show the window on the watch, with animated=true
  window_stack_push(s_main_window, true);
}

static void deinit(){
  // Destroy Window
  window_destroy(s_main_window);
}

static void main_window_load(Window *window){

}

static void main_window_unload(Window *window){

}
