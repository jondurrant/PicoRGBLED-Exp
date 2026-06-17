/*
 * main.cpp
 *
 *  Created on: 16 Jun 2026
 *      Author: jondurrant
 */


#include <stdio.h>
#include "pico/stdlib.h"

#include <PicoLed.hpp>

#define LED_PIN 2
#define LED_LENGTH (16*10)


uint8_t colors[6][3] = {
		{255, 0, 0},
		{255, 255, 0},
		{0, 255, 0},
		{0, 255, 255},
		{0,0, 255},
		{255,0,255}
};


int main(){
    stdio_init_all();
    sleep_ms(5000);

    // 0. Initialize LED strip
    printf("0. Initialize LED strip\n");
    auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LED_PIN, LED_LENGTH, PicoLed::FORMAT_RGB);
    ledStrip.setBrightness(64);
    printf("1. Clear the strip!\n");

    // 1. Set all LEDs to red!
    printf("1. Set all LEDs to red!\n");
    ledStrip.fill( PicoLed::RGB(255, 0, 0) );

    for (;;){
    	for (int i=0; i < 6; i++){
    		 ledStrip.fill( PicoLed::RGB(colors[i][0], colors[i][1], colors[i][2]) );
    		 for (int j=0; j < 10; j++){
    			 ledStrip.show();
				sleep_ms(500);
    		}
    	}
    }

}


