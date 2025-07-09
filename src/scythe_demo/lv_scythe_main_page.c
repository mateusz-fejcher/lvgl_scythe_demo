#include "lv_scythe_main_page.h"
#include "lv_scythe_callbacks.h"
#include "Icons/wavingHand.c"
#include "Icons/thermostat.c"
#include "Icons/water_drop.c"
#include "Icons/voltage.c"
#include "Icons/air.c"
#include "lvgl.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// If you want to keep these globals accessible, you can declare them as extern in a header.
lv_obj_t *g_side_panel = NULL;
lv_obj_t *g_temp_tile = NULL;
lv_obj_t *g_temp_label = NULL;
lv_obj_t *g_hum_tile = NULL;
lv_obj_t *g_hum_label = NULL;
lv_obj_t *g_all_buttons[4] = {NULL, NULL, NULL, NULL};

void lv_scythe_main_page(lv_obj_t *parent)
{
    /* 1) background */
    lv_obj_remove_style_all(parent);
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x161616), 0);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, 0);

    lv_obj_t *root = lv_obj_create(parent);
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, LV_PCT(100), LV_PCT(100)); // Fill the whole window

    /* 2) Title row container */
    lv_obj_t *title_row = lv_obj_create(root);
    lv_obj_remove_style_all(title_row); // Remove default styles
    lv_obj_set_size(title_row, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(title_row, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_bg_opa(title_row, LV_OPA_TRANSP, 0); // Transparent background
    lv_obj_align(title_row, LV_ALIGN_TOP_LEFT, 20, 20);
    lv_obj_set_flex_align(title_row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t *title_label = lv_label_create(title_row);
    lv_label_set_text(title_label, "Hello Mateusz");
    // lv_obj_set_style_text_font(title_label, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(title_label, lv_color_white(), 0);

    LV_IMAGE_DECLARE(wavingHand);
    lv_obj_t *wavingHand_icon = lv_image_create(title_row);
    lv_image_set_src(wavingHand_icon, &wavingHand);
    lv_obj_set_size(wavingHand_icon, 50, 50); // Set icon size to 50x50 px
    lv_obj_set_style_pad_left(wavingHand_icon, 15, 0); // 15px separation from label

    // Add 40px spacing between waving hand and performance button
    lv_obj_t *spacer = lv_obj_create(title_row);
    lv_obj_remove_style_all(spacer);
    lv_obj_set_size(spacer, 40, 1); // 40px wide, 1px tall invisible spacer
    lv_obj_set_style_bg_opa(spacer, LV_OPA_TRANSP, 0);

    // Replace performance label with a button
    lv_obj_t* performance_btn = lv_btn_create(title_row);
    lv_obj_remove_style_all(performance_btn);
    lv_obj_set_style_bg_color(performance_btn, lv_color_hex(0x404040), 0);
    lv_obj_set_style_bg_opa(performance_btn, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(performance_btn, 8, 0);
    lv_obj_set_style_pad_all(performance_btn, 10, 0); // Add 10px padding on all sides
    lv_obj_set_size(performance_btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_event_cb(performance_btn, performance_btn_event_cb, LV_EVENT_CLICKED, (void *)(uintptr_t)0);

    lv_obj_t* performance_label = lv_label_create(performance_btn);
    lv_label_set_text(performance_label, "Performance");
    // lv_obj_set_style_text_font(performance_label, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(performance_label, lv_color_white(), 0);
    lv_obj_center(performance_label);

    /* 3) Grid container on the left */
    lv_obj_t *grid_container = lv_obj_create(root);
    lv_obj_remove_style_all(grid_container);
    lv_obj_set_size(grid_container, 650, 500);
    lv_obj_align(grid_container, LV_ALIGN_LEFT_MID, 10, 20);
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(grid_container, col_dsc, row_dsc);

    /* Add spacing/padding */
    lv_obj_set_style_pad_row(grid_container, 15, 0);
    lv_obj_set_style_pad_column(grid_container, 15, 0);
    lv_obj_set_style_pad_all(grid_container, 10, 0);

    /* 3a) Create four tiles in the grid */
    const char *tile_texts[] = {
        "Temperature: 13.0°C",
        "Humidity: Low",
        "Power: 25 kW/h",
        "Air Quality: Good"};

    LV_IMAGE_DECLARE(thermostat);
    LV_IMAGE_DECLARE(water_drop);
    LV_IMAGE_DECLARE(voltage);
    LV_IMAGE_DECLARE(air);

    // Create an array of pointers to the image descriptors:
    const lv_image_dsc_t* icons[] = {
        &thermostat,
        &water_drop,
        &voltage,
        &air,
    };

    for (int i = 0; i < 4; i++)
    {
        lv_obj_t *tile = lv_obj_create(grid_container);
        lv_obj_remove_style_all(tile);
        lv_obj_set_size(tile, LV_PCT(100), LV_PCT(100));
        lv_obj_set_style_bg_color(tile, lv_color_hex(0x404040), 0);
        lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
        lv_obj_set_style_radius(tile, 8, 0);

        lv_obj_set_grid_cell(tile,
                             LV_GRID_ALIGN_STRETCH, i % 2, 1,
                             LV_GRID_ALIGN_STRETCH, i / 2, 1);

        // Create a flex row container centered in the tile
        lv_obj_t *row = lv_obj_create(tile);
        lv_obj_remove_style_all(row);
        lv_obj_set_layout(row, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, 0);
        lv_obj_set_size(row, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_center(row);

        // Icon on the left
        lv_obj_t *icon = lv_image_create(row);
        lv_image_set_src(icon, icons[i]);
        lv_obj_set_size(icon, 30, 30);

        // Label on the right
        lv_obj_t *label = lv_label_create(row);
        lv_label_set_text(label, tile_texts[i]);
        lv_obj_set_style_text_color(label, lv_color_white(), 0);
        // lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0); // Adjust font as needed
        lv_obj_set_style_pad_left(label, 10, 0); // Space between icon and label

        g_all_buttons[i] = tile;

        if (i == 0)
        {
            g_temp_tile = tile;
            g_temp_label = label;
        }
        else if (i == 1)
        {
            g_hum_tile = tile;
            g_hum_label = label;
        }

        lv_obj_add_event_cb(tile, tile_event_cb, LV_EVENT_CLICKED, (void *)(uintptr_t)i);
    }

    g_side_panel = lv_obj_create(root);
    lv_obj_remove_style_all(g_side_panel);
    lv_obj_set_style_bg_color(g_side_panel, lv_color_hex(0x252525), 0);
    lv_obj_set_style_bg_opa(g_side_panel, LV_OPA_COVER, 0);
    lv_obj_set_size(g_side_panel, 260, 480);
    lv_obj_align(g_side_panel, LV_ALIGN_RIGHT_MID, -50, 20);

    lv_obj_t *panel_label = lv_label_create(g_side_panel);
    lv_label_set_text(panel_label, "Select a tile\nfor more info...");
    lv_obj_set_style_text_color(panel_label, lv_color_hex(0xBBBBBB), 0);
    lv_obj_center(panel_label);

    srand(time(NULL));
}
