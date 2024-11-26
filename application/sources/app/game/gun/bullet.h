#ifndef __AR_GAME_ARROW_H__
#define __AR_GAME_ARROW_H__

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "buzzer.h"
#include "scr_gun_game.h"

#define MAX_NUM_ARROW       (10)
#define MAX_AXIS_X_ARROW    (120)
#define SIZE_BITMAP_ARROW_X (7)
#define SIZE_BITMAP_ARROW_Y (6)

typedef struct {
    bool visible;
    uint32_t x, y;
    uint8_t action_image;
} ar_game_arrow_t;

extern ar_game_arrow_t arrow[MAX_NUM_ARROW];

#endif //__AR_GAME_ARROW_H__