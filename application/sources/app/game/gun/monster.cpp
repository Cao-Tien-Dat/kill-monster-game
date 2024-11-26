#include "monster.h"
#include "bullet.h"
#include "bang.h"
#include "game_border.h"
#include "scr_gun_game.h"

ar_game_meteoroid_t meteoroid[NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT + BOSS];
uint8_t gift_hit_count = 0;
uint8_t level3_hit_count = 1;
#define POINTS_FOR_GIFT 100

void check_and_spawn_gift() {
    static uint8_t last_score = 0; 
    static uint8_t gift_spawned = 0;

    if (ar_game_score > 0 && ar_game_score % POINTS_FOR_GIFT == 0 && last_score < ar_game_score) {
        if (!gift_spawned) {
            APP_DBG_SIG("Checking and spawning gift\n");
            for (uint8_t i = 0; i < NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT; i++) {
                if (meteoroid[i].visible == BLACK ) {
                    meteoroid[i].action_image = 8; // Äáº·t thÃ nh gift
                    meteoroid[i].visible = WHITE;   
                    APP_DBG_SIG("Gift spawned at index: %d\n", i);
                    gift_spawned = 1;
                    break; 
                }
            }
        }
    }
    
    if (gift_spawned && last_score < ar_game_score) {
        last_score = ar_game_score; 
    }

    if (ar_game_score > last_score && ar_game_score % POINTS_FOR_GIFT != 0) {
        gift_spawned = 0; 
    }
}


#define AR_GAME_CHECK_METEOROID_LEVEL_3() \
do { \
} while (0);

#define AR_GAME_METEOROID_RESET() \
do { \
    for (uint8_t i = 0; i < NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT; i++) { \
        meteoroid[i].x = (rand() % 39) + 130; \
        meteoroid[i].y = AXIS_Y_METEOROID_0 + (i % 5) * 10; \
        meteoroid[i].visible = WHITE; \
        meteoroid[i].action_image = rand() % 5 + 1; \
        meteoroid[i].hit_count = 1;  \
        meteoroid[i].direction = 1; \
    } \
    gift_hit_count = 0; \
    settingsetup.num_arrow = 0; \
    ar_game_score = score_now; \
} while (0);

void update_meteoroid_direction(ar_game_meteoroid_t* meteoroid) {
    if (meteoroid->y >= 45) {
        meteoroid->direction = -1;  
    } else if (meteoroid->y <= 0) {
        meteoroid->direction = 1;   
    }
}

#define SOME_SCORE_THRESHOLD 100 // Ngưỡng điểm số để tạo action_image 2

#define AR_GAME_METEOROID_SETUP() \
do { \
    for (uint8_t i = 0; i < NUM_METEOROIDS + NUM_METEOROIDS_III; i++) { \
        uint8_t is_unique; \
        do { \
            is_unique = 1; \
            meteoroid[i].y = AXIS_Y_METEOROID_0 + (i % 5) * 10; \
            meteoroid[i].x = (rand() % 39) + 130; \
            meteoroid[i].visible = WHITE; \
            for (uint8_t j = 0; j < i; j++) { \
                if (meteoroid[i].y == meteoroid[j].y && abs(meteoroid[i].x - meteoroid[j].x) < 15) { \
                    is_unique = 0; \
                    break; \
                } \
            } \
        } while (!is_unique); \
        if (ar_game_score >= SOME_SCORE_THRESHOLD) { \
            meteoroid[i].action_image = 2;  \
        } else { \
            do { \
                meteoroid[i].action_image = (rand() % 5) + 1; \
            } while (meteoroid[i].action_image == 2); \
        } \
        meteoroid[i].direction = 1; \
    } \
} while (0);


