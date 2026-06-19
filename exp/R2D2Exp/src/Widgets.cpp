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

	lv_obj_clear_flag(lv_screen_active(), LV_OBJ_FLAG_SCROLLABLE);
	xTV =lv_tileview_create(lv_screen_active());
	lv_obj_clear_flag(xTV, LV_OBJ_FLAG_SCROLLABLE);
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);

	lv_style_init(&xStyleTile);
	lv_style_set_bg_color(&xStyleTile, lv_color_hex(0x000000));
	lv_style_set_bg_opa(&xStyleTile, LV_OPA_COVER);
	lv_obj_add_style(xTV, &xStyleTile, 0);



	 lv_obj_t * tile;

	tile = lv_tileview_add_tile(xTV, 0, 0, LV_DIR_NONE);
	lv_obj_clear_flag(tile, LV_OBJ_FLAG_SCROLLABLE);
	xScroll.init(tile);
	tile = lv_tileview_add_tile(xTV, 0, 1, LV_DIR_NONE);
	xKnitt.init(tile);
	tile = lv_tileview_add_tile(xTV, 0, 2, LV_DIR_NONE);
	xScan.init(tile);

	tile = lv_tileview_add_tile(xTV, 0, 3, LV_DIR_NONE);
	lv_obj_clear_flag(tile, LV_OBJ_FLAG_SCROLLABLE);
	xDirection.init(tile);
	xDirection.setSpeedMs(50);

	tile = lv_tileview_add_tile(xTV, 0, 4, LV_DIR_NONE);
	xPixels.init(tile);

	tile = lv_tileview_add_tile(xTV, 0, 5, LV_DIR_NONE);
	xPride.init(tile);
	xPride.setSpeedMs(250);

	pTimer = lv_timer_create(timerCB, 5000,  this);
}


void Widgets::timerCB(lv_timer_t * timer){
	Widgets *self = (Widgets *)lv_timer_get_user_data( timer);
	self->timerHandler(timer);
}

void Widgets::timerHandler(lv_timer_t * timer){
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);

	switch(xStep){
	case 0:
		lv_tileview_set_tile_by_index(xTV, 0, 0, LV_ANIM_OFF);
		break;
	case 1:
		lv_tileview_set_tile_by_index(xTV, 0, 1, LV_ANIM_OFF);
		break;
	case 2:
		xScan.setColor(lv_color_hex(0x005000));
		xScan.showHorizontal(true);
		lv_tileview_set_tile_by_index(xTV, 0, 2, LV_ANIM_OFF);
		break;
	case 3:
		xScan.setColor(lv_color_hex(0x005020));
		xScan.showHorizontal(false);
		lv_tileview_set_tile_by_index(xTV, 0, 2, LV_ANIM_OFF);
		break;
	case 4:
		xDirection.setDirection(DIRECTION_STOP);
		lv_tileview_set_tile_by_index(xTV, 0, 3, LV_ANIM_OFF);
		break;
	case 5:
		xDirection.setDirection(DIRECTION_DOWN);
		lv_tileview_set_tile_by_index(xTV, 0, 3, LV_ANIM_OFF);
		break;
	case 6:
		xDirection.setDirection(DIRECTION_LEFT);
		lv_tileview_set_tile_by_index(xTV, 0, 3, LV_ANIM_OFF);
		break;
	case 7:
		xDirection.setDirection(DIRECTION_UP);
		lv_tileview_set_tile_by_index(xTV, 0, 3, LV_ANIM_OFF);
		break;
	case 8:
		xDirection.setDirection(DIRECTION_RIGHT);
		lv_tileview_set_tile_by_index(xTV, 0, 3, LV_ANIM_OFF);
		break;
	case 9:
		lv_tileview_set_tile_by_index(xTV, 0, 4, LV_ANIM_OFF);
		break;
	case 10:
		lv_tileview_set_tile_by_index(xTV, 0, 5, LV_ANIM_OFF);
		break;
	}

	xStep ++;
	if (xStep > 10){
		xStep = 0;
	}


}


