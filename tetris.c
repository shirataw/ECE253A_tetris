#include "tetris.h"

// Variable declarations;


// Initialization variables in INIT state;
void game_init () {
    // Initialize background;
    for (int y = 0; y < game_height; y ++) {
        for (int x = 0; x < game_width; x ++) {
            if ((x < boundary_left) || (x > boundary_right) || (y < boundary_bot)) background[x][y] = 1;
            else background[x][y] = 0;
        }
    }
    // Initialize next type;
    next_type = (enum block_type) (rand() % 8);
    generate();
}


// Generate next block;
void generate () {
    current_block.type = next_type;
    new_block.type = next_type;
    for (int i = 0; i < 4; i ++) {
        current_block.pos_x[i] = block_pos_init[next_type][i];
        new_block.pos_x[i] = block_pos_init[next_type][i];
        current_block.pos_y[i] = block_pos_init[next_type][i + 4];
        new_block.pos_y[i] = block_pos_init[next_type][i + 4];
    }
    // Generate the next type for side bar display;
    next_type = (enum block_type) (rand() % 8);
}

// Check legacy of left move;
int is_block_movable_left (void) {
    for (int i = 0; i < 4; i ++) {
        new_block.pos_x[i] = current_block.pos_x[i] + 1;
        if (background[new_block.pos_x[i]][new_block.pos_y[i]] == 1) return false;
    }
    return true;
}

// Check legacy of right move;
int is_block_movable_right (void) {
    for (int i = 0; i < 4; i ++) {
        new_block.pos_x[i] = current_block.pos_x[i] - 1;
        if (background[new_block.pos_x[i]][new_block.pos_y[i]] == 1) return false;
    }
    return true;
}

// Check legacy of block falling;
int is_block_fallable (void) {
    for (int i = 0; i < 4; i ++) {
        // Down button is pressed, check legacy of falling 2 squares
        // If not legal, check legacy of falling 1 square;
        if (btn_down == 1) {
            new_block.pos_y[i] = current_block.pos_y[i] - 2;
            if (background[new_block.pos_x[i]][new_block.pos_y[i]] == 1) {
                for (int j = 0; j < 4; j ++) {
                    new_block.pos_y[i] = current_block.pos_y[i] - 1;
                    if (background[new_block.pos_x[i]][new_block.pos_y[i]] == 1) return false;
                }
                return true;
            };
        }
        else {
            new_block.pos_y[i] = current_block.pos_y[i] - 1;
            if (background[new_block.pos_x[i]][new_block.pos_y[i]] == 1) return false;
        }
    }
    return true;
}

// Check legacy of rotation;
int is_block_rotatable (void) {
    // Variable to record the position bias between the current block and boundary;
    int bias_left = 0, bias_right = 0;
    // Rotate the current block without considering legacy;
    // If the current block type is SQUARE, no need to rotate;
    if (current_block.type != O_SHAPE) {
        // Get new x, y position;
        for (int i = 0; i < 4; i ++) {
            new_block.pos_x[i] = current_block.pos_y[i] - current_block.pos_y[0] + current_block.pos_x[i];
            new_block.pos_y[i] = current_block.pos_x[0] - current_block.pos_x[i] + current_block.pos_y[i];
        }
        // Check the x, y position of the rotated block;
        for (int i = 0; i < 4; i ++) {
            if ((boundary_left - current_block.pos_x[i]) > bias_left) bias_left = boundary_left - current_block.pos_x[i];
            if ((current_block.pos_x[i] - boundary_right) > bias_right) bias_right = current_block.pos_x[i] - boundary_right;
        }
        // If it is exceeding boundary, shift the rotated block back within;
        for (int i = 0; i < 4; i ++) {
            new_block.pos_x[i] + bias_left - bias_right;
        }
        // Rotation legacy checking;
        for (int i = 0; i < 4; i ++) {
            if (background[new_block.pos_x[i]][new_block.pos_y[i]] == 1) return false;
        }
        return true;
    }
}

// Copy next block to current block;
void block_copy () {
    current_block.type = new_block.type;
     for (int i = 0; i < 4; i ++) {
         current_block.pos_x[i] = new_block.pos_x[i];
         current_block.pos_y[i] = new_block.pos_y[i];
     }
}

// Merge the current block to background;
void block_merge () {
    // Update highest y position value and the background array;
    // Also get the detective range: elimination detection will only perform within
    // the detection range;
    dtc_range_bot = current_block.pos_y[0];
    dtc_range_top = current_block.pos_y[0];
    for (int i = 0; i < 4; i ++) {
        if (current_block.pos_y[i] > pos_y_highest) pos_y_highest = current_block.pos_y[i];
        background[current_block.pos_x[i]][current_block.pos_y[i]] = 1;
        if (current_block.pos_y[i] < dtc_range_bot) dtc_range_bot = current_block.pos_y[i];
        if (current_block.pos_y[i] > dtc_range_top) dtc_range_top = current_block.pos_y[i];
    }
}

// Game over detection, check if highest y larger than top celling;
int is_game_over () {
    if (pos_y_highest >= boundary_top) {
        pos_y_highest = boundary_bot;
        return true;
    }
}

// Check if eliminable;
int is_eliminable () {
    // In the worst case, 4 rows will be eliminated;
    // The game does not support the falling of hanging squares;
    row_elimination[4] = {0, 0, 0, 0};
    int flag_elimination = 1;
    clear_row_count = 0;
    // Store rows that needs to be eliminated;
    for (int y = dtc_range_bot; y < dtc_range_top + 1; y ++) {
        for (int x = boundary_left; x < boundary_right + 1; x ++) {
            flag_elimination &= background[x][y];
        }
        if (flag_elimination == 1) {
            row_elimination[clear_row_count] = y;
            clear_row_count ++;
        }
        flag_elimination = 1;
    }
    // Return true;
    for (int i = 0; i < 4; i ++) {
        if (row_elimination[i] == 1) return true;
    }
    return false;
}

// Perform elimination;
void elimination () {
    int row_to_replace;
    for (int y = dtc_range_bot; y < pos_y_highest; y ++) {
        row_to_replace = dtc_range_bot + 1;
        // Check if the row to replace is one of the eliminated rows;
        // If it is, check above row;
        for (int i = 0; i < clear_row_count; i ++) {
            if (row_to_replace == row_elimination[i]) row_to_replace++;
            else break;
        }
        for (int x = boundary_left; x < boundary_right + 1; x ++) {
            background[x][y] = background[x][row_to_replace];
        }
    }
    // Copy the highest y position and update;
    // The coped highest y is used to determine the update area of the background;
    refresh_y_top = pos_y_highest;
    pos_y_highest = pos_y_highest - clear_row_count;
    // Update game score;
    score += clear_row_count;
}
