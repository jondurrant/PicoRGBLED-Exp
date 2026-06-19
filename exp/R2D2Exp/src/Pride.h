/*
 * Pride.h
 *
 *  Created on: 19 Jun 2026
 *      Author: jondurrant
 */

#ifndef EXP_R2D2EXP_SRC_PRIDE_H_
#define EXP_R2D2EXP_SRC_PRIDE_H_

#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/misc/lv_area.h"
#include "pico/stdlib.h"
#include "Pattern.h"

class Pride : public Pattern{
public:
	Pride();
	virtual ~Pride();

protected:
	virtual void timerHandler(lv_timer_t * timer);

	uint8_t xStep;

	static uint32_t RAINBOX[6];
};

#endif /* EXP_R2D2EXP_SRC_PRIDE_H_ */
