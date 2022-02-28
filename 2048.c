
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "2048.h"

int counter;
int score = 0;

int getch(void)									//输入一个字符刷新缓冲区
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

void print2048(int (*arry)[4], int rows)		//按照格式打印二维数组
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

void remove_right(int (*arry)[4],int rows)		//向右移动，数组内数字对应改变
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

		for(j = 3; j > 0; --j)					//移动后，前后左右两个有相同的前数乘二，后数归零
		{
			if(arry[i][j] == arry[i][j - 1])
			{
				arry[i][j] = 2 * arry[i][j];
				arry[i][j - 1] = 0;
				if(arry[i][j] != 0)
				{
					++score;					//消除数字时分数加1
				}
			}
		}

		for(t = 0;t < 3; ++t)					//防止消除相同数字后中间有空位，再次向右移动
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

void remove_left(int (*arry)[4],int rows)		//向左对应操作
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

void remove_up(int (*arry)[4],int rows)					//向上对应操作
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

void remove_down(int (*arry)[4],int rows)					//向下对应操作
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
int random2or4(void)					//返回一个2或者4
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

int randomLess4(void)					//返回一个小于4的值
{
	return (random() % 4);
}

int isSame(int (*arry)[4])				//判断每个位置相邻的数是否有相同的，有相同的返回1，没有相同返回0
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
int  winOrLoseStop(int (*arry)[4])				//判断是否输或者赢，赢返回1，输返回-1，继续游戏返回0
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

int copyarry(int (*des)[4], int (*src)[4])						//用于拷贝数组
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

int isSame_OldAndNewArry(int (*old)[4], int (*new)[4])			//用于判断两个二维数组是否相同
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
	arry[i][j] = random2or4();							//游戏开始在随机位置写入一个2或者4
	int rows = sizeof(arry) / sizeof(arry[0]);

	print2048(arry, rows);

	while(1)
	{
		int buff[4][4] = {0};
		copyarry(buff, arry);

		char ch = getch();								//获取从键盘输入字符
		if(ch == 'd')									//若输入d执行向右相关操作
		{
			remove_right(arry, rows);
		}
		else if(ch == 'a')								//若输入a执行向左相关操作
		{
			remove_left(arry, rows);
		}
		else if(ch == 'w')
		{
			remove_up(arry, rows);						//若输入w执行向上相关操作
		}
		else if(ch == 's')
		{
			remove_down(arry, rows);					//若输入s执行向下相关操作
		}
		else if(ch == 'q')								//若输入q退出游戏
		{
			return 0;
		}
		else											//输入其他字符进入下一个循环
		{
			continue;
		}

		system("clear");								//清屏
		int sameOldAndNew = isSame_OldAndNewArry(buff, arry);
		do
		{
			i = randomLess4();
			j = randomLess4();
			winOrLoseStop(arry);
		}
		while(arry[i][j] != 0 && counter < 16);			

		if(counter < 16 && sameOldAndNew == 1)			//在数组未满以及移动前后数组不相同情况下找不为零位置写入2或者4
		{
			arry[i][j] = random2or4();
		}
		
		printf("score   %d\n",score);					//打印分数
		print2048(arry, rows);							//打印移动后二维数组

		if(winOrLoseStop(arry) == 1)					//判断是否赢
		{
			printf("win\n");
			break;
		}
		if(winOrLoseStop(arry) == -1)					//判断是否输
		{
			printf("lose\n");
			break;
		}

	}

	return 0;
}

