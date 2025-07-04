#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#define HEIGHT 30
#define WIDTH 70

typedef enum {STOP = 0, LEFT, RIGHT, UP, DOWN} direction;

typedef struct {
    int x,y;} position;

typedef struct {
    position head;
    position body[100];
    int length;
    direction dir;
    int score;
    bool gameover;
} gamestate;

void setup(gamestate* game){
    game->head.x = WIDTH/2;
    game->head.y = HEIGHT/2;
    game->length = 1;
    game->dir = STOP;
    game->score = 0;
    game->gameover = FALSE;
}

void draw(gamestate* game){
    system("cls");
    for (int i=0; i<WIDTH; i++){printf("-");}
    printf("\n");

    for(int y=0; y<HEIGHT; y++){
        for(int x=0; x<WIDTH; x++){
            if(x==0 || x==WIDTH-1){printf("|");}
            else if(x == game->head.x && y == game->head.y){printf("O");}
            else {printf(" ");}
        }
        printf("\n");
    }
        for (int i=0; i<WIDTH; i++){printf("-");}
    printf("\nScore: %d\n", game->score);
}

void input(gamestate* game){
    if(_kbhit()){
        switch(_getch()){
        case 'w': if(game->dir!=DOWN) game->dir=UP; break;
        case 'a': if(game->dir!=RIGHT) game->dir=LEFT; break;
        case 's': if(game->dir!=UP) game->dir=DOWN; break;
        case 'd': if(game->dir!=LEFT) game->dir=RIGHT; break;
        }
    }
}

void logic(gamestate* game){
    for (int i=game->length-1;i>0;i--){
        game->body[i] = game->body[i-1];
    }
    if (game->length>0){game->body[0]=game->head;}

    switch(game->dir){
    case UP: game->head.y--; break;
    case LEFT: game->head.x--; break;
    case DOWN: game->head.y++; break;
    case RIGHT: game->head.x++; break;}

    if(game->head.x <= 0 || game->head.x >= WIDTH-1 || game->head.y <0 || game->head.y >= HEIGHT){
        game->gameover = true;
    }

}

int main() {
    gamestate game;
    setup(&game);

    while (!game.gameover) {
        draw(&game);
        input(&game);
        logic(&game);
        Sleep(100);
    }

    return 0;
}

