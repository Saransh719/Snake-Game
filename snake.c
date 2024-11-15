#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

#define HEIGHT 25
#define WIDTH 50 

int snake_tail_x[100]={WIDTH/2-1,WIDTH/2-2};
int snake_tail_y[100]={HEIGHT/2,HEIGHT/2};
int snake_head_x=WIDTH/2,snake_head_y=HEIGHT/2;
int is_tail=0;
int snake_length=1;
char direction='r';

void moving_tail_repititive_code(int temp_x,int temp_y)
{
    int i=0;
    while ((snake_tail_x[i+1]!=0)&&(snake_tail_y[i+1]!=0))
    {
        snake_tail_x[i+1]=snake_tail_x[i];
        snake_tail_y[i+1]=snake_tail_y[i];
        i++;
    }
    snake_tail_x[1]=temp_x;
    snake_tail_y[1]=temp_y;
}
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
    switch (direction)
    {
        case 'r':
        {
            snake_head_x++;
            snake_tail_x[0]=snake_head_x-1;
            snake_tail_y[0]=snake_head_y;
            moving_tail_repititive_code(temp_x,temp_y);
            break;
        }
        case 'l':
        {
            snake_head_x--;
            snake_tail_x[0]=snake_head_x+1;
            snake_tail_y[0]=snake_head_y;
            moving_tail_repititive_code(temp_x,temp_y);
            break;
        }
        case 'u':
        {
            snake_head_y--;
            snake_tail_y[0]=snake_head_y+1;
            snake_tail_x[0]=snake_head_x;
            moving_tail_repititive_code(temp_x,temp_y);
            break;
        }
        case 'd':
        {
            snake_head_y++;
            snake_tail_y[0]=snake_head_y-1;
            snake_tail_x[0]=snake_head_x;
            moving_tail_repititive_code(temp_x,temp_y);
            break;
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
        draw();
        move_snake();
        Sleep(200);
    }
    return 0;
}