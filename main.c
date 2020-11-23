# include "tetris.h"
# include "peripheral.h"




int main () {
    // Initialize type;
    enum block_type next_type = T_SHAPE;

    enum state_game STATE_GAME = INIT;

    // Initialize score and highest score;
    int score = 0, highest_score = 0;

    // Initialize current block and new block;
    struct block current_block, new_block;

    peripheral_init();
    fsm_game();
    return 0;
}