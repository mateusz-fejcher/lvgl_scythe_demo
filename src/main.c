#include <unistd.h>
#include <lvgl.h>
#include <SDL.h>

int main(void)
{
	/*Initialize LVGL*/
	lv_init();

	/*Initialize the HAL (display, input devices, tick) for LVGL*/
	lv_display_t *disp = lv_sdl_window_create(1024, 768);

	/*Setup your UI*/
	lv_obj_t *label = lv_label_create(lv_screen_active());
	lv_label_set_text_static(label, "Hello World");
	lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

	while (1) {
		const uint32_t sleep_timer = lv_timer_handler();
		usleep(sleep_timer * 1000);
	}

	return 0;
}
