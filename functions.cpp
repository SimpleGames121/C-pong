#include "functions.h"

void Intro()
{
    const int screenWidth = 1600;
    const int screenHeight = 900;

    int logoPositionX = screenWidth / 2 - 128;
    int logoPositionY = screenHeight / 2 - 128;

    int framesCounter = 0;
    int lettersCount = 0;

    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;

    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;

    int state = 0;                  // Tracking animation states (State Machine)
    float alpha = 1.0f;

    while (state != 4 && !WindowShouldClose() && !IsKeyDown(KEY_ENTER))
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

            if (framesCounter / 12)       // Every 12 frames, one more letter!
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
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        if (state == 0)
        {
            if ((framesCounter / 15) % 2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, WHITE);
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

            DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(BLACK, alpha));

            DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(WHITE, alpha));
        }

        EndDrawing();
    }
}

int CheckSet(int player1_score, int player2_score)
{
    if (player1_score == 11)
    {
        return 1;
    }

    if (player2_score == 11)
    {
        return 2;
    }
    return 0;
}