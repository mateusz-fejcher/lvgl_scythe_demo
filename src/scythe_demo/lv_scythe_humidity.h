#ifndef LV_SCYTHE_HUMIDITY_H
#define LV_SCYTHE_HUMIDITY_H

#include "lvgl.h"

void lv_humidity_set_label(const char *hum_str);
lv_obj_t* lv_humidity_create_buttons(lv_obj_t *parent, void (*event_cb)(lv_event_t *));
void humidity_btn_event_cb(lv_event_t *e);

#endif // LV_SCYTHE_HUMIDITY_H
