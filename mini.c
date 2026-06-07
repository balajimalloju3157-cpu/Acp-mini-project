#include <stdio.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

// Function to initialize the canvas
void initializeCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

// Function to display the canvas
void displayCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

// Function to draw a rectangle
void drawRectangle(int row, int col, int width, int height)
{
    for(int i = row; i < row + height && i < ROWS; i++)
    {
        for(int j = col; j < col + width && j < COLS; j++)
        {
            if(i == row || i == row + height - 1 ||
               j == col || j == col + width - 1)
            {
                canvas[i][j] = '*';
            }
        }
    }
}

// Function to draw a horizontal or vertical line
void drawLine(int row1, int col1, int row2, int col2)
{
    if(row1 == row2) // Horizontal line
    {
        for(int j = col1; j <= col2 && j < COLS; j++)
        {
            canvas[row1][j] = '*';
        }
    }
    else if(col1 == col2) // Vertical line
    {
        for(int i = row1; i <= row2 && i < ROWS; i++)
        {
            canvas[i][col1] = '*';
        }
    }
    else
    {
        printf("Only horizontal and vertical lines are supported.\n");
    }
}

int main()
{
    initializeCanvas();

    // Sample rectangle
    drawRectangle(2, 5, 12, 6);

    // Sample horizontal line
    drawLine(12, 2, 12, 20);

    // Sample vertical line
    drawLine(8, 30, 15, 30);

    displayCanvas();

    return 0;
}