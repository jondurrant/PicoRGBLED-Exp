/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
extern "C"{
#include "lvgl.h"
}
#include "lv_port_disp.h"
#include <PicoLed.hpp>
#include <cstring>

#define LED_PIN 2
#define LED_LENGTH (16*10)
#define BYTES_PER_PIXEL 3

PicoLed::PicoLedController xLedStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LED_PIN, LED_LENGTH, PicoLed::FORMAT_RGB);


#define BUF_DIVIDER 1
static lv_display_t * display1;
static uint8_t buf1[MY_DISP_HOR_RES * MY_DISP_VER_RES / BUF_DIVIDER * BYTES_PER_PIXEL];
static uint8_t buf2[MY_DISP_HOR_RES * MY_DISP_VER_RES / BUF_DIVIDER * BYTES_PER_PIXEL];


void my_flush_cb(lv_display_t * display, const lv_area_t * area, uint8_t * px_map){
    uint8_t * buf = px_map;
    int32_t x, y;

    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
        	uint8_t b = *buf++;
        	uint8_t g = *buf++;
        	uint8_t r = *buf++;
        	uint pixel = y * MY_DISP_HOR_RES + x;
        	xLedStrip.setPixelColor(pixel, PicoLed::RGB(r, g, b));
        }
    }

    /* IMPORTANT!!!
     * Inform LVGL that flushing is complete so buffer can be modified again. */
    lv_display_flush_ready(display);
    xLedStrip.show();
}


void lv_port_disp_init(void){

	 xLedStrip.setBrightness(64);

	display1 = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);

	/* Set display buffer for display `display1`. */
	lv_display_set_buffers(display1, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

	lv_display_set_flush_cb(display1, my_flush_cb);

}


#endif
