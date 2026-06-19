/*
 * Scroll.cpp
 *
 *  Created on: 19 Jun 2026
 *      Author: jondurrant
 */

#include "Scroll.h"

#define SCROLL_Y 1

Scroll::Scroll() {
	setColor( lv_color_hex(0xA0A0A0));

}

Scroll::~Scroll() {
	// TODO Auto-generated destructor stub
}

void Scroll::init(lv_obj_t * parent){
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);

	lv_style_init(&xLabelStyle);
	lv_style_set_text_font(&xLabelStyle, &lv_font_montserrat_8);
	lv_style_set_text_color(
			&xLabelStyle,
			xColor);

	pLabel = lv_label_create(parent);
	lv_label_set_text(pLabel, "Hello World");
	//lv_obj_set_width(pLabel, hor);
	lv_obj_set_style_text_align(pLabel, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_add_style(pLabel , &xLabelStyle,  LV_PART_MAIN);

	xPos = hor;
	lv_obj_set_pos(pLabel,  xPos, SCROLL_Y);

	setSpeedMs(100);

}

void Scroll::setMessage(char * msg){
	lv_label_set_text(pLabel, msg);
}

void Scroll::timerHandler(lv_timer_t * timer){
	int hor = lv_disp_get_hor_res(NULL);
	xPos--;
	if (xPos < (lv_obj_get_width(pLabel) * -1)){
		xPos = hor;
	}
	lv_obj_set_pos(pLabel,  xPos, SCROLL_Y);
}
