#include "functions.h"

int player1_y = 350;
int player2_y = 350;

int ball_x = 800;
int ball_y = 450;

int ball_sy = 5;
int ball_sx = -5;
int players_speed = 6;

int player1_score = 0;
int player2_score = 0;

int last_loose = 0;
int last_sped_up = 0;
int seconds = 0;

int winer = 0;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Pong");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Intro();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        seconds = GetTime();
        if (seconds > last_sped_up + 10)
        {
            ball_sx *= 1.3;
            ball_sy *= 1.3;
            players_speed *= 1.3;
            last_sped_up = seconds;
        }

        ball_x += ball_sx;
        ball_y += ball_sy;

        if (ball_x < 0)
        {
            ball_sx = 5;
            ball_sy = 5;
            ball_x = 800;
            players_speed = 6;
            player2_score++;
            last_loose = seconds;
        }

        if (ball_x > 1600)
        {
            ball_sx = -5;
            ball_sy = 5;
            ball_x = 800;
            players_speed = 6;
            player1_score++;
            last_loose = seconds;
        }

        if (ball_y < 0)
        {
            ball_sy *= -1;
        }

        if (ball_y > 900)
        {
            ball_sy *= -1;
        }


        if (ball_x < 60 && ball_y < player1_y + 200 && ball_y > player1_y)
        {
            ball_sx *= -1;
        }

        if (ball_x > 1540 && ball_y < player2_y + 200 && ball_y > player2_y)
        {
            ball_sx *= -1;
        }


        if (IsKeyDown(KEY_DOWN) && player2_y < 700)
        {
            player2_y += players_speed;
        }

        if (IsKeyDown(KEY_UP) && player2_y > 0)
        {
            player2_y -= players_speed;
        }

        if (IsKeyDown(KEY_S) && player1_y < 700)
        {
            player1_y += players_speed;
        }

        if (IsKeyDown(KEY_W) && player1_y > 0)
        {
            player1_y -= players_speed;
        }

        winer = CheckSet(player1_score, player2_score);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        if (winer == 1)
        {
            DrawText("Player 1 won!", 100, 400, 200, WHITE);
        }
        else if (winer == 2)
        {
            DrawText("Player 2 won!", 100, 400, 200, WHITE);
        }
        else
        {
            DrawRectangle(0, player1_y, 50, 200, WHITE);     //Draw player 1
            DrawRectangle(1550, player2_y, 50, 200, WHITE);  //Draw player 2

            DrawRectangle(798, 0, 4, 900, WHITE);            //Draw net

            DrawCircle(ball_x, ball_y, 15, WHITE);           //Draw ball

            char buf[256];
            sprintf_s(buf, "%d", player1_score);               //Draw player 1 score
            DrawText(buf, 400, 0, 100, WHITE);

            char buf2[256];
            sprintf_s(buf2, "%d", player2_score);              //Draw player 2 score
            DrawText(buf2, 1200, 0, 100, WHITE);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}