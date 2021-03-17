#include <stdio.h>
#include <stdlib.h>
#include <waitpkgintrin.h>

// 组成蛇身子的点
typedef struct Point {
    int x; // x坐标
    int y; // y坐标
    struct Point *next;
    struct Point *previous;
} TPoint;

// 蛇
typedef struct Snake {
    TPoint *head;
    TPoint *tail;
    int direction;// 1-向左移动 2-向右移动 3-向上移动 4-向下移动
    int status; // 1-静止 2-运动中 3-死亡
} TSnake;

/**
 * 初始化蛇
 * @param s
 */
void initSnake(TSnake *s) {
    TPoint *point = (TPoint *) malloc(sizeof(TPoint));
    point->next = NULL;
    point->previous = NULL;
    point->x = 0;
    point->y = 0;
    s->head = point;
    s->tail = point;
    s->status = 1;
    s->direction = 0;
}

/**
 * 向上移动
 * @param s
 */
void moveUp(TSnake *s) {
    if (s->status == 1 || (s->status == 2 && (s->direction == 1 || s->direction == 2))) {
        TPoint *p = s->tail;
        while (NULL != p) {
            if (NULL == p->next) {
                p->y++;
            } else {
                p->x = p->next->x;
                p->y = p->next->y;
            }
            p = p->next;
        }
    }
}

/**
 * 向下移动
 * @param s
 */
void moveDown(TSnake *s) {
    if (s->status == 1 || (s->status == 2 && (s->direction == 1 || s->direction == 2))) {
        TPoint *p = s->tail;
        while (NULL != p) {
            if (NULL == p->next) {
                p->y--;
            } else {
                p->x = p->next->x;
                p->y = p->next->y;
            }
            p = p->previous;
        }
    }
}

/**
 * 向左移动
 * @param s
 */
void moveLeft(TSnake *s) {
    if (s->status == 1 || (s->status == 2 && (s->direction == 3 || s->direction == 4))) {
        TPoint *p = s->tail;
        while (NULL != p) {
            if (NULL == p->next) {
                p->x--;
            } else {
                p->x = p->next->x;
                p->y = p->next->y;
            }
            p = p->previous;
        }
    }
}

/**
 * 向右移动
 * @param s
 */
void moveRight(TSnake *s) {
    if (s->status == 1 || (s->status == 2 && (s->direction == 3 || s->direction == 4))) {
        TPoint *p = s->tail;
        while (NULL != p) {
            if (NULL == p->next) {
                p->x++;
            } else {
                p->x = p->next->x;
                p->y = p->next->y;
            }
            p = p->previous;
        }
    }
}

/**
 * 控制蛇移动的函数
 * @param s
 * @param direction
 */
void move(TSnake *s, int direction) {
    switch (direction) {
        case 1:
            moveUp(s);
            break;
        case 2:
            moveDown(s);
            break;
        case 3:
            moveLeft(s);
            break;
        case 4:
            moveRight(s);
            break;
    }
}

void display(TSnake *s) {
    char area[100][100] = {{'\0'}};
    TPoint *p = s->head;
    while (NULL != p) {
        area[p->y][p->x] = '*';
        p = p->previous;
    }
    int i, j;
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            printf("%c ", area[i][j]);
        }
        printf("\n");
    }
}

TSnake snake;

/**
 * 游戏初始化
 */
void init() {
    initSnake(&snake); // 初始化蛇
}

int main() {
    init();
    while (1) {
        system("clear");
        display(&snake);
        moveRight(&snake);
        sleep();
    }
    return 0;
}
