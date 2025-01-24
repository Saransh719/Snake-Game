#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

#define HEIGHT 25
#define WIDTH 50 

float sleep_time=16.66;     //in milliseconds
int snake_tail_x[100]={WIDTH/2-1,WIDTH/2-2};
int snake_tail_y[100]={HEIGHT/2,HEIGHT/2};
int snake_head_x=WIDTH/2,snake_head_y=HEIGHT/2;
int is_tail=0;
char direction='r';
int fruit_x=40,fruit_y=5;
int snake_len=2;
int score=0;
int gameover=1;

void initialise()
{
    snake_tail_x[0]=WIDTH/2-1;
    snake_tail_x[1]=WIDTH/2-2;
    snake_tail_y[0]=HEIGHT/2;
    snake_tail_y[1]=HEIGHT/2;
    snake_head_x=WIDTH/2,snake_head_y=HEIGHT/2;
    is_tail=0;
    direction='r';
    fruit_x=40,fruit_y=5;
    snake_len=2;
    score=0;
    gameover=1;
}

void is_gameover()
{
    //checking if snake hitting itself or boundary (used multiple if for reading simplicity but they are not required)
    for (int i=0;i<snake_len;i++)
    {
        if ((snake_head_x==snake_tail_x[i])&&(snake_head_y==snake_tail_y[i])) gameover=0;
    }
    if ((snake_head_x==0)||(snake_head_x==WIDTH)) gameover=0;
    if ((snake_head_y==0)||(snake_head_y==HEIGHT)) gameover=0;


    //manually exiting the game is handled inside move_snake function
}

void randomise()
{
    fruit_x=rand() % WIDTH;
    fruit_y=rand() % HEIGHT;
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
            case 'x':
            {
                gameover=0;
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
    for (int i=snake_len-1;i>0;i--) 
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
        //Changing fruit position
        randomise();

        //checking if fruit is inside snake after randomising
        int fruit_in_snake=1;
        while (fruit_in_snake)
        {
            fruit_in_snake=0;
            for (int i=0;i<snake_len;i++)
            {
                if ((fruit_x==snake_tail_x[i])||(fruit_y==snake_tail_y[i])) 
                {
                    randomise();
                    fruit_in_snake=1;
                    break;
                }
            }

        }
        //in case x or y gets 0
        while ((fruit_x==0)||(fruit_y==0))
        {
            randomise();
        }
        //Making snake bigger
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
        score++;
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
    printf("Score : %d \n",score);
}

void main()
{
    while (1)
    {
        while (gameover==1)
        {
            fruit_check();
            draw();
            move_snake();
            is_gameover();
            Sleep(sleep_time);
        }
        system("cls");
        printf("GAMEOVER \n");
        printf("Your score was : %d \n",score);
        printf("Thank You for playing \n");
        printf("Press x to exit");
        printf("Press r to restart");
        char button=getch();
        if (button=='x') break;
        // char exit=getch();
        if (button=='r') initialise();
        
    }
}