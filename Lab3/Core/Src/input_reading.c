/*
 * input_reading.c
 *
 *  Created on: Oct 20, 2026
 *      Author: asus
 */
#include "input_reading.h"

#define DURATION_FOR_AUTO_INCREASING 100
#define BUTTON_IS_PRESSED            GPIO_PIN_RESET
#define BUTTON_IS_RELEASED           GPIO_PIN_SET

static GPIO_TypeDef* BUTTON_PORT[NO_OF_BUTTONS] = {GPIOB, GPIOB, GPIOB};
static uint16_t BUTTON_PIN[NO_OF_BUTTONS] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2};

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];
static uint8_t flagForButtonPressSingle[NO_OF_BUTTONS];
void button_reading(void) {
    for (uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON_PORT[i], BUTTON_PIN[i]);

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
        	if ((buttonBuffer[i] == BUTTON_IS_RELEASED) && (debounceButtonBuffer1[i] == BUTTON_IS_PRESSED)) {
        	                flagForButtonPressSingle[i] = 1;
        	            }
            buttonBuffer[i] = debounceButtonBuffer1[i];

            if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
                if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                    counterForButtonPress1s[i]++;
                } else {
                    flagForButtonPress1s[i] = 1;
                }
            } else {
                counterForButtonPress1s[i] = 0;
                flagForButtonPress1s[i] = 0;
            }
        }
    }
}

unsigned char is_button_pressed(unsigned char index) {
    if (index >= NO_OF_BUTTONS) return 0;
    return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}
unsigned char is_button_pressed_single(unsigned char index) {
    if (index >= NO_OF_BUTTONS) return 0;
    if (flagForButtonPressSingle[index] == 1) {
        flagForButtonPressSingle[index] = 0;
        return 1;
    }
    return 0;
}
unsigned char is_button_pressed_1s(unsigned char index) {
    if (index >= NO_OF_BUTTONS) return 0;
    return (flagForButtonPress1s[index] == 1);
}

