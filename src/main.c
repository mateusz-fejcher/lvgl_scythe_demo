#include <unistd.h>
#include <lvgl.h>
#include <SDL.h>

#include "scythe_demo/lv_scythe.h"

static lv_display_t * hal_init(int32_t w, int32_t h);

int main(void)
{
	/*Initialize LVGL*/
	lv_init();

	hal_init(1000, 600);

	/*Setup your UI*/
	lv_scythe();

	while (1) {
		const uint32_t sleep_timer = lv_timer_handler();
		usleep(sleep_timer * 1000);
	}

	return 0;
}

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_display_t * hal_init(int32_t w, int32_t h)
{
  lv_group_set_default(lv_group_create());

  lv_display_t * disp = lv_sdl_window_create(w, h);

  lv_indev_t * mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);

  LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t * cursor_obj;
  cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
  lv_image_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

  lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
  lv_indev_set_display(mousewheel, disp);
  lv_indev_set_group(mousewheel, lv_group_get_default());

  return disp;
}
