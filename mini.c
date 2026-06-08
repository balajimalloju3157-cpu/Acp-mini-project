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

// Function to draw rectangle
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

// Function to draw line
void drawLine(int row1, int col1, int row2, int col2)
{
    if(row1 == row2)
    {
        for(int j = col1; j <= col2 && j < COLS; j++)
        {
            canvas[row1][j] = '*';
        }
    }
    else if(col1 == col2)
    {
        for(int i = row1; i <= row2 && i < ROWS; i++)
        {
            canvas[i][col1] = '*';
        }
    }
}

// Function to draw triangle
void drawTriangle(int row, int col, int height)
{
    for(int i = 0; i < height; i++)
    {
        canvas[row + i][col - i] = '*';
        canvas[row + i][col + i] = '*';
    }

    for(int j = col - (height - 1); j <= col + (height - 1); j++)
    {
        canvas[row + height - 1][j] = '*';
    }
}

// Function to draw a simple circle
void drawCircle(int centerRow, int centerCol, int radius)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            int dx = i - centerRow;
            int dy = j - centerCol;

            int dist = dx * dx + dy * dy;

            if(dist >= radius * radius - radius &&
               dist <= radius * radius + radius)
            {
                canvas[i][j] = '*';
            }
        }
    }
}

int main()
{
    int choice;

    initializeCanvas();

    printf("===== MINI GRAPHICS EDITOR =====\n");
    printf("1. Draw Vertical Line\n");
    printf("2. Draw Horizontal Line\n");
    printf("3. Draw Rectangle\n");
    printf("4. Draw Triangle\n");
    printf("5. Draw Circle\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            drawLine(2, 20, 15, 20);
            break;

        case 2:
            drawLine(10, 5, 10, 30);
            break;

        case 3:
            drawRectangle(2, 5, 12, 6);
            break;

        case 4:
            drawTriangle(2, 20, 6);
            break;

        case 5:
            drawCircle(10, 20, 5);
            break;

        default:
            printf("Invalid Choice!\n");
            return 0;
    }

    printf("\nCanvas Output:\n\n");
    displayCanvas();

    return 0;
}