/*
 * input_processing.h
 *
 *  Created on: Oct 20, 2026
 *      Author: asus
 */
#include "main.h"
#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_
#define MODE_NORMAL     1
#define MODE_MODIFY_RED 2
#define MODE_MODIFY_YEL 3
#define MODE_MODIFY_GRE 4
void fsm_mode_processing(void);
void fsm_traffic_processing(void);
void fsm_display_processing(void);

#endif /* INC_INPUT_PROCESSING_H_ */
