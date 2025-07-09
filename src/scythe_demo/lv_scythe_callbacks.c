#include "lv_scythe.h"
#include "lv_scythe_air.h"
#include "lv_scythe_callbacks.h"
#include "lv_scythe_humidity.h"
#include "lv_scythe_performance_page.h"
#include "lv_scythe_thermostat.h"
#include "lv_scythe_main_page.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// External variables from lv_scythe.c
extern lv_obj_t *g_side_panel;
extern lv_obj_t *g_temp_label;
extern lv_obj_t *g_hum_label;
extern lv_obj_t *g_all_buttons[4];

void tile_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *tile = lv_event_get_target(e);

    if (code == LV_EVENT_CLICKED)
    {
        int index = (int)(uintptr_t)lv_event_get_user_data(e);

        for (int i = 0; i < 4; i++)
        {
            lv_obj_set_style_border_width(g_all_buttons[i], 0, 0);
        }

        lv_obj_set_style_border_width(tile, 4, 0);
        lv_obj_set_style_border_color(tile, lv_color_hex(0xFFAA00), 0);
        lv_obj_set_style_border_opa(tile, LV_OPA_COVER, 0);

        lv_obj_clean(g_side_panel);

        if (index == 0)
        {
            /* Create the temperature slider */
            lv_obj_t *slider = lv_scythe_create_thermostat_slider(g_side_panel);
        }
        if (index == 1)
        {
            lv_humidity_create_buttons(g_side_panel, humidity_btn_event_cb);
        }
        else if (index == 2)
        {
            lv_obj_t *out_container = lv_obj_create(g_side_panel);
            lv_obj_remove_style_all(out_container);
            lv_obj_set_size(out_container, 250, 445);
            lv_obj_align(out_container, LV_ALIGN_CENTER, 0, 0);
            lv_obj_set_scroll_dir(out_container, LV_DIR_HOR | LV_DIR_VER);
            lv_obj_set_scrollbar_mode(out_container, LV_SCROLLBAR_MODE_AUTO);

            lv_obj_set_layout(out_container, LV_LAYOUT_FLEX);
            lv_obj_set_flex_flow(out_container, LV_FLEX_FLOW_ROW_WRAP);
            lv_obj_set_style_pad_gap(out_container, 10, 0);

            for (int i = 0; i < 21; i++)
            {
                int usage = (rand() % 86) + 5;

                lv_obj_t *outlet_tile = lv_obj_create(out_container);
                lv_obj_remove_style_all(outlet_tile);
                lv_obj_set_style_bg_color(outlet_tile, lv_color_hex(0x3B3B3B), 0);
                lv_obj_set_style_bg_opa(outlet_tile, LV_OPA_COVER, 0);
                lv_obj_set_style_radius(outlet_tile, 8, 0);
                lv_obj_set_size(outlet_tile, 76, 76);

                lv_obj_set_layout(outlet_tile, LV_LAYOUT_FLEX);
                lv_obj_set_flex_flow(outlet_tile, LV_FLEX_FLOW_COLUMN);
                lv_obj_set_flex_align(outlet_tile, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

                lv_obj_set_style_pad_row(outlet_tile, 8, LV_PART_MAIN);

                LV_IMAGE_DECLARE(power);
                lv_obj_t *power_icon = lv_image_create(outlet_tile);
                lv_image_set_src(power_icon, &power);
                lv_obj_set_size(power_icon, 30, 30); // Set icon size as desired
                lv_obj_center(power_icon);

                lv_obj_t *txt = lv_label_create(outlet_tile);
                lv_label_set_text_fmt(txt,
                                      "Outlet %d\n%d kW/h",
                                      i + 1,
                                      usage);
                lv_obj_set_style_text_align(txt, LV_TEXT_ALIGN_CENTER, 0);
                lv_label_set_recolor(txt, true);
                lv_obj_set_style_text_color(txt, lv_color_hex(0xFFFF00), 0);

                static lv_style_t style;
                lv_style_init(&style);
                //lv_style_set_text_font(&style, &font_normal);
                lv_obj_add_style(txt, &style, 0);
                lv_obj_center(txt);
            }
        }
        else if (index == 3)
        {
            lv_air_create_information_panel(g_side_panel);
        }
    }
}

void performance_btn_event_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
    {
        return; // Only handle click events
    }

    // Handle performance button click
    // This function can be used to toggle performance mode or display performance metrics
    printf("Performance button clicked\n");

    lv_obj_clean(lv_scr_act()); // Clear the side panel

    lv_create_performance_page(lv_scr_act());
}

void backFromPerformancePageEventCb(lv_event_t *e)
{
    // Clear the current screen
    lv_obj_clean(lv_scr_act());

    // Reset the side panel and labels
    g_side_panel = NULL;
    g_temp_label = NULL;
    g_hum_label = NULL;

    // Recreate the main page
    lv_scythe_main_page(lv_scr_act());

    // Reset all buttons to default state
    for (int i = 0; i < 4; i++)
    {
        lv_obj_set_style_border_width(g_all_buttons[i], 0, 0);
        lv_obj_set_style_border_color(g_all_buttons[i], lv_color_hex(0x000000), 0);
        lv_obj_set_style_border_opa(g_all_buttons[i], LV_OPA_TRANSP, 0);
    }
}
