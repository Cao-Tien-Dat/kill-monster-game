#include "game_border.h"

#include "monster.h"
#include "game_gun.h"

ar_game_border_t border;
uint32_t ar_game_score = 10;

#define AR_GAME_BORDER_SETUP() \
do { \
    border.x = AXIS_X_BORDER; \
    border.visible = WHITE; \
    border.action_image = 0; \
} while (0);

#define AR_GAME_LEVEL_UP() \
do { \
    if (ar_game_score%200 == 0) { \
        /* border.x += 10; */\
        if (settingsetup.meteoroid_speed < 10) { \
            settingsetup.meteoroid_speed = settingsetup.meteoroid_speed; \
            ar_game_score += 10; \
        } \
    } \
} while(0);

#define AR_GAME_CHECK_GAME_OVER() \
do { \
    for (uint8_t i = 0; i < NUM_METEOROIDS ; i++) { \
        if (meteoroid[i].x <= (border.x - 3)) { \
            if (meteoroid[i].action_image == 2) { \
                meteoroid[i].visible = BLACK; \
            } else { \
                task_post_pure_msg(AR_GAME_SCREEN_ID, AR_GAME_RESET); \
            } \
        } \
    } \
    for (uint8_t i = NUM_METEOROIDS; i < (NUM_METEOROIDS + NUM_METEOROIDS_III); i++) { \
        if (meteoroid[i].x <= (border.x - 3)) { \
            if (meteoroid[i].action_image == 2) { \
                meteoroid[i].visible = BLACK; \
            } else { \
                task_post_pure_msg(AR_GAME_SCREEN_ID, AR_GAME_RESET); \
            } \
        } \
    } \
} while(0);



#define AR_GAME_BORDER_RESET() \
do { \
    border.x = AXIS_X_BORDER; \
    border.visible = BLACK; \
} while (0);

void ar_game_border_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case AR_GAME_BORDER_SETUP: {
        APP_DBG_SIG("AR_GAME_BORDER_SETUP\n");
        AR_GAME_BORDER_SETUP();
    }
        break;

    case AR_GAME_LEVEL_UP: {
        APP_DBG_SIG("AR_GAME_LEVEL_UP\n");
        AR_GAME_LEVEL_UP();
    }
        break;

    case AR_GAME_CHECK_GAME_OVER: {
        APP_DBG_SIG("AR_GAME_CHECK_GAME_OVER\n");
        AR_GAME_CHECK_GAME_OVER();
    }
        break;

    case AR_GAME_BORDER_RESET: {
        APP_DBG_SIG("AR_GAME_BORDER_RESET\n");
        AR_GAME_BORDER_RESET();
    }
        break;

    default:
        break;
    }
}