/**
 * @file lv_scythe.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_scythe.h"
#include "lv_scythe_main_page.h"

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN && LV_MEM_SIZE < (38ul * 1024ul)
#error Insufficient memory for lv_demo_widgets. Please set LV_MEM_SIZE to at least 38KB (38ul * 1024ul).  48KB is recommended.
#endif

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

#include "lvgl.h"

/***********************************************************
 * MAIN DEMO FUNCTION
 ***********************************************************/

void lv_scythe(void)
{
    lv_scythe_main_page(lv_scr_act());
    lv_obj_enable_style_refresh(true);
}
