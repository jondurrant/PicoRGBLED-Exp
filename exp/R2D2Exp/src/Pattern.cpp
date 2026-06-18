/*
 * Pattern.cpp
 *
 *  Created on: 18 Jun 2026
 *      Author: jondurrant
 */

#include "Pattern.h"
#include "FreeRTOS.h"

Pattern::Pattern() {
	xColor = lv_color_hex(0xA0A0A0);
}

Pattern::~Pattern() {
	// TODO Auto-generated destructor stub
}

void Pattern::init(lv_obj_t * parent){

	buildCanvas(parent);
	setSpeedMs(xMilliSec);
}

void Pattern::buildCanvas(lv_obj_t * parent){
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
}

void Pattern::setColor(lv_color_t c){
	xColor = c;
}
void Pattern::setSpeedMs(uint ms){
	xMilliSec = ms;
	if (pTimer != NULL){
		lv_timer_delete(pTimer);
	}
	pTimer = lv_timer_create(timerCB, xMilliSec,  this);
}



void Pattern::timerCB(lv_timer_t * timer){
	Pattern *self = (Pattern *)lv_timer_get_user_data( timer);
	self->timerHandler(timer);
}

void Pattern::timerHandler(lv_timer_t * timer){

}
