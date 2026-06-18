/*
 * Direction.cpp
 *
 *  Created on: 18 Jun 2026
 *      Author: jondurrant
 */

#include "Direction.h"
#include "FreeRTOS.h"

Direction::Direction() {
	setColor(lv_color_hex(0x00A000));
}

Direction::~Direction() {
	// TODO Auto-generated destructor stub
}

uint8_t Direction::LEFT[10] = {
		0x6,
		0xE,
		0x1E,
		0x3E,
		0x7E,
		0x7E,
		0x3E,
		0x1E,
		0xE,
		0x6
};
 uint8_t Direction::RIGHT[10] = {
		 0x60,
		 0x70,
		 0x78,
		 0x7C,
		 0x7E,
		 0x7E,
		 0x7C,
		 0x78,
		 0x70,
		 0x60
};
 uint8_t Direction::UP[10] = {
		 0x0,
		 0x18,
		 0x18,
		 0x3C,
		 0x3C,
		 0x7E,
		 0x7E,
		 0xFF,
		 0xFF,
		 0x0
 };
 uint8_t Direction::DOWN[10] = {
		 0x0,
		 0xFF,
		 0xFF,
		 0x7E,
		 0x7E,
		 0x3C,
		 0x3C,
		 0x18,
		 0x18,
		 0x0
 };
 uint8_t Direction::STOP[20] = {
		 0x18,
		 0x3C,
		 0x7E,
		 0xFF,
		 0x81,
		 0x81,
		 0xFF,
		 0x7E,
		 0x3C,
		 0x18,
		 0x0,
		 0x0,
		 0x0,
		 0x0,
		 0x7E,
		 0x7E,
		 0x0,
		 0x0,
		 0x0,
		 0x0
 };

 void Direction::init(lv_obj_t * parent){
	 uint hor = 8;
	uint ver = 10;

	pCanvas = lv_canvas_create(parent);
	lv_color_t *buf = (lv_color_t *)pvPortMalloc(8 * 10 * 4); //sizeof(lv_color_t));
	if (buf) {
		lv_canvas_set_buffer(pCanvas, buf, 8, 10, LV_COLOR_FORMAT_ARGB8888);
		lv_obj_set_size(pCanvas, 8, 10);
		lv_obj_center(pCanvas);
		lv_canvas_fill_bg(pCanvas, lv_color_hex(0x000000), LV_OPA_COVER);
	} else {
		lv_obj_set_size(pCanvas, 1, 1);
	}

	setDirection(DIRECTION_STOP);

	setSpeedMs(300);
 }


 void Direction::drawGlif(uint8_t *data, lv_color_t c){
	lv_display_t * disp = lv_obj_get_display(pCanvas);
	lv_display_enable_invalidation(disp, false);

	lv_canvas_fill_bg(pCanvas, lv_color_hex(0x000000), LV_OPA_COVER);
	for (int y=0; y < 10; y++){
		uint8_t px = data[y];
		for (int x = 7; x >= 0; x--){
			if ((px & 1) == 1){
				lv_canvas_set_px(
						pCanvas,
						x,
						y,
						c,
						LV_OPA_100);
			}
			px = px >> 1;
		}
	}

	lv_display_enable_invalidation(disp, true);
	lv_obj_invalidate(pCanvas);
 }

 void Direction::drawGlif2C(uint8_t *data, lv_color_t c1, lv_color_t c2){
	lv_display_t * disp = lv_obj_get_display(pCanvas);
	lv_display_enable_invalidation(disp, false);

	lv_canvas_fill_bg(pCanvas, lv_color_hex(0x000000), LV_OPA_COVER);
	for (int y=0; y < 10; y++){
		uint8_t px = data[y];
		for (int x = 7; x >= 0; x--){
			if ((px & 1) == 1){
				lv_canvas_set_px(
						pCanvas,
						x,
						y,
						c1,
						LV_OPA_100);
			}
			px = px >> 1;
		}
	}

	for (int y=0; y < 10; y++){
			uint8_t px = data[y+10];
			for (int x = 7; x >= 0; x--){
				if ((px & 1) == 1){
					lv_canvas_set_px(
							pCanvas,
							x,
							y,
							c2,
							LV_OPA_100);
				}
				px = px >> 1;
			}
		}

	lv_display_enable_invalidation(disp, true);
	lv_obj_invalidate(pCanvas);
 }


 void Direction::timerHandler(lv_timer_t * timer) {
 	int hor = lv_disp_get_hor_res(NULL);
 	int ver = lv_disp_get_ver_res(NULL);

 	if (xDirection == DIRECTION_STOP){
 		lv_obj_center(pCanvas);
 		return;
 	}

 	if (xDirection == DIRECTION_RIGHT){
		xPos++;
		if (xPos >= hor){
			xPos = -8;
		}
		lv_obj_set_pos(pCanvas,  xPos, 0);
 	}

 	if (xDirection == DIRECTION_LEFT){
		xPos--;
		if (xPos < -10){
			xPos = hor -1;
		}
		lv_obj_set_pos(pCanvas,  xPos, 0);
 	}

	if (xDirection == DIRECTION_DOWN){
		yPos++;
		if (yPos >= ver ){
			yPos = -10;
		}
		lv_obj_set_pos(pCanvas,  0, yPos);
 	}

	if (xDirection == DIRECTION_UP){
		yPos--;
		if (yPos < -10 ){
			yPos = ver ;
		}
		lv_obj_set_pos(pCanvas,  0, yPos);
 	}
 }

 void Direction::setDirection(DirectionType d){
	 	 xDirection = d;

	 	xPos = 0;
		yPos = (lv_disp_get_hor_res(NULL) + 8) / 2;
		lv_obj_set_pos(pCanvas,  xPos, yPos);
		switch(xDirection){
			case DIRECTION_LEFT:
				drawGlif(LEFT, xColor);
				break;
			case DIRECTION_RIGHT:
				drawGlif(RIGHT, xColor);
				break;
			case DIRECTION_UP:
				drawGlif(UP, xColor);
				break;
			case DIRECTION_DOWN:
				drawGlif(DOWN, xColor);
				break;
			case DIRECTION_STOP:
				drawGlif2C(STOP, lv_color_hex(0xA00000), lv_color_hex(0xA0A0A0));
				break;
		}
 }