#define AR_GAME_METEOROID_RUN() \
do { \
    static uint8_t action_9_index = 255; \
    static uint8_t action_10_spawned = 0; \
    static uint8_t bomb_spawned = 0; \
    \
    for (uint8_t i = 0; i < (NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT + BOSS); i++) { \
        if (meteoroid[i].visible == WHITE) { \
            meteoroid[i].x -= settingsetup.meteoroid_speed; \
            update_meteoroid_direction(&meteoroid[i]);    \
            if (ar_game_score < 200) { \
                meteoroid[i].y = (meteoroid[i].action_image > 8) ? 0 : (meteoroid[i].y + meteoroid[i].direction * settingsetup.meteoroid_speed); \
            } else if (ar_game_score < 400) { \
                meteoroid[i].y = AXIS_Y_METEOROID_0 + (i % 5) * 10; \
            } else { \
                meteoroid[i].y = (meteoroid[i].action_image > 8) ? 0 : (meteoroid[i].y + meteoroid[i].direction * settingsetup.meteoroid_speed); \
            } \
        } \
    } \
    \
    check_and_spawn_gift(); \
    \
    if (ar_game_score >= 100 && !bomb_spawned) { \
        for (uint8_t i = 0; i < (NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT + BOSS); i++) { \
            if (meteoroid[i].visible == BLACK && meteoroid[i].action_image == 2) { \
                meteoroid[i].visible = WHITE; \
                meteoroid[i].x = (rand() % 39) + 130; \
                meteoroid[i].y = AXIS_Y_METEOROID_0 + (i % 5) * 10; \
                bomb_spawned = 1; \
                APP_DBG_SIG("Bomb spawned at index: %d\n", i); \
                break; \
            } \
        } \
    } \
    \
    if (ar_game_score >= 200) { \
        for (uint8_t i = 0; i < (NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT); i++) { \
            if (meteoroid[i].visible == BLACK && meteoroid[i].action_image != 6 && meteoroid[i].action_image != 8) { \
                meteoroid[i].action_image = 6; \
                meteoroid[i].visible = WHITE; \
                meteoroid[i].x = (rand() % 39) + 130; \
                meteoroid[i].y = AXIS_Y_METEOROID_0 + (i % 5) * 10; \
                break; \
            } \
        } \
    } \
    \
    if (ar_game_score >= 700) { \
        for (uint8_t i = 0; i < (NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT + BOSS); i++) { \
            if (meteoroid[i].action_image <= 8) { \
                meteoroid[i].visible = BLACK; \
            } \
        } \
        \
        if (action_9_index == 255) { \
            for (uint8_t i = 0; i < (NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT + BOSS); i++) { \
                if (meteoroid[i].visible == BLACK) { \
                    meteoroid[i].action_image = 9; \
                    meteoroid[i].visible = WHITE; \
                    meteoroid[i].x = (rand() % 39) + 130; \
                    meteoroid[i].y = 0; \
                    meteoroid[i].x -= settingsetup.meteoroid_speed; \
                    action_9_index = i; \
                    break; \
                } \
            } \
        } \
        \
        if (action_9_index != 255 && meteoroid[action_9_index].x <= 70 && !action_10_spawned) { \
            for (uint8_t j = 0; j < (NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT + BOSS); j++) { \
                if (meteoroid[j].visible == BLACK) { \
                    meteoroid[j].action_image = 10; \
                    meteoroid[j].visible = WHITE; \
                    meteoroid[j].x = 50; \
                    meteoroid[j].y = meteoroid[action_9_index].y; \
                    action_10_spawned = 1; \
                    meteoroid[action_9_index].visible = BLACK; \
                    action_9_index = 255; \
                    break; \
                } \
            } \
        } \
    } \
} while (0);

