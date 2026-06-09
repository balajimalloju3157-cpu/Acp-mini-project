#include <stdio.h>

#define ROWS 20
#define COLS 40
#define MAX_OBJECTS 100

char canvas[ROWS][COLS];

typedef struct
{
    int id;
    int type; // 1-Line 2-Rectangle 3-Triangle 4-Circle

    int row1, col1;
    int row2, col2;

    int width, height;
    int radius;

    int active;
} Object;

Object objects[MAX_OBJECTS];
int objectCount = 0;

/* ---------------- Canvas Functions ---------------- */

void initializeCanvas()
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

/* ---------------- Shape Drawing Functions ---------------- */

void drawRectangleCanvas(int row,int col,int width,int height)
{
    for(int i=row;i<row+height && i<ROWS;i++)
    {
        for(int j=col;j<col+width && j<COLS;j++)
        {
            if(i==row || i==row+height-1 ||
               j==col || j==col+width-1)
            {
                canvas[i][j]='*';
            }
        }
    }
}

void drawLineCanvas(int row1,int col1,int row2,int col2)
{
    if(row1==row2)
    {
        if(col1>col2)
        {
            int t=col1;
            col1=col2;
            col2=t;
        }

        for(int j=col1;j<=col2 && j<COLS;j++)
            canvas[row1][j]='*';
    }
    else if(col1==col2)
    {
        if(row1>row2)
        {
            int t=row1;
            row1=row2;
            row2=t;
        }

        for(int i=row1;i<=row2 && i<ROWS;i++)
            canvas[i][col1]='*';
    }
}

void drawTriangleCanvas(int row,int col,int height)
{
    for(int i=0;i<height;i++)
    {
        if(row+i<ROWS && col-i>=0)
            canvas[row+i][col-i]='*';

        if(row+i<ROWS && col+i<COLS)
            canvas[row+i][col+i]='*';
    }

    for(int j=col-(height-1);
        j<=col+(height-1);j++)
    {
        if(j>=0 && j<COLS)
            canvas[row+height-1][j]='*';
    }
}

void drawCircleCanvas(int centerRow,
                      int centerCol,
                      int radius)
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            int dx=i-centerRow;
            int dy=j-centerCol;

            int d=dx*dx + dy*dy;

            if(d>=radius*radius-radius &&
               d<=radius*radius+radius)
            {
                canvas[i][j]='*';
            }
        }
    }
}

/* ---------------- Redraw Entire Scene ---------------- */

void redrawCanvas()
{
    initializeCanvas();

    for(int i=0;i<objectCount;i++)
    {
        if(objects[i].active==0)
            continue;

        switch(objects[i].type)
        {
            case 1:
                drawLineCanvas(
                    objects[i].row1,
                    objects[i].col1,
                    objects[i].row2,
                    objects[i].col2
                );
                break;

            case 2:
                drawRectangleCanvas(
                    objects[i].row1,
                    objects[i].col1,
                    objects[i].width,
                    objects[i].height
                );
                break;

            case 3:
                drawTriangleCanvas(
                    objects[i].row1,
                    objects[i].col1,
                    objects[i].height
                );
                break;

            case 4:
                drawCircleCanvas(
                    objects[i].row1,
                    objects[i].col1,
                    objects[i].radius
                );
                break;
        }
    }
}

/* ---------------- Add Object ---------------- */

void addObject()
{
    Object obj;

    objectCount++;

    obj.id = objectCount;
    obj.active = 1;

    printf("\n1. Line");
    printf("\n2. Rectangle");
    printf("\n3. Triangle");
    printf("\n4. Circle");

    printf("\nEnter Shape Type: ");
    scanf("%d",&obj.type);

    switch(obj.type)
    {
        case 1:
            printf("Start Row Col: ");
            scanf("%d%d",&obj.row1,&obj.col1);

            printf("End Row Col: ");
            scanf("%d%d",&obj.row2,&obj.col2);
            break;

        case 2:
            printf("Top Row Col: ");
            scanf("%d%d",&obj.row1,&obj.col1);

            printf("Width Height: ");
            scanf("%d%d",&obj.width,&obj.height);
            break;

        case 3:
            printf("Top Row Col: ");
            scanf("%d%d",&obj.row1,&obj.col1);

            printf("Height: ");
            scanf("%d",&obj.height);
            break;

        case 4:
            printf("Center Row Col: ");
            scanf("%d%d",&obj.row1,&obj.col1);

            printf("Radius: ");
            scanf("%d",&obj.radius);
            break;

        default:
            printf("Invalid Shape\n");
            objectCount--;
            return;
    }

    objects[objectCount-1] = obj;

    redrawCanvas();

    printf("Object Added. ID = %d\n",obj.id);
}

/* ---------------- Delete Object ---------------- */

void deleteObject()
{
    int id;

    printf("Enter Object ID to Delete: ");
    scanf("%d",&id);

    for(int i=0;i<objectCount;i++)
    {
        if(objects[i].id==id &&
           objects[i].active)
        {
            objects[i].active=0;

            redrawCanvas();

            printf("Object Deleted\n");
            return;
        }
    }

    printf("Object Not Found\n");
}

/* ---------------- Modify Object ---------------- */

void modifyObject()
{
    int id;

    printf("Enter Object ID to Modify: ");
    scanf("%d",&id);

    for(int i=0;i<objectCount;i++)
    {
        if(objects[i].id==id &&
           objects[i].active)
        {
            switch(objects[i].type)
            {
                case 1:
                    printf("New Start Row Col: ");
                    scanf("%d%d",
                          &objects[i].row1,
                          &objects[i].col1);

                    printf("New End Row Col: ");
                    scanf("%d%d",
                          &objects[i].row2,
                          &objects[i].col2);
                    break;

                case 2:
                    printf("New Top Row Col: ");
                    scanf("%d%d",
                          &objects[i].row1,
                          &objects[i].col1);

                    printf("New Width Height: ");
                    scanf("%d%d",
                          &objects[i].width,
                          &objects[i].height);
                    break;

                case 3:
                    printf("New Top Row Col: ");
                    scanf("%d%d",
                          &objects[i].row1,
                          &objects[i].col1);

                    printf("New Height: ");
                    scanf("%d",
                          &objects[i].height);
                    break;

                case 4:
                    printf("New Center Row Col: ");
                    scanf("%d%d",
                          &objects[i].row1,
                          &objects[i].col1);

                    printf("New Radius: ");
                    scanf("%d",
                          &objects[i].radius);
                    break;
            }

            redrawCanvas();

            printf("Object Modified\n");
            return;
        }
    }

    printf("Object Not Found\n");
}

/* ---------------- Main ---------------- */

int main()
{
    int choice;

    initializeCanvas();

    while(1)
    {
        printf("\n\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Add Object\n");
        printf("2. Delete Object\n");
        printf("3. Modify Object\n");
        printf("4. Display Canvas\n");
        printf("5. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addObject();
                break;

            case 2:
                deleteObject();
                break;

            case 3:
                modifyObject();
                break;

            case 4:
                displayCanvas();
                break;

            case 5:
                printf("Project Ended.\n");
                return 0;

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}