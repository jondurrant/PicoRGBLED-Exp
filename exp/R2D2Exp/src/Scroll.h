/*
 * Scroll.h
 *
 *  Created on: 19 Jun 2026
 *      Author: jondurrant
 */

#ifndef EXP_R2D2EXP_SRC_SCROLL_H_
#define EXP_R2D2EXP_SRC_SCROLL_H_

#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/misc/lv_area.h"
#include "pico/stdlib.h"
#include "Pattern.h"

class Scroll : public Pattern{
public:
	Scroll();
	virtual ~Scroll();

	virtual void init(lv_obj_t * parent);

	virtual void setMessage(char * msg);

protected:
	virtual void timerHandler(lv_timer_t * timer);

private:
	lv_obj_t *pLabel;
	lv_style_t xLabelStyle;
	int xPos = 0;
};

#endif /* EXP_R2D2EXP_SRC_SCROLL_H_ */
