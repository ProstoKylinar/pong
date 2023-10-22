#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LENGTH 80
#define WIDTH 25
#define RACKET_POSITION 13
#define BALL_POSITION_X (LENGTH / 2)
#define BALL_POSITION_Y (WIDTH / 2 + WIDTH % 2)

void init_field(int score_1, int score_2, int ball_x, int ball_y, int racket_1, int racket_2);
int move_racket_1(char temp, int racket_1);
int move_racket_2(char temp, int racket_2);
int random_vector();
void screen_preparation();
void score_printer(int score_1);

int main() {
    int racket_1, racket_2, ball_x, ball_y, score_1, score_2, dir_x, dir_y;
    racket_1 = racket_2 = RACKET_POSITION, ball_x = BALL_POSITION_X, ball_y = BALL_POSITION_Y,
    score_1 = score_2 = 0, dir_x = random_vector(), dir_y = random_vector();
    screen_preparation();
    init_field(score_1, score_2, ball_x, ball_y, racket_1, racket_2);
    if (getchar()) {
        refresh();
        usleep(500000);
        while (1) {
            char temp;
            clear();
            usleep(74100);
            init_field(score_1, score_2, ball_x, ball_y, racket_1, racket_2);
            temp = getch();
            racket_1 = move_racket_1(temp, racket_1);
            racket_2 = move_racket_2(temp, racket_2);
            if (ball_x < 3) {
                if (racket_1 != ball_y && (racket_1 - 1) != ball_y && (racket_1 + 1) != ball_y &&
                    (racket_1 - 2) != ball_y && (racket_1 + 2) != ball_y) {
                    score_2 += 1;
                    ball_x = BALL_POSITION_X;
                    ball_y = BALL_POSITION_Y;
                    dir_x = random_vector();
                    dir_y = random_vector();
                } else if (racket_1 == ball_y || racket_1 - 1 == ball_y || racket_1 + 1 == ball_y ||
                           racket_1 + 1 == ball_y + dir_y || racket_1 - 1 == ball_y + dir_y)
                    dir_x = -dir_x;
            } else if (ball_x > 78) {
                if (racket_2 != ball_y && (racket_2 - 2) != ball_y && (racket_2 + 2) != ball_y &&
                    (racket_2 - 1) != ball_y && (racket_2 + 1) != ball_y) {
                    score_1 += 1;
                    ball_x = BALL_POSITION_X;
                    ball_y = BALL_POSITION_Y;
                    dir_x = random_vector();
                    dir_y = random_vector();
                } else if (racket_2 == ball_y || racket_2 - 1 == ball_y || racket_2 + 1 == ball_y ||
                           racket_2 + 1 == ball_y + dir_y || racket_2 - 1 == ball_y + dir_y)
                    dir_x = -dir_x;
            } else if (ball_y == 1 || ball_y == 25)
                dir_y = -dir_y;
            ball_x += dir_x;
            ball_y += dir_y;
            if (score_1 == 21 || score_2 == 21) break;
        }
    }
    endwin();
    score_printer(score_1);
    return 0;
}

void init_field(int score_1, int score_2, int ball_x, int ball_y, int racket_1, int racket_2) {
    printw("%d || %d\n", score_1, score_2);
    for (int i = 0; i < WIDTH + 2; i++) {
        for (int j = 0; j < LENGTH + 2; j++) {
            if (i == 0 || i == WIDTH + 1 || j == 0 || j == LENGTH + 1) {
                printw("#");
            } else if ((j == (LENGTH / 2) + LENGTH % 2) && ((ball_x == j && ball_y != i) || ball_x != j)) {
                printw("|");
            } else if (((i == racket_1 || i == racket_1 - 1 || i == racket_1 + 1) && j == 1) ||
                       ((i == racket_2 || i == racket_2 - 1 || i == racket_2 + 1) && j == LENGTH)) {
                printw("|");
            } else if (j == ball_x && i == ball_y) {
                printw("*");
            } else {
                printw(" ");
            }
        }
        printw("\n\r");
    }
}

int move_racket_1(char temp, int racket_1) {
    switch (temp) {
        case 'a':
            ((racket_1 - 2) != 0) ? (racket_1 -= 1) : racket_1;
            break;
        case 'z':
            ((racket_1 + 2) != 26) ? (racket_1 += 1) : racket_1;
            break;
    }
    return racket_1;
}

int move_racket_2(char temp, int racket_2) {
    switch (temp) {
        case 'k':
            ((racket_2 - 2) != 0) ? (racket_2 -= 1) : racket_2;
            break;
        case 'm':
            ((racket_2 + 2) != 26) ? (racket_2 += 1) : racket_2;
            break;
        case ' ':
            break;
    }
    return racket_2;
}

int random_vector() {
    int dir;
    srand(time(NULL));
    dir = rand() % 2;
    if (dir == 0) dir -= 1;
    return dir;
}

void screen_preparation() {
    initscr();
    noecho();
    printw("\t\t\tPlease, press any key to play...\n");
    refresh();
    nodelay(stdscr, 1);
}

void score_printer(int score_1) {
    if (score_1 == 21) {
        printf("Game over! Left player won!\n");
    } else {
        printf("Game over! Right player won!\n");
    }
}