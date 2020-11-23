// This is the header file for the main functions in tetris.c
// The peripheral devices are declared in perepheral.h
#include <stdio.h>
#include <stdlib.h>

// Gaming boundary;
// Game width is the number of squares per line, so as game height;
#define game_width 14
#define game_height 31
// The boundary axis;
#define boundary_left 2
#define boundary_right 11
#define boundary_bot 2
#define boundary_top 27
// Button value definition;
#define rotate 1
#define left_click 2
#define right_click 4
#define down 8
#define pause 16

// Game constants;

// Different shape of blocks;
enum block_type {
    T_SHAPE = 0, J_SHAPE, L_SHAPE, I_SHAPE, O_SHAPE, Z_SHAPE, S_SHAPE
};

// Return value of functions;
enum function_return {
    true, false
};

// The initial position of a new block;
extern int block_pos_init[7][4] = {
        {7, 7, 6, 8, 27, 28, 27, 27}, // T shape;
        {7, 7, 7, 6, 28, 27, 29, 27}, // J shape;
        {7, 7, 7, 8, 28, 27, 29, 27}, // L shape;
        {7, 5, 6, 8, 27, 27, 27, 27}, // I shape;
        {7 ,6, 7, 6, 27, 27, 28, 28}, // O shape;
        {7, 6, 7, 8, 27, 28, 28, 27}, // Z shape;
        {7, 6, 7, 8, 27, 27, 28, 28}  // S shape;
};

// FSM states;
enum state_game {
    INIT, FALL, OVER, PAUSE
};

// Signals from peripheral devices;

// Button value read from GPIO interrupt handler;
extern int btn_rotate, btn_left, btn_right, btn_down, btn_pause;

// Timer event;
extern int tick;








// Function variables;

// Game FSM state variable;
extern enum state_game STATE_GAME;


// The structure of the current moving block;
// Including type, x and y position of each small square;
// The point (pos_x[0], pos_y[0]) is the rotation center;
struct block {
    int type;
    int pos_x[4];
    int pos_y[4];
};
extern struct block current_block, new_block;

// The game background with existing bricks and boundary;
extern int background[game_width][game_height];

// Current highest square's y position;
extern int pos_y_highest;

// Active detection range for elimination detection;
extern int dtc_range_bot, dtc_range_top;

// Variable for elimination;
extern int row_elimination[4];
extern int clear_row_count;

// Refresh top boundary for display;
extern int refresh_y_top;

// Type of the next block;
extern enum block_type next_type;

// Game score and highest score;
extern int score;
extern int highest_score;

// External functions;
extern void game_init();
extern void generate ();
extern int is_block_movable_left ();
extern int is_block_movable_right ();
extern int is_block_fallable ();
extern int is_block_rotatable ();
extern void block_copy ();
extern void block_merge ();
extern int is_game_over ();
extern int is_eliminable ();
extern void elimination ();

extern void fsm_game ();



// Printing functions;
extern void display_block_update ();

extern void display_background_update ();

extern void display_initialization ();

extern void display_game_over ();

extern void display_sidebar ();




