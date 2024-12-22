#include "raylib.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){

    //initiallisation 
    bool over = false;
    bool restart = true;
    
    int sh = 900;
    int sw = 900;

    Color BGcol = BLACK;

    int dir = 0;
    int size = 20; //size of each box
    int speed = size;
    int posx = sw/2;
    int posy = sh/2;

    int SnakeSize = 50; //snake length
    
    struct position {int x, y;};
    vector <position> pos_log;

    //window
    InitWindow(sw, sh, "snake game");
    SetTargetFPS(5);

    //main game loop
    while (!WindowShouldClose()){

        if (restart){

            //initial position for all snake box
            dir = 0;
            pos_log.clear();
            for (int i=0; i< SnakeSize; i++){
                pos_log.push_back({posx , posy});

            over = false;
            restart = false;
            }
        }

        if (!over){            
            if(IsKeyPressed(KEY_W) && dir!= 2) dir = 1;
            if(IsKeyPressed(KEY_S) && dir!= 1) dir = 2;
            if(IsKeyPressed(KEY_A) && dir!= 4) dir = 3;
            if(IsKeyPressed(KEY_D) && dir!= 3)dir = 4;

            switch (dir)
            {
                case 1:pos_log[0].y -= speed;break;
                case 2:pos_log[0].y += speed;break;
                case 3:pos_log[0].x -= speed;break;
                case 4:pos_log[0].x += speed;break;
            }

            //updates position
            if (SnakeSize>1){
                for (int i=SnakeSize; i>0; i--){
                    pos_log[i] = pos_log[i-1];
                }
            }

            //self collision
            for (int i = 2; i<SnakeSize; i++){
                if (pos_log[0].x == pos_log[i].x && pos_log[0].y == pos_log[i].y && dir!=0) {
                    over = true;
                }
            }

            //wall collision
            if (pos_log[0].x+size >= sw || pos_log[0].y+size >= sh || pos_log[0].x <= 0 || pos_log[0].y <= 0) {
                over = true;
            }

            BeginDrawing();
            ClearBackground(BGcol);

            //draws blocks based on updated position
            for(int i = 0; i<SnakeSize; i++){
                DrawRectangle(pos_log[i].x, pos_log[i].y , size, size, BGcol);
                DrawRectangle(pos_log[i].x, pos_log[i].y , size-1, size-1, WHITE);
            }
            EndDrawing();
        }

        //game over
        else if (over){
            BeginDrawing();
            ClearBackground(BGcol);
            DrawText("Game over", (sw-MeasureText("Game over",50))/2, (sh- 50)/2 , 50, WHITE);
            DrawText("press spcae to restart", (sw-MeasureText("press spcae to restart",20))/2, ((sh+ 30)/2) , 20, WHITE);
            EndDrawing();

            if (IsKeyPressed(KEY_SPACE)){
                restart=true;
            }
        }
    }
    CloseWindow();
    return 0;
}