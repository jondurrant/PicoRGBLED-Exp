/*
 * Scan.cpp
 *
 *  Created on: 18 Jun 2026
 *      Author: jondurrant
 */

#include "Scan.h"
#include <cstdio>
#include "FreeRTOS.h"
#include "pico/rand.h"

Scan::Scan() {
	xColor = lv_color_hex(0x0000A0);
	yPos = lv_disp_get_ver_res(NULL) / 2;
}

Scan::~Scan() {
	// TODO Auto-generated destructor stub
}

void Scan::showHorizontal(bool on){
	xHorizontal = on;
}


void Scan::vLine(lv_color_t c, int x){
	uint ver = lv_disp_get_ver_res(NULL);
	for (int i = 0; i < ver; i++){
		lv_canvas_set_px(
				pCanvas,
				x,
				i,
				c,
				LV_OPA_100);
	}
}
void Scan::hLine(lv_color_t c, int y){
	uint hor = lv_disp_get_hor_res(NULL);
	for (int i = 0; i < hor; i++){
		lv_canvas_set_px(
				pCanvas,
				i,
				y,
				c,
				LV_OPA_100);
	}
}


void Scan::timerHandler(lv_timer_t * timer) {
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);
	uint mid = ver/2;

	lv_display_t * disp = lv_obj_get_display(pCanvas);
	lv_display_enable_invalidation(disp, false);

	lv_color_t black = lv_color_hex(0x000000);

	vLine(black, xPos);
	hLine(black, yPos);

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

	int dir = get_rand_32() % ver;
	if (dir > yPos){
		yPos ++;
		if (yPos >= ver){
			yPos = ver -1;
		}
	} else if (dir < yPos){
		yPos --;
		if (yPos < 0){
			yPos = 0;
		}
	}

	vLine(xColor, xPos);
	if (xHorizontal){
		hLine(xColor, yPos);
	}

	lv_display_enable_invalidation(disp, true);
	lv_obj_invalidate(pCanvas);
}
