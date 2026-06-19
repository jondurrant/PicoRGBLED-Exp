/*
 * Pride.cpp
 *
 *  Created on: 19 Jun 2026
 *      Author: jondurrant
 */

#include "Pride.h"

Pride::Pride() {
	// TODO Auto-generated constructor stub

}

Pride::~Pride() {
	// TODO Auto-generated destructor stub
}

uint32_t Pride::RAINBOX[6]={
		0xE40303 ,
		0xFF8C00 ,
		0xFFED00 ,
		0x008026 ,
		0x004DFF ,
		0x750787
};

void Pride::timerHandler(lv_timer_t * timer){
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);

	uint width = hor / 6;
	uint margin = (hor - (width * 6)) / 2;

	lv_display_t * disp = lv_obj_get_display(pCanvas);
	lv_display_enable_invalidation(disp, false);

	lv_canvas_fill_bg(pCanvas, lv_color_hex(0x000000), LV_OPA_COVER);
	for (int i=0; i < 6; i++){
		uint colorInd = (i + xStep) % 6;
		lv_color_t c = lv_color_hex(RAINBOX[colorInd]);
		int x = margin + i * width;
		for (int y=0; y < ver; y++){
			lv_canvas_set_px(
						pCanvas,
						x,
						y,
						c,
						LV_OPA_100);
		}
	}

	lv_display_enable_invalidation(disp, true);
	lv_obj_invalidate(pCanvas);

	xStep ++;
	if (xStep >= 6){
		xStep = 0;
	}

}
