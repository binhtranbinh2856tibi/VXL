/*
 * timer.c
 *
 *  Created on: Oct 20, 2026
 *      Author: asus
 */
#include "main.h"
#include "timer.h"
#include "input_reading.h"
uint8_t timer_1s_flag = 0;
static int timer_1s_counter = 0;

uint8_t timer_2hz_flag = 0;
static int timer_2hz_counter = 0;

uint8_t timer_scan_flag = 0;
static int timer_scan_counter = 0;
void set_timer_1s(void) {
    timer_1s_counter = 1000 / TIMER_CYCLE; // 1000ms = 1s
    timer_1s_flag = 0;
}

void set_timer_2hz(void) {
    timer_2hz_counter = 250 / TIMER_CYCLE; // 250ms đảo trạng thái 1 lần = 2 Hz
    timer_2hz_flag = 0;
}

void set_timer_scan(void) {
    timer_scan_counter = 10 / TIMER_CYCLE; // Quét nhanh mỗi 10ms để 4 LED sáng tĩnh đồng thời
    timer_scan_flag = 0;
}

void timer_run(void) {
    if (timer_1s_counter > 0) {
        timer_1s_counter--;
        if (timer_1s_counter <= 0) {
            timer_1s_flag = 1;
            timer_1s_counter = 1000 / TIMER_CYCLE;
        }
    }

    if (timer_2hz_counter > 0) {
        timer_2hz_counter--;
        if (timer_2hz_counter <= 0) {
            timer_2hz_flag = 1;
            timer_2hz_counter = 250 / TIMER_CYCLE;
        }
    }

    if (timer_scan_counter > 0) {
        timer_scan_counter--;
        if (timer_scan_counter <= 0) {
            timer_scan_flag = 1;
            timer_scan_counter = 10 / TIMER_CYCLE; // Nạp lại 10ms
        }
    }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2) {
        button_reading();
        timer_run();
    }
}

