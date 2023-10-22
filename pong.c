#include <stdio.h>

#define LENGTH 80
#define WIDTH 25
#define RACKET_POSITION 13
#define BALL_POSITION_X (LENGTH / 2)
#define BALL_POSITION_Y (WIDTH / 2 + WIDTH % 2)

void init_field(int score_1, int score_2, int ball_x, int ball_y, int racket_1, int racket_2);
int move_racket_1(char temp, int racket_1);
int move_racket_2(char temp, int racket_2);
void field_clean();

int main() {
    int racket_1, racket_2, ball_x, ball_y, score_1, score_2, dir_x, dir_y;
    racket_1 = racket_2 = RACKET_POSITION, ball_x = BALL_POSITION_X, ball_y = BALL_POSITION_Y,
    score_1 = score_2 = 0, dir_x = dir_y = 1;
    while (1) {
        init_field(score_1, score_2, ball_x, ball_y, racket_1, racket_2);
        char temp = getchar();
        while (temp != '\n') {
            racket_1 = move_racket_1(temp, racket_1);
            racket_2 = move_racket_2(temp, racket_2);
            temp = getchar();
        }
        if (ball_x < 3) {
            if (racket_1 != ball_y && (racket_1 - 1) != ball_y && (racket_1 + 1) != ball_y &&
                (racket_1 - 2) != ball_y && (racket_1 + 2) != ball_y) {
                score_2 += 1;
                ball_x = BALL_POSITION_X;
                ball_y = BALL_POSITION_Y;
            } else if (racket_1 == ball_y || racket_1 - 1 == ball_y || racket_1 + 1 == ball_y ||
                       racket_1 + 1 == ball_y + dir_y || racket_1 - 1 == ball_y + dir_y)
                dir_x = -dir_x;
        } else if (ball_x > 78) {
            if (racket_2 != ball_y && (racket_2 - 2) != ball_y && (racket_2 + 2) != ball_y &&
                (racket_2 - 1) != ball_y && (racket_2 + 1) != ball_y) {
                score_1 += 1;
                ball_x = BALL_POSITION_X;
                ball_y = BALL_POSITION_Y;
            } else if (racket_2 == ball_y || racket_2 - 1 == ball_y || racket_2 + 1 == ball_y ||
                       racket_2 + 1 == ball_y + dir_y || racket_2 - 1 == ball_y + dir_y)
                dir_x = -dir_x;
        } else if (ball_y == 1 || ball_y == 25)
            dir_y = -dir_y;
        ball_x += dir_x;
        ball_y += dir_y;
        if (score_1 == 21 || score_2 == 21) break;
        field_clean();
    }
    if (score_1 == 21) {
        printf("Game over! Left player won!\n");
    } else {
        printf("Game over! Right player won!\n");
    }
    return 0;
}

void init_field(int score_1, int score_2, int ball_x, int ball_y, int racket_1, int racket_2) {
    printf("%d || %d\n", score_1, score_2);
    for (int i = 0; i < WIDTH + 2; i++) {
        for (int j = 0; j < LENGTH + 2; j++) {
            if (i == 0 || i == WIDTH + 1 || j == 0 || j == LENGTH + 1) {
                printf("#");
            } else if ((j == (LENGTH / 2) + LENGTH % 2) && ((ball_x == j && ball_y != i) || ball_x != j)) {
                printf("|");
            } else if (((i == racket_1 || i == racket_1 - 1 || i == racket_1 + 1) && j == 1) ||
                       ((i == racket_2 || i == racket_2 - 1 || i == racket_2 + 1) && j == LENGTH)) {
                printf("|");
            } else if (j == ball_x && i == ball_y) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
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

void field_clean() { printf("\33[0d\33[2J"); }
