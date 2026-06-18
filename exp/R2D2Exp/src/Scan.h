/*
 * Scan.h
 *
 *  Created on: 18 Jun 2026
 *      Author: jondurrant
 */

#ifndef EXP_R2D2EXP_SRC_SCAN_H_
#define EXP_R2D2EXP_SRC_SCAN_H_

#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/misc/lv_area.h"
#include "pico/stdlib.h"
#include "Pattern.h"

class Scan : public Pattern {
public:
	Scan();
	virtual ~Scan();

	void showHorizontal(bool on);

protected:

	virtual void timerHandler(lv_timer_t * timer);

	void vLine(lv_color_t c, int x);
	void hLine(lv_color_t c, int y);

	int xPos = 0;
	int  yPos = 0;
	bool xLeft = false;
	bool xHorizontal = true;
};


#endif /* EXP_R2D2EXP_SRC_SCAN_H_ */
