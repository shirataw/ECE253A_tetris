#include "tetris.h"
#include "lcd.h"

// Update only the area affected by the action of current block;
void display_block_update () {
    // Print current block area with background color;
    // Print new block area with square color;
}

// Update the background area affected by elimination;
// The affected area is "dtc_range_bot" to "refresh_y_top";
void display_background_update () {

}

// Display the initialized game windows;
void display_initialization () {
    // Display the game background;

    // Display the sidebar;
    display_sidebar();
}

// Is this really necessary?
void display_game_over () {

}

// Display the sidebar window;
void display_sidebar () {
    // Display the next type;

    // Display the current score;

    // Display the highest score;
}