#include <unistd.h>
#include <lvgl.h>
#include <SDL.h>

#include "scythe_demo/lv_scythe.h"

int main(void)
{
	/*Initialize LVGL*/
	lv_init();

	/*Initialize the HAL (display, input devices, tick) for LVGL*/
	lv_display_t *disp = lv_sdl_window_create(1000, 600);

	/*Setup your UI*/
	lv_scythe();

	while (1) {
		const uint32_t sleep_timer = lv_timer_handler();
		usleep(sleep_timer * 1000);
	}

	return 0;
}
