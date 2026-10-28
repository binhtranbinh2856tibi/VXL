/*
 * led_display.h
 *
 *  Created on: Oct 20, 2026
 *      Author: asus
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_
#include "main.h"
void display7SEG(uint8_t num);
void update7SEG(uint8_t index, uint8_t val1, uint8_t val2);
void clear_all_leds(void);
void set_traffic_lights(uint8_t r1, uint8_t y1, uint8_t g1, uint8_t r2, uint8_t y2, uint8_t g2);
void toggle_red_leds(void);
void toggle_amber_leds(void);
void toggle_green_leds(void);

#endif /* INC_LED_DISPLAY_H_ */
