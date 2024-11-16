#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

#define HEIGHT 25
#define WIDTH 50 

int snake_tail_x[100]={WIDTH/2-1,WIDTH/2-2,WIDTH/2-3,WIDTH/2-4,WIDTH/2-5};
int snake_tail_y[100]={HEIGHT/2,HEIGHT/2,HEIGHT/2,HEIGHT/2,HEIGHT/2};
int snake_head_x=WIDTH/2,snake_head_y=HEIGHT/2;
int is_tail=0;
char direction='r';
int fruit_x=24,fruit_y=5;
int snake_len=5;

void move_snake()
{
    if (kbhit())
    {
        switch ((char)getch())
        {
            case 'w': 
            {
                direction='u';
                break;
            }
            case 'a': 
            {
                direction='l';
                break;
            }
            case 's': 
            {
                direction='d';
                break;
            }
            case 'd': 
            {
                direction='r';
                break;
            }
            
        }
    }
    int temp_x=snake_tail_x[0];
    int temp_y=snake_tail_y[0];
    snake_tail_x[0]=snake_head_x;
    snake_tail_y[0]=snake_head_y;
    switch (direction)
    {
        case 'r':
        {
            snake_head_x++;
            break;
        }
        case 'l':
        {
            snake_head_x--;
            break;
        }
        case 'u':
        {
            snake_head_y--;
            break;
        }
        case 'd':
        {
            snake_head_y++;
            break;
        }
    }
    for (int i = snake_len - 1; i > 0; i--) 
    {
        snake_tail_x[i]=snake_tail_x[i-1];
        snake_tail_y[i]=snake_tail_y[i-1];
    }
    snake_tail_x[1]=temp_x;
    snake_tail_y[1]=temp_y;
}

void fruit_check()
{
    if ((snake_head_x==fruit_x)&&(snake_head_y==fruit_y))
    {
        switch(direction)
        {
            case 'u':
            {
                snake_tail_y[snake_len]=snake_tail_y[snake_len-1]+1;
                snake_tail_x[snake_len]=snake_tail_x[snake_len-1];
                snake_len++;
                break;
            }
            case 'd':
            {
                snake_tail_y[snake_len]=snake_tail_y[snake_len-1]-1;
                snake_tail_x[snake_len]=snake_tail_x[snake_len-1];
                snake_len++;
                break;
            }
            case 'l':
            {
                snake_tail_y[snake_len]=snake_tail_y[snake_len-1];
                snake_tail_x[snake_len]=snake_tail_x[snake_len-1]+1;
                snake_len++;
                break;
            }
            case 'r':
            {
                snake_tail_y[snake_len]=snake_tail_y[snake_len-1];
                snake_tail_x[snake_len]=snake_tail_x[snake_len-1]-1;
                snake_len++;
                break;
            }
        }
    }
}

void draw()
{
    system("cls");
    for (int i=0;i<=HEIGHT;i++)
    {
        for (int j=0;j<=WIDTH;j++)
        {
            //printing top
            if ((i==0)||(i==HEIGHT)) printf("-");
            //printing sides
            else if ((j==0)||(j==WIDTH)) printf("|");
            //printing snake head
            else if ((i==snake_head_y)&&(j==snake_head_x)) printf("*");
            //printing fruit
            else if ((j==fruit_x)&&(i==fruit_y)) printf("@");
            //printing tail
            else
            {
                is_tail=0;
                for (int k=0;k<100;k++)
                {
                    if ((snake_tail_x[k]==j)&&(snake_tail_y[k]==i)) 
                    {
                        printf("+");
                        is_tail=1;
                    }

                    
                }
                if (is_tail==0) printf(" ");
            }
        }
        printf("\n");
    }
}

int main()
{
    while (1)
    {
        fruit_check();
        draw();
        move_snake();
        Sleep(100);
    }
    return 0;
}