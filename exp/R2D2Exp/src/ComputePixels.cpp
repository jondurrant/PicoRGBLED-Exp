/*
 * ComputePixels.cpp
 *
 *  Created on: 17 Jun 2026
 *      Author: jondurrant
 */

#include "ComputePixels.h"
#include <cstdio>
#include "pico/rand.h"
#include "FreeRTOS.h"

ComputePixels::ComputePixels() {
	// TODO Auto-generated constructor stub

}

ComputePixels::~ComputePixels() {
	// TODO Auto-generated destructor stub
}

void ComputePixels::init(lv_obj_t * parent){
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);

	pCanvas = lv_canvas_create(parent);
	lv_color_t *buf = (lv_color_t *)pvPortMalloc(hor * ver * sizeof(lv_color_t));
	if (buf) {
		lv_canvas_set_buffer(pCanvas, buf, hor, ver, LV_COLOR_FORMAT_ARGB8888);
		lv_obj_set_size(pCanvas, hor, ver);
		lv_obj_center(pCanvas);
		lv_canvas_fill_bg(pCanvas, lv_color_hex(0x000000), LV_OPA_COVER);
	} else {
		lv_obj_set_size(pCanvas, 1, 1);
	}

	for (int s=0; s < LED_SERIES; s++){
		lv_color_t c = lv_color_hex(colors[s]);
		for (int n=0; n < LED_NUMBER; n++){
			int x = get_rand_32() % hor;
			int y = get_rand_32() % ver;
			xLeds[s][n][0] = x;
			xLeds[s][n][1] = y;
			lv_canvas_set_px(
					pCanvas,
					x,
					y,
					c,
					LV_OPA_50);
		}
	}

	pTimer = lv_timer_create(timerCB, 200,  this);

}

void ComputePixels::timerCB(lv_timer_t * timer){
	ComputePixels *self = (ComputePixels *)lv_timer_get_user_data( timer);
	self->timerHandler(timer);
}

void ComputePixels::timerHandler(lv_timer_t * timer) {
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);

	lv_display_t * disp = lv_obj_get_display(pCanvas);
	lv_display_enable_invalidation(disp, false);


	if (xStep >= LED_SERIES){
		xStep = 0;
	}

	int s = xStep;
	lv_color_t c = lv_color_hex(0);
	lv_color_t cn = lv_color_hex(colors[s]);
	for (int n=0; n < LED_NUMBER; n++){
		int x = xLeds[s][n][0];
		int y = xLeds[s][n][1];
		lv_canvas_set_px(
							pCanvas,
							x,
							y,
							c,
							LV_OPA_50);
		 x = get_rand_32() % hor;
		 y = get_rand_32() % ver;
		xLeds[s][n][0] = x;
		xLeds[s][n][1] = y;
		lv_canvas_set_px(
							pCanvas,
							x,
							y,
							cn,
							10);
	}


	//Brighten Sequence

	for (int i=0; i < LED_SERIES/2; i++){
		int s = (i + xStep) % LED_SERIES;
		uint8_t a = (0xFF / LED_SERIES) * i * 2;
		for (int n=0; n < LED_NUMBER; n++){
			int x = xLeds[s][n][0];
			int y = xLeds[s][n][1];
			lv_color32_t px = lv_canvas_get_px(pCanvas, x, y);
			lv_canvas_set_px(pCanvas, x, y, lv_color_make(px.red, px.green, px.blue), a);
		}
	}



	//Dim Sequence
	for (int i=0; i < LED_SERIES/2; i++){
		int s = (i + xStep + LED_SERIES /2) % LED_SERIES;
		uint8_t a = (0xFF / LED_SERIES) * i * 2;
		a = 0xFF - a;
		for (int n=0; n < LED_NUMBER; n++){
			int x = xLeds[s][n][0];
			int y = xLeds[s][n][1];
			lv_color32_t px = lv_canvas_get_px(pCanvas, x, y);
			lv_canvas_set_px(pCanvas, x, y, lv_color_make(px.red, px.green, px.blue), a);
		}
	}


	xStep++;

	lv_display_enable_invalidation(disp, true);
	lv_obj_invalidate(pCanvas);
}

