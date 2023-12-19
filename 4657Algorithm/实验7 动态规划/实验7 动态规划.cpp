// 实验7 动态规划.cpp : 定义控制台应用程序的入口点。
//0-1背包
//最长递增子序列 
//https://blog.csdn.net/qq_36935691/article/details/113924931?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522170053300116800180634279%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=170053300116800180634279&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-113924931-null-null.142^v96^pc_search_result_base8&utm_term=%E6%9C%80%E9%95%BF%E9%80%92%E5%A2%9E%E5%AD%90%E5%BA%8F%E5%88%97%20%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92&spm=1018.2226.3001.4187

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <iostream>

using namespace std;
/*0/1背包
#define N 4		//物品数量
#define W 5		//背包容量

int _tmain(int argc, _TCHAR* argv[]){
	int v[] = {0,2,4,5,6};//物品价值数组
	int w[] = {0,1,2,3,4};//物品重量数组

	int dp[N + 1][W + 1] = {0};//子问题解数组 物品容量表 表示从i个物品中选取价值为j的最大价值
	int i,j;
	for(i = 1;i <= N; i ++){
		for(j = 1; j <= W; j ++){
			dp[i][j] = dp[i - 1][j];	//不选第i个物品

			if(j >= w[i])	//选第i个物品的前提
				//等于选与不选第i个物品两种情况的较大值
				dp[i][j] = max(dp[i][j],dp[i - 1][j - w[i]] + v[i]);
		}
	}

	printf("最大重量为%d\n",dp[N][W]);

	for (i = 0; i <= N; i ++){
		for (j = 0; j <= W; j ++)
			printf("%d ",dp[i][j]);
		printf("\n");
	}
	printf("\n");

	system("pause");
	return 0;
}*/

//拦截导弹 最长不增子序列
const int MAXN = 25;
int height[MAXN];//导弹高度
int dp[MAXN];

int longestIncreasingSeq(int n){
	int answer = 0;
	for(int i = 0;i < n; i ++){
		dp[i] = 1;
		for(int j = 0;j < i;j ++){
			if(height[i] <= height[j])
				dp[i] = max(dp[i],dp[j] + 1);
		}
		answer =  max(answer,dp[i]);
	}
	return answer;
}

int main(){
	int n;
	printf("请输入雷达捕捉到的敌国导弹个数K与高度");
	while(cin >> n){
		for(int i = 0; i < n; i ++)
			cin >> height[i];
		int answer = longestIncreasingSeq(n);
		cout << "最多能拦截" << answer << "个导弹" << endl;
	}

	return 0;
}