/*
 * Knitt.cpp
 *
 *  Created on: 18 Jun 2026
 *      Author: jondurrant
 */

#include "Knitt.h"
#include <cstdio>
#include "FreeRTOS.h"

Knitt::Knitt() {
	xColor = lv_color_hex(0xFF0000);
}

Knitt::~Knitt() {
	// TODO Auto-generated destructor stub
}


void Knitt::timerHandler(lv_timer_t * timer) {
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);
	uint mid = ver/2;

	lv_display_t * disp = lv_obj_get_display(pCanvas);
	lv_display_enable_invalidation(disp, false);

	lv_color_t black = lv_color_hex(0x000000);

	lv_canvas_set_px(
			pCanvas,
			xPos,
			mid,
			black,
			LV_OPA_100);
	if (xLeft){
		xPos --;
		if (xPos < 0){
			xPos = 1;
			xLeft = false;
		}
	} else {
		xPos ++;
		if (xPos >= hor){
			xPos = hor -2;
			xLeft = true;
		}
	}
	lv_canvas_set_px(
			pCanvas,
			xPos,
			mid,
			xColor,
			LV_OPA_100);

	lv_display_enable_invalidation(disp, true);
	lv_obj_invalidate(pCanvas);
}
