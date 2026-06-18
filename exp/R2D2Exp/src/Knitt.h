/*
 * Knitt.h
 *
 *  Created on: 18 Jun 2026
 *      Author: jondurrant
 */

#ifndef EXP_R2D2EXP_SRC_KNITT_H_
#define EXP_R2D2EXP_SRC_KNITT_H_

#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/misc/lv_area.h"
#include "pico/stdlib.h"
#include "Pattern.h"

class Knitt : public Pattern {
public:
	Knitt();
	virtual ~Knitt();

protected:

	virtual void timerHandler(lv_timer_t * timer);

private:
	int xPos = 0;
	bool xLeft = false;
};

#endif /* EXP_R2D2EXP_SRC_KNITT_H_ */
