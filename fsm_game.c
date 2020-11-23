#include "tetris.h"

void fsm_game() {
    switch (STATE_GAME) {
        case INIT: {
            // Use rotate button as the start button;
            if (btn_rotate == 1) {
                // Initialize game upon start button is pressed;
                game_init();
                // Print the initialized game image;
                display_initialization();
                STATE_GAME = FALL;
            }
        }
        case FALL: {
            if (btn_pause == 1) {
                STATE_GAME = PAUSE;
            }
            else if (tick == 1) {
                // Falling legacy checking;
                // If the falling is legal, print the updated image and copy new block to current block;
                if (is_block_fallable() == true) {
                    display_block_update();
                    block_copy();
                }
                // If illegal, merge the current block to the background;
                else {
                    block_merge();
                    // Check if game is over;
                    if (is_game_over() == true) {
                        // Record current score;
                        if (score > highest_score) highest_score = score;
                        // Display game over image;
                        display_game_over();
                        STATE_GAME = OVER;
                    }
                    // If game is not over, check if there's any elimination to perform;
                    else {
                        // Perform elimination, update background and print new display;
                        if (is_eliminable() == true) {
                            elimination();
                            display_background_update();
                        }
                        // If no elimination can happen, do nothing;
                        // Generate next block;
                        generate();
                        // Update side bar;
                        display_sidebar();
                    }
                }
            }
            else if (btn_left == 1) {
                if (is_block_movable_left() == true) {
                    display_block_update();
                    block_copy();
                }
            }
            else if (btn_right == 1) {
                if (is_block_movable_right() == true) {
                    display_block_update();
                    block_copy();
                }
            }
            else if (btn_rotate == 1) {
                if (is_block_rotatable() == true) {
                    display_block_update();
                    block_copy();
                }
            }
        }
        case PAUSE: {
            // Use rotate button as the start button;
            if (btn_rotate == 1) {
                STATE_GAME = FALL;
            }
        }
        case OVER: {
            if (btn_rotate == 1) {
                // Initialize game upon start button is pressed;
                game_init();
                // Print the initialized game image;
                display_initialization();
                STATE_GAME = FALL;
            }
        }
    }
}