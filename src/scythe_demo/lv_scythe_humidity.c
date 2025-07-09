#include <stdio.h>

#include "lv_scythe_humidity.h"
#include "lv_scythe.h"

// External variable from lv_scythe.c
extern lv_obj_t *g_hum_label;
lv_obj_t *humidity_buttons[3];

lv_obj_t* lv_humidity_create_buttons(lv_obj_t *parent, void (*event_cb)(lv_event_t *)) {
    lv_obj_t *btn_container = lv_obj_create(parent);
    lv_obj_remove_style_all(btn_container);
    lv_obj_set_size(btn_container, 200, 400);
    lv_obj_align(btn_container, LV_ALIGN_CENTER, 0, 10);
    lv_obj_set_style_pad_row(btn_container, 10, 0);

    lv_obj_set_flex_flow(btn_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(btn_container,
                         LV_FLEX_ALIGN_CENTER,
                         LV_FLEX_ALIGN_CENTER,
                         LV_FLEX_ALIGN_CENTER);

    static const char *humidity_levels[] = {"High", "Medium", "Low"};
    for (int i = 0; i < 3; i++) {
        lv_obj_t *btn = lv_btn_create(btn_container);
        lv_obj_remove_style_all(btn);
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x3B3B3B), 0);
        lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
        lv_obj_set_style_radius(btn, 50, 0);
        lv_obj_set_size(btn, 200, 100);

        lv_obj_t *b_label = lv_label_create(btn);
        lv_label_set_text(b_label, humidity_levels[i]);
        if (i == 2) {
            lv_obj_set_style_text_color(b_label, lv_color_hex(0x2196f3), 0);
        } else {
            lv_obj_set_style_text_color(b_label, lv_color_white(), 0);
        }
        lv_obj_center(b_label);

        lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, (void *)humidity_levels[i]);
        if (humidity_buttons) humidity_buttons[i] = b_label;
    }
    return btn_container;
}

void lv_humidity_set_label(const char *hum_str) {
    if (g_hum_label)
    {
        char buf[64];
        sprintf(buf, "Humidity: %s", hum_str);
        lv_label_set_text(g_hum_label, buf);
    }
}

void humidity_btn_event_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        const char *hum_str = (const char *)lv_event_get_user_data(e);

        for (int i = 0; i < 3; i++)
        {
            lv_obj_set_style_text_color(humidity_buttons[i], lv_color_white(), 0);
        }

        lv_obj_t *btn = lv_event_get_target(e);
        lv_obj_t *label = lv_obj_get_child(btn, 0);
        lv_obj_set_style_text_color(label, lv_color_hex(0x2196f3), 0);

        lv_humidity_set_label(hum_str);
    }
}
