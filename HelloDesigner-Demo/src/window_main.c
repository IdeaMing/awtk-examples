#include "awtk.h"
extern ret_t application_init(void);
static void init_children_widget(widget_t* widget);

static ret_t on_basic_click(void* ctx, event_t* e) {
  (void)ctx;
  (void)e;

  open_basic_window();

  return RET_OK;
}

static ret_t on_animation_click(void* ctx, event_t* e) {
  (void)ctx;
  (void)e;

  open_animation_window();

  return RET_OK;
}

/**
 * 子控件初始化(主要是设置click回调、初始显示信息)
 */
static ret_t init_widget(void* ctx, const void* iter) {
  widget_t* widget = WIDGET(iter);
  widget_t* win = widget_get_window(widget);
  (void)ctx;

  if (widget->name != NULL) {
    const char* name = widget->name;

    if (strstr(name, "basic") != NULL) {
      widget_on(widget, EVT_CLICK, on_basic_click, win);
    } else if (strstr(name, "animation") != NULL) {
      widget_on(widget, EVT_CLICK, on_animation_click, win);
    }
  }

  return RET_OK;
}

/**
 * 初始化窗口上的子控件
 */
static void init_children_widget(widget_t* widget) {
  widget_foreach(widget, init_widget, widget);
}

/**
 * 初始化
 */
ret_t application_init() {
  widget_t* system_bar = window_open("system_bar/system_bar");
  widget_t* system_bar_b = window_open("system_bar_b/system_bar_b");
  widget_t* win = window_open("home_page/home_page");

  if (win) {
    init_children_widget(win);
  }

  return RET_OK;
}