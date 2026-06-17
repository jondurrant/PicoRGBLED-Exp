/*
 * Widgets.cpp
 *
 *  Created on: 4 Aug 2025
 *      Author: jondurrant
 */

#include "Widgets.h"
#include <cstdio>
#include "pico/rand.h"
#include "FreeRTOS.h"




Widgets::Widgets() {

}

Widgets::~Widgets() {
	// TODO Auto-generated destructor stub
}



void Widgets::init() {

	xTV =lv_scr_act();
	lv_obj_clear_flag(xTV, LV_OBJ_FLAG_SCROLLABLE);
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);

	lv_style_init(&xStyleTile);
	lv_style_set_bg_color(&xStyleTile, lv_color_hex(0x000000));
	lv_style_set_bg_opa(&xStyleTile, LV_OPA_COVER);
	lv_obj_add_style(xTV, &xStyleTile, 0);

	xPixels.init(xTV);

}


void Widgets::timerCB(lv_timer_t * timer){
	Widgets *self = (Widgets *)lv_timer_get_user_data( timer);
	self->timerHandler(timer);
}

void Widgets::timerHandler(lv_timer_t * timer){
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);

}


