#include "raylib.h"

class Ball
{
public:
float x, y;
int speed_x, speed_y;
int sizex, sizey;
int color;
void draw()
{   
    DrawRectangle(x, y, sizex, sizey, WHITE);
}

void update()
{
    x += speed_x;
    y += speed_y;
};

};
Ball ball;

class Score
{
public:
int aiscore = 0;
int playerscore = 0;
int instance;
int screenWidth = 1280;
int screenHeight = 800;
void draw()
{
    DrawText(TextFormat("%d", aiscore), 1280/4, 800/10, 80, WHITE);
    DrawText(TextFormat("%d", playerscore), 1280/4*3, 800/10, 80, WHITE);
}
void update(int &instance)
{
    if (ball.x <= 0)
    {
        
        if (ball.x <= 0 || ball.x >= screenWidth){
                ball.x = screenWidth/2;
                ball.y = screenHeight/2;
            }
        playerscore++;
    }
    if (ball.x >= 1280-20)
    {
        
        if (ball.x <= 0 || ball.x >= screenWidth-20){
                ball.x = screenWidth/2;
                ball.y = screenHeight/2;
            }
        aiscore++;
    }
    if (aiscore == 5)
    {
        instance = 2;
    }
    if (playerscore == 5)
    {
        instance = 3;
    }
}
};

Score score;
class Playerpaddle
{
    public:
    int x, y;
    int speed;
    int sizex, sizey;
    int color;
    void draw()
        {
            DrawRectangle(x, GetMouseY(), sizex, sizey, WHITE);
        }
    void collision()
    {
        if (CheckCollisionRecs({(float)ball.x, (float)ball.y, (float)ball.sizex, (float)ball.sizey}, {(float)x, (float)GetMouseY(), (float)sizex, (float)sizey}))
        {
            ball.speed_x *= -1;
        }
    }

};
class Aipaddle
{
public:
int x, y;
int speed;
int sizex, sizey;
int color;
void draw()
    {
    DrawRectangle(x, y, sizex, sizey, WHITE);
    }
void collision()
{
    if (CheckCollisionRecs({(float)ball.x, (float)ball.y, (float)ball.sizex, (float)ball.sizey}, {(float)x, (float)y, (float)sizex, (float)sizey}))
    {
        ball.speed_x *= -1;
};
};
void movement()
{
    if (ball.y < y+50-ball.sizey/2)
    {
        y -= speed;
    }
    if (ball.y > y+50-ball.sizey/2)
    {
        y += speed;
    }
}
};
Playerpaddle player;
Aipaddle ai;

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 800;
    ball.x = screenWidth/2;
    ball.y = screenHeight/2;
    ball.sizex = 20;
    ball.sizey = 20;
    ball.speed_x = 4;
    ball.speed_y = 4;
    int paddleheight = 100;
    int paddlewidth = 20;
    int instance = 0;

    InitWindow(screenWidth, screenHeight, "Pong Game");

    SetTargetFPS(60);
    

    while (!WindowShouldClose())
    {
        //Main Menu
        if (!IsKeyPressed(KEY_ENTER)&& instance == 0)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Pong Game", 1280/2-MeasureText("Pong Game", 100)/2, 800/2 - 200, 100, WHITE);
            DrawText("Press Enter to start", 1280/2-MeasureText("Press Enter to start",40)/2, 800/2, 40, WHITE);
            DrawText("Press ESC to exit", 1280/2-MeasureText("Press ESC to exit",40)/2, 800/2 + 50, 40, WHITE);
            EndDrawing();
            
            if (IsKeyPressed(KEY_ESCAPE))
            {
                CloseWindow();             
                return 0;
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                instance = 1;
            }
        }
        //Game
        else if (instance == 1)
        {
            BeginDrawing();
            //Background
            ClearBackground(BLACK);
            //Score
            score.draw();
            score.update(instance);
            //Ball
            ball.draw();
            ball.update();
            if (ball.y+20 >= screenHeight || ball.y <= 0)
            {
                ball.speed_y *= -1;
            }

            //middle line
            DrawLine(screenWidth/2, 0, screenWidth/2, 800, WHITE);
            //Player
            player.x = screenWidth - 20 - paddlewidth;
            player.y = screenHeight/2 - paddleheight/2;
            player.sizex = paddlewidth;
            player.sizey = paddleheight;
            player.draw();
            player.collision();
            //AI
            ai.x = 20;
            ai.sizex = paddlewidth;
            ai.sizey = paddleheight;
            ai.speed = 3.8;
            ai.draw();
            ai.movement();
            ai.collision();
            EndDrawing();
            //Exit
            if (IsKeyPressed(KEY_ESCAPE))
            {
                CloseWindow();
                return 0;
            }
        }
        else if (instance == 2)
        {
            BeginDrawing();
            score.aiscore = 0;
            score.playerscore = 0;
            ClearBackground(BLACK);
            DrawText("GAME OVER", 1280/2-MeasureText("GAME OVER", 100)/2, 800/2 - 200, 100, WHITE);
            //Play again
            DrawText("Press Enter to play again", 1280/2-MeasureText("Press Enter to play again",40)/2, 800/2, 40, WHITE);            
            if (IsKeyPressed(KEY_ENTER))
            {
                instance = 1;
            }
            //Exit
            DrawText("Press ESC to exit", 1280/2-MeasureText("Press ESC to exit",40)/2, 800/2 + 50, 40, WHITE);
            if (IsKeyPressed(KEY_ESCAPE))
            {
                CloseWindow();
                return 0;
            }
            EndDrawing();
        }
        else if (instance == 3)
        {
            BeginDrawing();
            score.aiscore = 0;
            score.playerscore = 0;
            ClearBackground(BLACK);
            DrawText("YOU WIN", 1280/2-MeasureText("YOU WIN", 100)/2, 800/2 - 200, 100, WHITE);
            //Play again
            DrawText("Press Enter to play again", 1280/2-MeasureText("Press Enter to play again",40)/2, 800/2, 40, WHITE);
            if (IsKeyPressed(KEY_ENTER))
            {
                instance = 1;
            }
            //Exit
            DrawText("Press ESC to exit", 1280/2-MeasureText("Press ESC to exit",40)/2, 800/2 + 50, 40, WHITE);
            if (IsKeyPressed(KEY_ESCAPE))
            {
                CloseWindow();
                return 0;
            }
            EndDrawing();
        }
    }
}
