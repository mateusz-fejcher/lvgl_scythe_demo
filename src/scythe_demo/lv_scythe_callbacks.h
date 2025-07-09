#ifndef LV_SCYTHE_CALLBACKS_H
#define LV_SCYTHE_CALLBACKS_H

#include "lvgl.h"

void tile_event_cb(lv_event_t *e);
void slider_event_cb(lv_event_t *e);
void humidity_btn_event_cb(lv_event_t *e);
void performance_btn_event_cb(lv_event_t *e);
void backFromPerformancePageEventCb(lv_event_t *e);

#endif // LV_SCYTHE_CALLBACKS_H
