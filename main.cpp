#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#define F 25	//刷新频率 
#define WID 40 //x
#define HIGH 28 //y

//初始化地图 0:死   1:生 
//多一圈便于处理边界 
int map2[HIGH+1][WID+1]={0}; 	//map2用于中间过程存放地图数据 
int map[HIGH+1][WID+1]={0}; 

void initMap();
void drawMap();
void updateMap(); 
void gotoxy();
void deconsole(); 

int main()
{
	deconsole();
	//初始化地图
	srand((unsigned)time(NULL));
	initMap(); 
	
	int m=0;
	while(1)
	{
		//记录迭代次数 
		++m;
		
		//绘制地图
		drawMap();
		
		//更新地图 
		updateMap();
		
		//控制刷新时间
		Sleep(F);
		
//		system("cls");	//会频闪 
		printf("\n\n次数：%d",m);
	}
	return 0;
}

//初始化地图
void initMap()
{
	//尽量把 1 放在地图中间区域 
	int margin = 10; 
	for(int i=margin;i<HIGH-margin;++i)
	{
		for(int j=margin;j<WID-margin;++j)
		{
			map[i][j]=rand()%2;
		}
	}
}

//绘制地图 
void drawMap()
{
	gotoxy();
	for(int i=1;i<HIGH;++i)			//不绘制坐标为0的点，为了方便处理边界计数情况 
	{
		for(int j=1;j<WID;++j)
		{
			if(map[i][j]) 
			{
				printf("■");
			}
			else 
			{
				printf("  ");
			}
		}
		printf("|\n");	//打印一行后打印右边界再换行 
	}
	for(int i=1;i<WID;++i)
	printf("—");		//打印左边界 
} 

//更新地图
void updateMap()
{
	for(int i=1;i<HIGH;++i)
	{
		for(int j=1;j<WID;++j)
		{
			int sum;
			sum=map[i-1][j-1]+map[i-1][j]+map[i-1][j+1]+map[i][j-1]+map[i][j+1]+map[i+1][j-1]+map[i+1][j]+map[i+1][j+1]; 
			if(sum==3)
			map2[i][j]=1;
			else if(sum==2) 
			map2[i][j]=map[i][j];
			else map2[i][j]=0;
		}
	}
	memcpy(map,map2,(HIGH+1)*(WID+1)*sizeof(int));		//将中间数据map2复制给map 
}

//使光标回到原处
void gotoxy() 
{
  HANDLE h0ut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = 0;
  pos.Y = 0;
  SetConsoleCursorPosition(h0ut, pos);
} 

//隐藏光标
void deconsole()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
} 
