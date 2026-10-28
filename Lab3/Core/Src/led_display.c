/*
 * led_display.c
 *
 *  Created on: Oct 20, 2026
 *      Author: asus
 */
#include "led_display.h"
static const uint8_t seg_code[10] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};

void display7SEG(uint8_t num) {
    uint8_t pattern = seg_code[num % 10];
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (pattern & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (pattern & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (pattern & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (pattern & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (pattern & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (pattern & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (pattern & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void update7SEG(uint8_t index, uint8_t val1, uint8_t val2) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);

    switch (index) {
        case 0:
            display7SEG(val1 % 10); // LED 1: hàng đơn vị
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
            break;
        case 1:
            display7SEG(val1 / 10); // LED 2: hàng chục
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
            break;
        case 2:
            display7SEG(val2 % 10); // LED 3 (EN3): hàng đơn vị
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
            break;
        case 3:
            display7SEG(val2 / 10); // LED 4 (EN4): hàng chục
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}

void clear_all_leds(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
                             GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
}

void set_traffic_lights(uint8_t r1, uint8_t y1, uint8_t g1, uint8_t r2, uint8_t y2, uint8_t g2) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, r1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, y1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, g1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, r2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, y2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, g2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void toggle_red_leds(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_4);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
}

void toggle_amber_leds(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_5);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6, GPIO_PIN_RESET);
}

void toggle_green_leds(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3 | GPIO_PIN_6);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);
}
