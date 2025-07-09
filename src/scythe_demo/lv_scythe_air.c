#include "lv_scythe_air.h"
#include "Icons/co_2_cloud.c"
#include "Icons/cloud.c"
#include "Icons/eye.c"
#include "Icons/wave.c"

void lv_air_create_information_panel(lv_obj_t *parent) {
    lv_obj_t *air_information = lv_obj_create(parent);
    lv_obj_remove_style_all(air_information);
    lv_obj_set_size(air_information, LV_PCT(85), 270);
    lv_obj_align(air_information, LV_ALIGN_CENTER, 0, 0); // Centered in parent
    lv_obj_set_layout(air_information, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(air_information, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        air_information,
        LV_FLEX_ALIGN_START,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(air_information, 28, 0); // Increase row spacing

    static const char *item_titles[] = {
        "CO2 Levels",
        "PM2.5 Particulate\nMatter",
        "Visibility",
        "Air Pressure"};
    static const char *item_values[] = {
        "412 ppm",
        "35 mg/m3",
        "6.4 km",
        "1013 hPa"};

    LV_IMAGE_DECLARE(co_2_cloud);
    LV_IMAGE_DECLARE(cloud);
    LV_IMAGE_DECLARE(eye);
    LV_IMAGE_DECLARE(wave);

    const lv_image_dsc_t* icons[] = {
        &co_2_cloud,
        &cloud,
        &eye,
        &wave,
    };

    for (int i = 0; i < 4; i++) {
        lv_obj_t *row = lv_obj_create(air_information);
        lv_obj_remove_style_all(row);
        lv_obj_set_size(row, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_style_pad_column(row, 10, 0);
        lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, 0);
        lv_obj_set_layout(row, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(row,
                              LV_FLEX_ALIGN_START,
                              LV_FLEX_ALIGN_CENTER,
                              LV_FLEX_ALIGN_CENTER);
        // Icon on the left
        lv_obj_t *icon = lv_image_create(row);
        lv_image_set_src(icon, icons[i]);
        lv_obj_set_size(icon, 30, 30);
        lv_obj_align(icon, LV_ALIGN_LEFT_MID, 0, 0);
        // Column for two texts on the right
        lv_obj_t *col = lv_obj_create(row);
        lv_obj_remove_style_all(col);
        lv_obj_set_style_bg_opa(col, LV_OPA_TRANSP, 0);
        lv_obj_set_layout(col, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(col, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(col, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_height(col, LV_SIZE_CONTENT);
        lv_obj_set_width(col, LV_SIZE_CONTENT);
        // Top label (bigger font)
        lv_obj_t *top_label = lv_label_create(col);
        lv_label_set_text(top_label, item_titles[i]);
        lv_obj_set_style_text_color(top_label, lv_color_hex(0xFFFFFF), 0);
        // lv_obj_set_style_text_font(top_label, &lv_font_montserrat_20, 0);
        lv_obj_set_style_text_align(top_label, LV_TEXT_ALIGN_LEFT, 0);
        lv_obj_set_style_pad_top(top_label, 0, 0);
        lv_obj_set_style_pad_bottom(top_label, 0, 0);
        // Bottom label (smaller font)
        lv_obj_t *bottom_label = lv_label_create(col);
        lv_label_set_text(bottom_label, item_values[i]);
        lv_obj_set_style_text_color(bottom_label, lv_color_hex(0xBBBBBB), 0);
        lv_obj_set_style_text_font(bottom_label, &lv_font_montserrat_14, 0);
        lv_obj_set_style_text_align(bottom_label, LV_TEXT_ALIGN_LEFT, 0);
        lv_obj_set_style_pad_top(bottom_label, 0, 0);
        lv_obj_set_style_pad_bottom(bottom_label, 0, 0);
    }
}
