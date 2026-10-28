#include "input_processing.h"
#include "input_reading.h"
#include "led_display.h"
#include "main.h"
#include "timer.h"
static uint8_t red_time = 5;
static uint8_t amber_time = 2;
static uint8_t green_time = 3;

static uint8_t temp_time = 0;

static uint8_t current_mode = MODE_NORMAL;

enum TrafficState {
    ROAD1_RED_ROAD2_GREEN,
    ROAD1_RED_ROAD2_AMBER,
    ROAD1_GREEN_ROAD2_RED,
    ROAD1_AMBER_ROAD2_RED
};

static enum TrafficState trafficState = ROAD1_RED_ROAD2_GREEN;
static int countdown_road1 = 5;
static int countdown_road2 = 3;
static uint8_t current_scan_digit = 0;
void fsm_mode_processing(void) {
    if (is_button_pressed_single(0)) {
        current_mode++;
        if (current_mode > MODE_MODIFY_GRE) {
            current_mode = MODE_NORMAL;
            trafficState = ROAD1_RED_ROAD2_GREEN;
            countdown_road1 = red_time;
            countdown_road2 = green_time;
            set_timer_1s();
        }

        clear_all_leds();
        set_timer_2hz();
        if (current_mode == MODE_MODIFY_RED) temp_time = red_time;
        if (current_mode == MODE_MODIFY_YEL) temp_time = amber_time;
        if (current_mode == MODE_MODIFY_GRE) temp_time = green_time;
    }

    switch (current_mode) {
        case MODE_NORMAL:
            fsm_traffic_processing();
            break;

        case MODE_MODIFY_RED:
            if (is_button_pressed_single(1)) {
                temp_time++;
                if (temp_time > 99) temp_time = 1;
            }
            if (is_button_pressed_single(2)) {
                red_time = temp_time;
                // Nếu tăng đỏ lên thì xanh tự động tăng cho tổng xanh + vàng vẫn bằng đỏ
                if (red_time > amber_time) {
                    green_time = red_time - amber_time;
                } else {
                    // Nếu đỏ nhỏ hơn hoặc bằng vàng, xanh giữ tối thiểu là 1 và đỏ tự động gán lại
                    green_time = 1;
                    red_time = green_time + amber_time;
                    temp_time = red_time;
                }
            }
            if (timer_2hz_flag) {
                timer_2hz_flag = 0;
                toggle_red_leds();
            }
            break;

        case MODE_MODIFY_YEL:
            if (is_button_pressed_single(1)) {
                temp_time++;
                if (temp_time > 99) temp_time = 1;
            }
            if (is_button_pressed_single(2)) {
                amber_time = temp_time;
                // Khi không chỉnh đỏ (giữ nguyên đỏ), nếu tăng vàng thì giảm xanh xuống để tổng vàng + xanh = đỏ
                if (amber_time < red_time) {
                    green_time = red_time - amber_time;
                } else {
                    // Nếu tăng vàng vượt quá mức đỏ (xanh chạm mức tối thiểu 1s), tự động tăng đỏ lên
                    green_time = 1;
                    red_time = green_time + amber_time;
                    if (red_time > 99) {
                        red_time = 99;
                        amber_time = red_time - green_time; // 98
                        temp_time = amber_time;
                    }
                }
            }
            if (timer_2hz_flag) {
                timer_2hz_flag = 0;
                toggle_amber_leds();
            }
            break;

        case MODE_MODIFY_GRE:
            if (is_button_pressed_single(1)) {
                temp_time++;
                if (temp_time > 99) temp_time = 1;
            }
            if (is_button_pressed_single(2)) {
                green_time = temp_time;
                // Khi không chỉnh đỏ (giữ nguyên đỏ), nếu tăng xanh thì giảm vàng xuống để tổng xanh + vàng = đỏ
                if (green_time < red_time) {
                    amber_time = red_time - green_time;
                } else {
                    // Nếu tăng xanh vượt quá mức đỏ (vàng chạm mức tối thiểu 1s), tự động tăng đỏ lên
                    amber_time = 1;
                    red_time = green_time + amber_time;
                    if (red_time > 99) {
                        red_time = 99;
                        green_time = red_time - amber_time; // 98
                        temp_time = green_time;
                    }
                }
            }
            if (timer_2hz_flag) {
                timer_2hz_flag = 0;
                toggle_green_leds();
            }
            break;

        default:
            break;
    }
}
void fsm_traffic_processing(void) {
    switch (trafficState) {
        case ROAD1_RED_ROAD2_GREEN:
            set_traffic_lights(1, 0, 0, 0, 0, 1);
            if (timer_1s_flag) {
                countdown_road1--;
                countdown_road2--;
                if (countdown_road2 <= 0) {
                    trafficState = ROAD1_RED_ROAD2_AMBER;
                    countdown_road2 = amber_time;
                }
            }
            break;

        case ROAD1_RED_ROAD2_AMBER:
            set_traffic_lights(1, 0, 0, 0, 1, 0);
            if (timer_1s_flag) {
                countdown_road1--;
                countdown_road2--;
                if (countdown_road1 <= 0 || countdown_road2 <= 0) {
                    trafficState = ROAD1_GREEN_ROAD2_RED;
                    countdown_road1 = green_time;
                    countdown_road2 = red_time;
                }
            }
            break;

        case ROAD1_GREEN_ROAD2_RED:
            set_traffic_lights(0, 0, 1, 1, 0, 0);
            if (timer_1s_flag) {
                countdown_road1--;
                countdown_road2--;
                if (countdown_road1 <= 0) {
                    trafficState = ROAD1_AMBER_ROAD2_RED;
                    countdown_road1 = amber_time;
                }
            }
            break;

        case ROAD1_AMBER_ROAD2_RED:
            set_traffic_lights(0, 1, 0, 1, 0, 0);
            if (timer_1s_flag) {
                countdown_road1--;
                countdown_road2--;
                if (countdown_road1 <= 0 || countdown_road2 <= 0) {
                    trafficState = ROAD1_RED_ROAD2_GREEN;
                    countdown_road1 = red_time;
                    countdown_road2 = green_time;
                }
            }
            break;
    }

    if (timer_1s_flag) {
        timer_1s_flag = 0;
    }
}

void fsm_display_processing(void) {
    if (timer_scan_flag) {
        timer_scan_flag = 0;
        if (current_mode == MODE_NORMAL) {
            // Mode 1: Cụm LED 1, 2 hiện Tuyến 1, Cụm LED 3, 4 hiện Tuyến 2
            update7SEG(current_scan_digit, countdown_road1, countdown_road2);
        } else {
            // Mode 2, 3, 4: Cụm LED 1, 2 hiện Mode, Cụm LED 3, 4 hiện Giá trị
            update7SEG(current_scan_digit, current_mode, temp_time);
        }
        current_scan_digit = (current_scan_digit + 1) % 4;
    }
}
