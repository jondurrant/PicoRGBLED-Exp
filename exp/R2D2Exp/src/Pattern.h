/*
 * Pattern.h
 *
 *  Created on: 18 Jun 2026
 *      Author: jondurrant
 */

#ifndef EXP_R2D2EXP_SRC_PATTURN_H_
#define EXP_R2D2EXP_SRC_PATTURN_H_

#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/misc/lv_area.h"
#include "pico/stdlib.h"

class Pattern {
public:
	Pattern();
	virtual ~Pattern();

	virtual void init(lv_obj_t * parent);

	virtual void setColor(lv_color_t c);
	virtual void setSpeedMs(uint ms);

protected:
	virtual void buildCanvas(lv_obj_t * parent);
	static void timerCB(lv_timer_t * timer);
	virtual void timerHandler(lv_timer_t * timer);

	lv_timer_t * pTimer = NULL;

	lv_obj_t * pCanvas = NULL;
	lv_color_t xColor;
	uint xMilliSec = 100;

};

#endif /* EXP_R2D2EXP_SRC_PATTURN_H_ */
