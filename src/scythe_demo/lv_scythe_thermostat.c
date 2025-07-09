#include "lv_scythe_thermostat.h"
#include "lv_scythe.h"

// External variable from lv_scythe.c
extern lv_obj_t *g_side_panel;
extern lv_obj_t *g_temp_label;

lv_obj_t* lv_scythe_create_thermostat_slider(lv_obj_t* parent) {
    lv_obj_t *slider = lv_slider_create(parent);
    lv_obj_remove_style_all(slider);
    lv_obj_set_size(slider, 140, 450);
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, 0);
    lv_slider_set_range(slider, 0, 30);
    lv_slider_set_value(slider, 13, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(slider, lv_color_hex(0x444444), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(slider, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(slider, 80, LV_PART_MAIN);
    lv_obj_set_style_bg_color(slider, lv_color_hex(0xFF0000), LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(slider, LV_OPA_COVER, LV_PART_INDICATOR);
    lv_obj_set_style_radius(slider, 10, LV_PART_INDICATOR);

    lv_obj_t *slider_val_label = lv_label_create(g_side_panel);
    lv_label_set_text_fmt(slider_val_label, "%d°C", 13);
    // lv_obj_set_style_text_font(slider_val_label, &lv_font_montserrat_28, 0); 
    lv_obj_set_style_text_color(slider_val_label, lv_color_white(), 0);           
    lv_obj_align(slider_val_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_user_data(slider, slider_val_label);

    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    return slider;
}

void lv_thermostat_slider_set_label(lv_obj_t *slider, int value) {
    lv_obj_t *slider_val_label = lv_obj_get_user_data(slider);
    if (slider_val_label) {
        lv_label_set_text_fmt(slider_val_label, "%d°C", value);
    }
    if (g_temp_label) {
        lv_label_set_text_fmt(g_temp_label, "Temperature: %d°C", value);
    }
}

void slider_event_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED)
    {
        lv_obj_t *slider = lv_event_get_target(e);
        int val = lv_slider_get_value(slider);
        lv_thermostat_slider_set_label(slider, val);
    }
}
