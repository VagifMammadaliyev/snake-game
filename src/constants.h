#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WIN_X 200                   /* Window's initial X position */
#define WIN_Y 200                   /* Window's initial Y position */
#define WIN_H 800                   /* Window's initial height */
#define WIN_W 800                   /* Window's initial width */
#define MAX_CELL_X 20               /* Maximum cells for X dimension */
#define MAX_CELL_Y 20               /* Maximum cells for Y dimension */
#define CELL_H (WIN_H/MAX_CELL_Y)   /* Cell's height */
#define CELL_W (WIN_W/MAX_CELL_X)   /* Cell's width */
#define START_SIZE 5                /* Starting size of snake */
#define SPEED 10                    /* Game speed */
#define ADD_SPEED_AFTER 5           /* Add speed after eating food */

#endif
