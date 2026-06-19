/*
 * Widgets.h
 *
 *  Created on: 4 Aug 2025
 *      Author: jondurrant
 */

#ifndef EXP_LVGLDASHBOARD_SRC_WIDGETS_H_
#define EXP_LVGLDASHBOARD_SRC_WIDGETS_H_

#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/misc/lv_area.h"
#include "pico/stdlib.h"
#include "ComputePixels.h"
#include "Knitt.h"
#include "Scan.h"
#include "Direction.h"
#include "Scroll.h"
#include "Pride.h"


#define LED_SERIES 10
#define LED_NUMBER 8


class Widgets {
public:
	Widgets();
	virtual ~Widgets();

	void init();

private:

	static void timerCB(lv_timer_t * timer);
	void timerHandler(lv_timer_t * timer);

	lv_obj_t *xTV;
	lv_obj_t *xTile1;

	lv_style_t xStyleTile;

	lv_timer_t * pTimer;

	ComputePixels xPixels;
	Knitt xKnitt;
	Scan xScan;
	Direction xDirection;
	Scroll xScroll;
	Pride xPride;

	uint8_t xStep = 0;



};

#endif /* EXP_LVGLDASHBOARD_SRC_WIDGETS_H_ */
