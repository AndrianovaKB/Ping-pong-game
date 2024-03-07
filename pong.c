#include <stdio.h>

int field(int x, int y, int n, int m, int ball_x, int ball_y, int sc_1, int sc_2);
int ball(int ball_x, int ball_y, int vek, int roc_1, int roc_2);
int max_score(int b1, int b2);

int main() {
    int x = 80;
    int y = 25;

    int ball_x = 40;
    int ball_y = 13;
    int vek = 2;
    int res;

    int left_y = 12;
    int right_y = 12;

    int sc_1 = 0;
    int sc_2 = 0;

    char a;
    int width = 3;
    printf("\e[1;1H\e[2J");
    printf(
        ">>>>>>>>>>>>>>>PING PONG!<<<<<<<<<<<<<<<<\n;\
            Приветствую, дорогие участники!)\n,\
            Правила игры:\n,\
                        Есть два игрока, их рокетки могут двигаться вверх и вниз. \n,\
                        И есть шарик ('0'), который передвигается внутри поля, и его нужно отбивать.\n,\
                        Если игрок не отбил, то засчитывается гол противнику.\n,\
                        Управление:\n,\
                        PLAYER 1: A - вверх, Z - вниз\n,\
                        PLAYER 2: K - вверх, M - вниз\n,\
                        Игра заканчивается, когда счет одного игрока достигает 21.\n,\
                        Ввод осуществляектся последовательно, обновление поля происходит нажатием Enter\n,\
                        \n,\
                        P.S. Завозите Милти по выходным (((((");

    while (max_score(sc_1, sc_2) < 21) {
        field(x, y, left_y, right_y, ball_x, ball_y, sc_1, sc_2);
        while (ball_x >= 1 && ball_x <= 79) {
            a = getchar();

            if (a != '\n') {
                if ((int)a == 97 || (int)a == 65) {  //кнопка A
                    left_y--;
                } else if ((int)a == 90 || (int)a == 122) {  //кнопка Z
                    left_y++;
                } else if ((int)a == 32) {
                    left_y = left_y + 0;
                } else if ((int)a == 75 || (int)a == 107) {  //кнопка K
                    right_y--;
                } else if ((int)a == 77 || (int)a == 109) {  //кнопка M
                    right_y++;
                } else if (a != ' ')
                    printf("Ошибка!!! Введите повторно ");

                //Проверки на стенки
                if (left_y + width >= y) {
                    left_y = y - 3;

                } else if (left_y == 0) {
                    printf("%d", left_y);
                    left_y = 1;
                }
                if (right_y + width >= y) {
                    right_y = y - 3;
                } else if (right_y == 0) {
                    printf("%d", right_y);
                    right_y = 1;
                }

                res = ball(ball_x, ball_y, vek, left_y, right_y);
                ball_x = res / 1000;
                ball_y = (res % 1000) / 10;
                vek = res % 10;
                field(x, y, left_y, right_y, ball_x, ball_y, sc_1, sc_2);
            }
        }
        if (ball_x == 0) {
            sc_2 += 1;
        } else if (ball_x == 80) {
            sc_1 += 1;
        }
        ball_x = 40;
        ball_y = 13;
        left_y = 12;
        right_y = 12;
    }
    if (sc_1 == 21)
        printf("Выиграл первый игрок!\n");
    else
        printf("Выиграл второй игрок!\n");
    return 0;
}

int field(int x, int y, int n, int m, int ball_x, int ball_y, int sc_1, int sc_2) {
    printf("\e[1;1H\e[2J");
    for (int i = 0; i <= y; i++) {
        for (int j = 0; j <= x; j++) {
            if (i == ball_y && j == ball_x) {
                printf("0");
            }
            //Вывод левой стенки
            else if (j == 0) {
                printf("%c", 124);
            }
            //Вывод правой стенки
            else if (j == x) {
                printf("%c", 124);
            }
            //Вывод верхней и нижней стенки
            else if ((i == 0) || (i == y)) {
                printf("%c", 61);
            }

            //Вывод разделителя поля
            else if (j == (x / 2)) {
                printf("%c", 124);
            } else if (((i == n || i == n + 1 || i == n + 2) && (j == 2)) ||
                       ((i == m || i == m + 1 || i == m + 2) && (j == 78))) {
                printf("%c", 124);
            }

            else if (ball_y != y / 2 && ball_x != x / 2 && i == y / 2 && j == x / 2) {
                printf("%c", 124);
            } else
                printf("%c", 32);
        }
        printf("\n");
    }
    printf("  PLAYER 1: %d                          |||                          PLAYER 2: %d\n", sc_1, sc_2);
    return 0;
}

int ball(int ball_x, int ball_y, int vek, int roc_1, int roc_2) {
    if (ball_y == 1) {
        if (vek == 1) vek = 2;
        if (vek == 4) vek = 3;
    }
    if (ball_y == 24) {
        if (vek == 2) vek = 1;
        if (vek == 3) vek = 4;
    }
    if (ball_x == 3 && (ball_y == roc_1 || ball_y == roc_1 + 1 || ball_y == roc_1 + 2)) {
        if (vek == 3) vek = 2;
        if (vek == 4) vek = 1;
    }
    if (ball_x == 77 && (ball_y == roc_2 || ball_y == roc_2 + 1 || ball_y == roc_2 + 2)) {
        if (vek == 2) vek = 3;
        if (vek == 1) vek = 4;
    }
    if (ball_x == 3 && vek == 3 && ball_y == roc_1 - 1) vek = 1;
    if (ball_x == 3 && vek == 4 && ball_y == roc_1 + 3) vek = 2;
    if (ball_x == 77 && vek == 2 && ball_y == roc_2 - 1) vek = 4;
    if (ball_x == 77 && vek == 1 && ball_y == roc_2 + 3) vek = 3;
    if (vek == 1) {
        ball_x += 1;
        ball_y -= 1;
    }
    if (vek == 2) {
        ball_x += 1;
        ball_y += 1;
    }
    if (vek == 3) {
        ball_x -= 1;
        ball_y += 1;
    }
    if (vek == 4) {
        ball_x -= 1;
        ball_y -= 1;
    }
    return (ball_x * 1000 + ball_y * 10 + vek);
}

int max_score(int b1, int b2) {
    if (b1 > b2)
        return b1;
    else
        return b2;
}