#define AR_GAME_METEOROID_DETONATOR() \
do { \
    for (uint8_t s = 0; s < NUM_BANG; s++) { \
        for (uint8_t i = 0; i < NUM_METEOROIDS + NUM_METEOROIDS_III + GIFT; i++) { \
            if (meteoroid[i].visible == WHITE) { \
                for (uint8_t j = 0; j < MAX_NUM_ARROW; j++) { \
                    if (meteoroid[i].x < (arrow[j].x + SIZE_BITMAP_ARROW_X - 3) && \
                        meteoroid[i].x + SIZE_BITMAP_METEOROIDS_X_1 > arrow[j].x && \
                        meteoroid[i].y < (arrow[j].y + SIZE_BITMAP_ARROW_Y) && \
                        meteoroid[i].y + SIZE_BITMAP_METEOROIDS_Y_1 > arrow[j].y) { \
                        APP_PRINT("%d\n", meteoroid[i].action_image); \
                        if (meteoroid[i].action_image == 8) { \
                            meteoroid[i].action_image = 7; \
                            settingsetup.num_arrow++; \
                            arrow[j].visible = BLACK; \
                            arrow[j].x = 0; \
                            ar_game_score += 10; \
                            continue; \
                        } \
                        if (meteoroid[i].action_image == 6) { \
                            meteoroid[i].hit_count++; \
                            if (meteoroid[i].hit_count >= 2) { \
                                meteoroid[i].action_image = 5; \
                            } \
                            settingsetup.num_arrow++; \
                            arrow[j].visible = BLACK; \
                            arrow[j].x = 0; \
                            bang[i].visible = WHITE; \
                            bang[i].x = meteoroid[i].x - 5; \
                            bang[i].y = meteoroid[i].y + 2; \
                            ar_game_score += 10; \
                            continue; \
                        } \
                        if (meteoroid[i].action_image == 2) { \
                            arrow[j].visible = BLACK; \
                            arrow[j].x = 0; \
                            bang[i].visible = WHITE; \
                            bang[i].x = meteoroid[i].x - 5; \
                            bang[i].y = meteoroid[i].y + 2; \
                            task_post_pure_msg(AR_GAME_SCREEN_ID, AR_GAME_RESET); \
                            break; \
                        }\
                        if (meteoroid[i].action_image == 7) { \
                            for (uint8_t k = 0; k < NUM_METEOROIDS + NUM_METEOROIDS_III; k++) { \
                                meteoroid[k].visible = BLACK; \
                                bang[k].visible = WHITE; \
                                bang[k].x = meteoroid[k].x - 5; \
                                bang[k].y = meteoroid[k].y + 2; \
                                meteoroid[k].x = (rand() % 39) + 130; \
                                meteoroid[k].action_image = rand() % 4 + 1; \
                            } \
                            arrow[j].visible = BLACK; \
                            arrow[j].x = 0; \
                            settingsetup.num_arrow++; \
                            ar_game_score += 30; \
                            BUZZER_PlayTones(tones_BUM); \
                            break; \
                        } \
                        /* Xử lý nổ thiên thạch thông thường */ \
                        if (meteoroid[i].action_image == 9 || meteoroid[i].action_image == 10) { \
                            meteoroid[i].visible = WHITE; /* Thiên thạch 9 và 10 trở thành màu đen */ \
                            bang[i].visible = WHITE; \
                            bang[i].x = meteoroid[i].x - 5; \
                            bang[i].y = meteoroid[i].y + 2; \
                            arrow[j].visible = BLACK; \
                            arrow[j].x = 0; \
                            ar_game_score += 20; /* Tăng điểm nhiều hơn cho việc bắn thiên thạch cấp cao */ \
                            BUZZER_PlayTones(tones_BUM); \
                            continue; \
                        } \
                        /* Xử lý nổ thiên thạch thông thường */ \
                        meteoroid[i].visible = BLACK; \
                        arrow[j].visible = BLACK; \
                        bang[i].visible = WHITE; \
                        bang[i].x = meteoroid[i].x - 5; \
                        bang[i].y = meteoroid[i].y + 2; \
                        arrow[j].x = 0; \
                        meteoroid[i].x = (rand() % 39) + 130; \
                        settingsetup.num_arrow++; \
                        ar_game_score += 10; \
                        BUZZER_PlayTones(tones_BUM); \
                    } \
                } \
            } \
        } \
    } \
} while (0);


void ar_game_meteoroid_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case AR_GAME_METEOROID_SETUP: {
        APP_PRINT("%d\n", ar_game_score);
        APP_DBG_SIG("AR_GAME_METEOROID_SETUP\n");
        AR_GAME_METEOROID_SETUP();
        break;
    }

    case AR_GAME_CHECK_METEOROID_LEVEL_3: {
        APP_DBG_SIG("AR_GAME_CHECK_METEOROID_LEVEL_3\n");
        AR_GAME_CHECK_METEOROID_LEVEL_3();
        break;
    }

    case AR_GAME_METEOROID_RUN: {
        APP_DBG_SIG("AR_GAME_METEOROID_RUN\n");
        AR_GAME_METEOROID_RUN();
        break;
    }

    case AR_GAME_METEOROID_DETONATOR: {
        APP_DBG_SIG("AR_GAME_METEOROID_DETONATOR\n");
        AR_GAME_METEOROID_DETONATOR();
        break;
    }

    default:
        break;
    }
}