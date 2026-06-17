/*
 * ComputePixels.h
 *
 *  Created on: 17 Jun 2026
 *      Author: jondurrant
 */

#ifndef EXP_R2D2EXP_SRC_COMPUTEPIXELS_H_
#define EXP_R2D2EXP_SRC_COMPUTEPIXELS_H

#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/misc/lv_area.h"
#include "pico/stdlib.h"


#define LED_SERIES 10
#define LED_NUMBER 8

class ComputePixels {
public:
	ComputePixels();
	virtual ~ComputePixels();

	void init(lv_obj_t * parent);
private:

	static void timerCB(lv_timer_t * timer);
	void timerHandler(lv_timer_t * timer);

	lv_obj_t * pCanvas;
	uint8_t xStep = 0;
	uint8_t xLeds[LED_SERIES][LED_NUMBER][2];
	lv_timer_t * pTimer;

	uint32_t colors[LED_SERIES] = {
					0xFF0000,
					0xFF4500,
					0xFFA500,
					0xFFC000,
					0xFFFF00,
					0x00FF00,
					0x00FFFF,
					0x0000FF,
					0x4B0082,
					0x8A2BE2
			};
};

#endif /* EXP_R2D2EXP_SRC_COMPUTEPIXELS_H_ */
