#include "lv_scythe_performance_page.h"
#include "Icons/power.c"
#include "lv_scythe_callbacks.h"

static void set_angle(void * img, int32_t v)
{
    lv_img_set_angle(img, v);
}

void lv_create_performance_page(lv_obj_t *parent)
{
    lv_obj_clean(parent); // Clear the parent container

    lv_obj_set_style_bg_color(parent, lv_color_hex(0x161616), 0);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, 0);

    // Create a column container
    lv_obj_t *col = lv_obj_create(parent);
    lv_obj_set_size(col, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_flow(col, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(col, 10, 0);
    lv_obj_set_scrollbar_mode(col, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(col, LV_OPA_TRANSP, 0); // Make column transparent
    lv_obj_set_style_border_opa(col, LV_OPA_TRANSP, 0); // Remove border

    // Back button at the top
    lv_obj_t *back_btn = lv_btn_create(col);
    lv_obj_set_width(back_btn, lv_pct(100));
    lv_obj_add_event_cb(back_btn, backFromPerformancePageEventCb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "Back");
    lv_obj_center(back_label);

    // Grid container below the button
    lv_obj_t *grid = lv_obj_create(col);
    lv_obj_set_flex_grow(grid, 1);
    lv_obj_set_size(grid, lv_pct(100), lv_pct(100));
    static lv_coord_t col_dsc[11];
    static lv_coord_t row_dsc[8];
    for(int i=0;i<10;i++) col_dsc[i] = LV_GRID_FR(1);
    col_dsc[10] = LV_GRID_TEMPLATE_LAST;
    for(int i=0;i<7;i++) row_dsc[i] = LV_GRID_FR(1);
    row_dsc[7] = LV_GRID_TEMPLATE_LAST;
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);
    lv_obj_set_style_pad_gap(grid, 4, 0);
    lv_obj_set_style_pad_all(grid, 4, 0);
    lv_obj_set_style_bg_opa(grid, LV_OPA_TRANSP, 0); // Make grid transparent
    lv_obj_set_style_border_opa(grid, LV_OPA_TRANSP, 0); // Remove border

    // Add rectangles to the grid
    for(int r=0; r<7; r++) {
        for(int c=0; c<10; c++) {
            lv_obj_t *rect = lv_obj_create(grid);
            lv_obj_set_grid_cell(rect, LV_GRID_ALIGN_STRETCH, c, 1, LV_GRID_ALIGN_STRETCH, r, 1);
            lv_obj_set_style_bg_opa(rect, LV_OPA_TRANSP, 0); // Make rectangle transparent
            lv_obj_set_style_border_color(rect, lv_color_hex(0x000000), 0); // Black border
            lv_obj_set_style_border_width(rect, 2, 0);
            lv_obj_set_style_radius(rect, 4, 0);

            // Add power icon centered in the rectangle
            // lv_obj_t *icon = lv_image_create(rect); // After this line application freezes.
            // lv_image_set_src(icon, &power);
            // lv_obj_center(icon);

            // Animate icon rotation clockwise
            // lv_anim_t a;
            // lv_anim_init(&a);
            // lv_anim_set_var(&a, icon);
            // lv_anim_set_exec_cb(&a, set_angle);
            // lv_anim_set_values(&a, 0, 3600);
            // lv_anim_set_time(&a, 5000);
            // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
            // lv_anim_start(&a);
        }
    }
}
