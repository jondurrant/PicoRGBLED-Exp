/*
 * Widgets.cpp
 *
 *  Created on: 4 Aug 2025
 *      Author: jondurrant
 */

#include "Widgets.h"
#include <cstdio>





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

	lv_style_init(&xLabelSt);
	lv_style_set_text_font(&xLabelSt, &lv_font_montserrat_8);
	lv_style_set_text_color(
			&xLabelSt,
			lv_color_make(0, 0x00, 0xF0));

	pTestLbl = lv_label_create(xTV);
	lv_label_set_text(pTestLbl, "Testing a Scoll Message");
	lv_obj_set_style_text_align(pTestLbl, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pTestLbl, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(pTestLbl , &xLabelSt,  LV_PART_MAIN);
	xPos = hor;
	lv_obj_set_pos(pTestLbl,  xPos,  0);

	pTimer = lv_timer_create(timerCB, 20,  this);

}


void Widgets::timerCB(lv_timer_t * timer){
	Widgets *self = (Widgets *)lv_timer_get_user_data( timer);
	self->timerHandler(timer);
}

void Widgets::timerHandler(lv_timer_t * timer){
	//printf("Timer to %d\n", xPos);
	uint ver = lv_disp_get_ver_res(NULL);
	lv_obj_set_pos(pTestLbl,  xPos--,  0);

	int32_t l = lv_obj_get_width(pTestLbl) ;
	if (xPos < (l * -1)){
		uint hor = lv_disp_get_hor_res(NULL);
		xPos = hor;
	}
}


