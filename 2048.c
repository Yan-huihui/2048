
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "2048.h"

int counter;
int score = 0;

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void print2048(int (*arry)[4], int rows)
{
	printf("---------------------\n");
	int i, j, clos = sizeof(arry[0]) / sizeof(arry[0][0]);
	for(i = 0; i < rows; ++i)
	{
		for(j = 0; j < clos; ++j)
		{
			if(arry[i][j] != 0)
			{
				printf("|%4d", arry[i][j]);
			}
			else
			{
				printf("|    ");
			}
		}
		puts("|");
		printf("---------------------\n");
	}
}

void remove_right(int (*arry)[4],int rows)
{
	int i, j, clos = sizeof(arry[0]) / sizeof(arry[0][0]);
	for(i = 0; i < rows ; ++i)//向右移动
	{
		int t ;
		for(t = 0;t < 3; ++t)
		{
			for(j = 3; j > 0; --j)
			{
				if(arry[i][j] == 0)
				{
					arry[i][j] = arry[i][j - 1];
					arry[i][j - 1] = 0;
				}
			}
		}

		for(j = 3; j > 0; --j)
		{
			if(arry[i][j] == arry[i][j - 1])
			{
				arry[i][j] = 2 * arry[i][j];
				arry[i][j - 1] = 0;
				if(arry[i][j] != 0)
				{
					++score;
				}
			}
		}

		for(t = 0;t < 3; ++t)
		{
			for(j = 3; j > 0; --j)
			{
				if(arry[i][j] == 0)
				{
					arry[i][j] = arry[i][j - 1];
					arry[i][j - 1] = 0;
				}
			}
		}
	}
}

void remove_left(int (*arry)[4],int rows)
{
	int i, j, clos = sizeof(arry[0]) / sizeof(arry[0][0]);
	for(i = 0; i < rows; ++i)//向左移动
	{
		int t ;
		for(t = 0;t < 3;++t)
		{
			for(j = 0; j < 3; ++j)
			{
				if(arry[i][j] == 0)
				{
					arry[i][j] = arry[i][j + 1];
					arry[i][j + 1] = 0;
				}
			}
		}

		for(j = 0; j < 3; ++j)
		{
			if(arry[i][j] == arry[i][j + 1])
			{
				arry[i][j] = 2 * arry[i][j];
				arry[i][j + 1] = 0;
				if(arry[i][j] != 0)
				{
					++score;
				}
			}
		}

		for(t = 0;t < 3;++t)
		{
			for(j = 0; j < 3; ++j)
			{
				if(arry[i][j] == 0)
				{
					arry[i][j] = arry[i][j + 1];
					arry[i][j + 1] = 0;
				}
			}
		}
	}
}

void remove_up(int (*arry)[4],int rows)
{
	int i, j, clos = sizeof(arry[0]) / sizeof(arry[0][0]);
	for(j = 0; j < clos; ++j)//向上移动
	{
		int t ;
		for(t = 0;t < 3;++t)
		{
			for(i = 0; i < 3; ++i)
			{
				if(arry[i][j] == 0)
				{
					arry[i][j] = arry[i + 1][j];
					arry[i + 1][j] = 0;
				}
			}
		}

		for(i = 0; i < 3; ++i)
		{
			if(arry[i][j] == arry[i + 1][j])
			{
				arry[i][j] = 2 * arry[i][j];
				arry[i + 1][j] = 0;
				if(arry[i][j] != 0)
				{
					++score;
				}
			}
		}

		for(t = 0;t < 3;++t)
		{
			for(i = 0; i < 3; ++i)
			{
				if(arry[i][j] == 0)
				{
					arry[i][j] = arry[i + 1][j];
					arry[i + 1][j] = 0;
				}
			}
		}
	}
}

