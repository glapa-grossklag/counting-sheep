#include "resources.h"

#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ENOUGH 64
#define DELAY  15000
#define WIDTH  getmaxx(stdscr)
#define HEIGHT getmaxy(stdscr)

int main() {
    char sheepstr[ENOUGH];

    // Setup ncurses
    initscr();
    curs_set(false);
    noecho();
    timeout(0);

    for (unsigned sheep = 1;; sheep += 1) {
        unsigned starting_height = random() % HEIGHT;

        // Determine if the sheep moves left-to-right or right-to-left
        bool isleft = random() % 2;
        unsigned start, stop;
        int step;
        if (isleft) {
            start = WIDTH - 6;
            stop = 0;
            step = -1;
        } else {
            start = 0;
            stop = WIDTH - 6;
            step = 1;
        }

        for (unsigned x = start; x != stop; x += step) {
            // Curve
            int y = -(HEIGHT / 4) * sin((M_PI / WIDTH) * x) + starting_height;

            // Update sheep position
            if (isleft) {
                mvprintw(y, x, sheep_left[0]);
                mvprintw(y + 1, x, sheep_left[1]);
            } else {
                mvprintw(y, x, sheep_right[0]);
                mvprintw(y + 1, x, sheep_right[1]);
            }

            // Update number of sheep
            sprintf(sheepstr, "%u", sheep);
            mvprintw(HEIGHT - 1, WIDTH / 2, sheepstr);

            // Update screen
            refresh();
            usleep(DELAY);
            clear();

            // Quit?
            if (getch() == 'q') {
                endwin();
                return 0;
            }
        }
    }

    endwin();
    return 0;
}
