#ifndef __AR_GAME_METEOROID_H__
#define __AR_GAME_METEOROID_H__

#include <stdio.h>
#include <stdbool.h> // Thêm thư viện cho kiểu bool

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "buzzer.h"
#include "scr_archery_game.h"

#define NUM_METEOROIDS              (4)
#define NUM_METEOROIDS_III          (3)
#define GIFT                        (2) 
#define BOSS                        (2)

#define SIZE_BITMAP_METEOROIDS_X_1   (12)
#define SIZE_BITMAP_METEOROIDS_Y_1   (8)

#define SIZE_BITMAP_METEOROIDS_X_3  (10)
#define SIZE_BITMAP_METEOROIDS_Y_3  (10)

#define SIZE_BITMAP_METEOROIDS_X_2  (9)
#define SIZE_BITMAP_METEOROIDS_Y_2  (10)

#define SIZE_BITMAP_METEOROIDS_X_5  (11)
#define SIZE_BITMAP_METEOROIDS_Y_5  (8)

#define SIZE_BITMAP_METEOROIDS_X_6  (20)
#define SIZE_BITMAP_METEOROIDS_Y_6  (10)

#define AXIS_Y_METEOROID_0          (0)
#define AXIS_Y_METEOROID_1          (12)
#define AXIS_Y_METEOROID_2          (22)
#define AXIS_Y_METEOROID_3          (32)
#define AXIS_Y_METEOROID_4          (42)

// Cấu trúc dữ liệu meteoroid với thêm thuộc tính direction và hit_count
typedef struct {
    bool visible;
    uint32_t x, y;
    uint8_t action_image;
    int8_t direction;  // Hướng di chuyển: 1 là lên, -1 là xuống
    uint8_t hit_count; // Số lần bị bắn
} ar_game_meteoroid_t;

// Khai báo các biến và hàm sử dụng
extern ar_game_meteoroid_t meteoroid[NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT + BOSS];

// Hàm cập nhật hướng di chuyển của meteoroid
void update_meteoroid_direction(ar_game_meteoroid_t* meteoroid);
void check_and_spawn_gift();
void check_and_spawn_boom() ;
#endif // __AR_GAME_METEOROID_H__