void remove_down(int (*arry)[4],int rows)
{
	int i, j, clos = sizeof(arry[0]) / sizeof(arry[0][0]);
	for(j = 0; j < clos; ++j)//向下移动
	{
		int t ;
		for(t = 0;t < 3;++t)
		{
			for(i = 3; i > 0; --i)
			{
				if(arry[i][j] == 0)
				{
					arry[i][j] = arry[i - 1][j];
					arry[i - 1][j] = 0;
				}
			}
		}

		for(i = 3; i > 0; --i)
		{
			if(arry[i][j] == arry[i - 1][j])
			{
				arry[i][j] = 2 * arry[i][j];
				arry[i - 1][j] = 0;
				if(arry[i][j] != 0)
				{
					++score;
				}
			}
		}

		for(t = 0;t < 3;++t)
		{
			for(i = 3; i > 0; --i)
			{
				if(arry[i][j] == 0)
				{
					arry[i][j] = arry[i - 1][j];
					arry[i - 1][j] = 0;
				}
			}
		}
	}
}
int random2or4(void)
{
	if(random() % 2 == 0)
	{
		return 2;
	}
	else
	{
		return 4;
	}
}

int randomLess4(void)
{
	return (random() % 4);
}

int isSame(int (*arry)[4])
{
	int i, j;
	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 3; ++j)
		{
			if(arry[i][j] == arry[i][j + 1])
			{
				return 1;
			}
		}
	}
	for(j = 0; j < 4; ++j)
	{
		for(i = 0; i < 3; ++i)
		{
			if(arry[i][j] == arry[i + 1][j])
			{
				return 1;
			}
		}
	}
	return 0;
}
int  winOrLoseStop(int (*arry)[4])
{
	int i, j;
	counter = 0;
	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			if(arry[i][j] != 0)
			{
				++counter;
			}
			if(arry[i][j] == 2048)
			{
				return 1;
			}
			if(counter == 16 && isSame(arry) == 0)
			{
				return -1;
			}
		}
	}
	return 0;
}

int copyarry(int (*des)[4], int (*src)[4])
{
	int i,j;
	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			des[i][j] = src[i][j];
		}
	}
	return 0;
}

int isSame_OldAndNewArry(int (*old)[4], int (*new)[4])
{
	int i,j;
	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			if(old[i][j] != new[i][j])
			{
				return 1;
			}
		}
	}
	return 0;
}
int  start(void)
{
	srandom(time(NULL));
	int arry[4][4] = {0};
	int i = randomLess4();
	int j = randomLess4();
	arry[i][j] = random2or4();
	int rows = sizeof(arry) / sizeof(arry[0]);

	print2048(arry, rows);

	while(1)
	{
		int buff[4][4] = {0};
		copyarry(buff, arry);

		char ch = getch();
		if(ch == 'd')
		{
			remove_right(arry, rows);
		}
		else if(ch == 'a')
		{
			remove_left(arry, rows);
		}
		else if(ch == 'w')
		{
			remove_up(arry, rows);
		}
		else if(ch == 's')
		{
			remove_down(arry, rows);
		}
		else if(ch == 'q')
		{
			return 0;
		}
		else
		{
			continue;
		}

		system("clear");
		int sameOldAndNew = isSame_OldAndNewArry(buff, arry);
		do
		{
			i = randomLess4();
			j = randomLess4();
			winOrLoseStop(arry);
		}
		while(arry[i][j] != 0 && counter < 16);

		if(counter < 16 && sameOldAndNew == 1)
		{
			arry[i][j] = random2or4();
		}
		
		printf("score   %d\n",score);
		printf("counter %d\n",counter);//
		printf("same    %d\n",isSame(arry));//
		printf("winOrLoseStop %d\n",winOrLoseStop(arry) );//
		print2048(arry, rows);

		if(winOrLoseStop(arry) == 1)
		{
			printf("win\n");
			break;
		}
		if(winOrLoseStop(arry) == -1)
		{
			printf("lose\n");
			break;
		}

	}

	return 0;
}

