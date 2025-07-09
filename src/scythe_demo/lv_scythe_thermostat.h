#ifndef LV_SCYTHE_THERMOSTAT_H
#define LV_SCYTHE_THERMOSTAT_H

#include "lvgl.h"

lv_obj_t* lv_scythe_create_thermostat_slider(lv_obj_t* parent);
void slider_event_cb(lv_event_t *e);
void lv_thermostat_slider_set_label(lv_obj_t *slider, int value);

#endif // LV_SCYTHE_THERMOSTAT_H
