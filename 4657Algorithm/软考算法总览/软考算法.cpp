// 软考算法总览.cpp : 定义控制台应用程序的入口点。
//1.回溯法 N皇后问题 递归与非递归

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>

#define N 4

int q[N + 1];	//存储皇后的内存 q[i] 表示该皇后存储在第i列
int answer = 0; //方案数

int check(int j){											//判断第j个皇后的位置是否合法
	int i;
	for(i = 1;i < j; i ++){
		if( q[i] == q[j] || abs(i - j) == abs(q[i] - q[j])) //同一行 或对角线（横纵坐标差的绝对值相同）
			return 0;
	}
		return 1;
}
//非递归 回溯法
void queen(){								//求解 N皇后 方案
	int i;
	for(i = 1;i <= N;i ++)
		q[i] = 0;							//初始化每一个皇后的位置为0

	answer = 0;							//方案数
	int j = 1;								//表示正在摆放第j个皇后

	while(j >= 1){
		q[j] = q[j] + 1;					//开始摆放 即让第j个皇后向后一列摆放

		while(q[j] <= N && !check(j)){		//判断第J个皇后的位置是否合法
			q[j] = q[j] + 1;				//不合法就往后一个位置摆放
		}

		if(q[j] <= N){						//表示第j个皇后的位置合法
			if(j == N){						//找到了N皇后的一组解
				answer ++;
				printf("方案%d: ",answer);
				for(i = 1; i <= N; i ++)
					printf("%d ",q[i]);
				printf("\n");
			}else{							//继续摆放下一个皇后
				j ++;
			}
		}
		else{				//表示第j个皇后找不到合法位置 回溯上一个位置
			q[j] = 0;		//还原第j个皇后的位置
			j --;			//回溯
		}
	}
}
//递归法
void queen1(int j){
	int i;
	for(i = 1; i <= N; i ++){
		q[j] = i;

		if(check(j)){		//当摆放的皇后位置合法时
			if(j == N){	//找到一组解
				answer ++;
				printf("方案%d: ",answer);
				for(i = 1; i <= N; i ++)
					printf("%d ",q[i]);
				printf("\n");
			}else{
				queen1(j ++);//递归摆放下一个皇后的位置
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	queen();
	printf ("\n");
	//queen1(1);
	system("pause");
	return 0;
}