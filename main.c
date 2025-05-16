#include "raylib.h"
#include <stdio.h>


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

void checkSet();
void intro();

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
    intro();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        seconds = GetTime();
        if(seconds > last_sped_up + 10)
        {
            ball_sx *= 1.3;
            ball_sy *= 1.3;
            players_speed *= 1.3;
            last_sped_up = seconds;
        }

        ball_x += ball_sx;
        ball_y += ball_sy;
        
        if(ball_x < 0)
        {
            ball_sx = 5;
            ball_sy = 5;
            ball_x = 800;
            players_speed = 6;
            player2_score++;
            last_loose = seconds;
        }
        
        if(ball_x > 1600)
        {
            ball_sx = -5;
            ball_sy = 5;
            ball_x = 800;
            players_speed = 6;
            player1_score++;
            last_loose = seconds;
        }
        
        if(ball_y < 0)
        {
            ball_sy *= -1;
        }
        
        if(ball_y > 900)
        {
            ball_sy *= -1;
        }
        
        
        if(ball_x < 60 && ball_y < player1_y + 200 && ball_y > player1_y)
        {
            ball_sx *= -1;
        }
        
        if(ball_x > 1540 && ball_y < player2_y + 200 && ball_y > player2_y)
        {
            ball_sx *= -1;
        }
        
        
        if(IsKeyDown(KEY_DOWN) && player2_y < 700)
        {
            player2_y += players_speed;
        }
        
        if(IsKeyDown(KEY_UP) && player2_y > 0)
        {
            player2_y -= players_speed;
        }
        
        if(IsKeyDown(KEY_S) && player1_y < 700)
        {
            player1_y += players_speed;
        }
        
        if(IsKeyDown(KEY_W) && player1_y > 0)
        {
            player1_y -= players_speed;
        }
        
        checkSet();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
            if(winer == 1)
            {
                DrawText("Player 1 won!", 100, 400, 200, WHITE);
            }
            else if(winer == 2)
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
                sprintf(buf, "%d", player1_score);               //Draw player 1 score
                DrawText(buf, 400, 0, 100, WHITE);
                
                char buf2[256];
                sprintf(buf2, "%d", player2_score);              //Draw player 2 score
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

void checkSet()
{
    if(player1_score == 11)
    {
        winer = 1;
    }
    
    if(player2_score == 11)
    {
        winer = 2;
    }
}


void intro()
{
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    int logoPositionX = screenWidth/2 - 128;
    int logoPositionY = screenHeight/2 - 128;

    int framesCounter = 0;
    int lettersCount = 0;

    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;

    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;

    int state = 0;                  // Tracking animation states (State Machine)
    float alpha = 1.0f;
    
    while(state != 4)
    {
        // Update
        //----------------------------------------------------------------------------------
        if (state == 0)                 // State 0: Small box blinking
        {
            framesCounter++;

            if (framesCounter == 120)
            {
                state = 1;
                framesCounter = 0;      // Reset counter... will be used later...
            }
        }
        else if (state == 1)            // State 1: Top and left bars growing
        {
            topSideRecWidth += 4;
            leftSideRecHeight += 4;

            if (topSideRecWidth == 256) state = 2;
        }
        else if (state == 2)            // State 2: Bottom and right bars growing
        {
            bottomSideRecWidth += 4;
            rightSideRecHeight += 4;

            if (bottomSideRecWidth == 256) state = 3;
        }
        else if (state == 3)            // State 3: Letters appearing (one by one)
        {
            framesCounter++;

            if (framesCounter/12)       // Every 12 frames, one more letter!
            {
                lettersCount++;
                framesCounter = 0;
            }

            if (lettersCount >= 10)     // When all letters have appeared, just fade out everything
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    state = 4;
                }
            }
        }
        else if (state == 4)            // State 4: Reset and Replay
        {
            if (IsKeyPressed(KEY_R))
            {
                framesCounter = 0;
                lettersCount = 0;

                topSideRecWidth = 16;
                leftSideRecHeight = 16;

                bottomSideRecWidth = 16;
                rightSideRecHeight = 16;

                alpha = 1.0f;
                state = 0;          // Return to State 0
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            if (state == 0)
            {
                if ((framesCounter/15)%2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, WHITE);
            }
            else if (state == 1)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, WHITE);
                DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, WHITE);
            }
            else if (state == 2)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, WHITE);
                DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, WHITE);

                DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, WHITE);
                DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, WHITE);
            }
            else if (state == 3)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(WHITE, alpha));
                DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(WHITE, alpha));

                DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(WHITE, alpha));
                DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(WHITE, alpha));

                DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(BLACK, alpha));

                DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(WHITE, alpha));
            }

        EndDrawing();
    }
}




