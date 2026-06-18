/*
 * Direction.h
 *
 *  Created on: 18 Jun 2026
 *      Author: jondurrant
 */

#ifndef EXP_R2D2EXP_SRC_DIRECTION_H_
#define EXP_R2D2EXP_SRC_DIRECTION_H_

#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/misc/lv_area.h"
#include "pico/stdlib.h"
#include "Pattern.h"

enum DirectionType {
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_STOP
};

class Direction : public Pattern {
public:
	Direction();
	virtual ~Direction();

	virtual void init(lv_obj_t * parent);

	void setDirection(DirectionType d);

protected:
	//virtual void timerHandler(lv_timer_t * timer);

	virtual void drawGlif(uint8_t *data, lv_color_t c);
	virtual void drawGlif2C(uint8_t *data, lv_color_t c1, lv_color_t c2);
	virtual void timerHandler(lv_timer_t * timer);

private:
	static uint8_t LEFT[10];
	static uint8_t RIGHT[10];
	static uint8_t UP[10];
	static uint8_t DOWN[10];
	static uint8_t STOP[20];

	DirectionType xDirection= DIRECTION_STOP;

	int xPos = 0;
	int yPos = 0;
};

#endif /* EXP_R2D2EXP_SRC_DIRECTION_H_ */
