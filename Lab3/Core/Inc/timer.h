/*
 * timer.h
 *
 *  Created on: Oct 20, 2026
 *      Author: asus
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include "main.h"
#define TIMER_CYCLE 10
extern uint8_t timer_1s_flag;
extern uint8_t timer_2hz_flag;
extern uint8_t timer_scan_flag;

void set_timer_1s(void);
void set_timer_2hz(void);
void set_timer_scan(void);
void timer_run(void);
#endif /* INC_TIMER_H_ */
