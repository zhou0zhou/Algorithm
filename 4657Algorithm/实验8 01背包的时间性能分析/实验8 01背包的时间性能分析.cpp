// 实验8 01背包的时间性能分析.cpp : 定义控制台应用程序的入口点。
//https://blog.csdn.net/Edward_Mcc/article/details/122567532#:~:text=01%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E4%B8%89%E7%A7%8D%E8%A7%A3%E5%86%B3%EF%BC%88%E8%B4%AA%E5%BF%83%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E5%88%86%E6%94%AF%E9%99%90%E7%95%8C%EF%BC%89%201%20%E7%94%A83%E7%A7%8D%E6%96%B9%E6%B3%95%E6%B1%82%E8%A7%A30-1%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%EF%BC%88%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95%E3%80%81%20%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E3%80%81%E5%88%86%E6%94%AF%E9%99%90%E7%95%8C%E6%B3%95%20%EF%BC%89%EF%BC%8C%E8%8E%B7%E5%BE%97%E7%B2%BE%E7%A1%AE%E6%9C%80%E4%BC%98%E8%A7%A3%E6%88%96%E8%BF%91%E4%BC%BC%E6%9C%80%E4%BC%98%E8%A7%A3%E5%9D%87%E5%8F%AF%E3%80%82,2%20%E9%80%9A%E8%BF%87%E4%B8%80%E4%B8%AA%E8%A7%84%E6%A8%A1%E8%BE%83%E5%A4%A7%E7%9A%84%E5%AE%9E%E4%BE%8B%E6%AF%94%E8%BE%83%E4%B8%8D%E5%90%8C%E6%96%B9%E6%B3%95%E7%9A%84%20%E6%B1%82%E8%A7%A3%E9%80%9F%E5%BA%A6%EF%BC%8C%E5%88%86%E6%9E%90%E4%B8%8D%E5%90%8C%E7%AE%97%E6%B3%95%E7%9A%84%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6%EF%BC%8C%E5%B9%B6%E5%88%86%E6%9E%90%E6%98%AF%E5%90%A6%E8%83%BD%E8%8E%B7%E5%BE%97%E6%9C%80%E4%BC%98%E8%A7%A3%E3%80%82%203%20%E5%AE%9E%E9%AA%8C%E7%BB%93%E6%9E%9C%E8%B7%9F%E5%AE%9E%E9%AA%8C%E8%AE%BE%E7%BD%AE%E7%9A%84%E5%8F%82%E6%95%B0%EF%BC%88%E5%A6%82%EF%BC%9A%E8%83%8C%E5%8C%85%E5%AE%B9%E9%87%8F%E3%80%81%E7%89%A9%E5%93%81%E7%9A%84%E4%BD%93%E7%A7%AF%EF%BC%89%E5%85%B3%E7%B3%BB%E5%BE%88%E5%A4%A7%EF%BC%8C%E7%AE%80%E8%A6%81%E5%88%86%E6%9E%90%E5%8F%82%E6%95%B0%E5%AF%B9%E7%BB%93%E6%9E%9C%E7%9A%84%E5%BD%B1%E5%93%8D%E3%80%82
//https://blog.csdn.net/qq_38289815/article/details/83620475?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522170098280816800215028264%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=170098280816800215028264&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-83620475-null-null.142^v96^pc_search_result_base8&utm_term=%E8%9B%AE%E5%8A%9B%E6%B3%9501%E8%83%8C%E5%8C%85&spm=1018.2226.3001.4187
//https://blog.csdn.net/sc2333/article/details/105159664
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <time.h>
#include <stack>
#include <Windows.h>
using namespace std;

#define max(x,y) (((x) > (y)) ? (x) : (y)) 
#define MAXN 10000 //最大的物品数
#define MAXW 10000 //最大限制重量

int n,W;//n个物品，背包容量为W
int x[MAXN];//解向量
int w[MAXN],v[MAXN];//物品重量和价值
int bestv;//存放最优解的总价值
//动态规划数据结构
int dp[MAXN][MAXN];//dp[i][j]表示从i个物品选出重量为j的背包的最大价值解
//蛮力 贪心数据结构
struct NodeType{
	int w;
	int v;
	double p;//性价比 p = v/w
	bool operator<(const NodeType& s)const{
		return p > s.p;
	}
};
NodeType A[MAXN];
//回溯法数据结构
bool best_x[MAXN];//存储最优方案
int now_v;//当前价值
int remain_v;//剩余价值
int now_w;//当前重量
int best_v;//最优价值
//蛮力法
int cv,cw,cx[MAXN];
int forcesolution(int i){
	if(i > n){//判断是不是叶子节点 是的话直接回溯输出
		if(bestv < cv && cw <= W){
			for(int k = 1; k <= n; k ++)
				x[k] = cx[k];//存储最优路径
			bestv = cv;
		}
		return bestv;
	}
	cw = cw + A[i].w;
	cv = cv + A[i].v;
	cx[i] = 1;//装入背包
	forcesolution(i + 1);//进行下一个 

	cw = cw - A[i].w;
	cv = cv - A[i].v;
	cx[i] = 0;//不装入背包
	forcesolution(i + 1);

	return bestv;
}

//动态规划
void dpsolution(){
	int i,j;
	for(i = 0;i <= n; i ++)//置边界条件dp[i][0] = 0
		dp[i][0] = 0;
	for(j = 0;j <= n; j ++)//置边界条件dp[0][j] = 0
		dp[0][j] = 0;
	for(i = 1;i <= n; i ++){
		for(j = 1; j <= W; j ++){
			if(j < w[i])
				dp[i][j] = dp[i - 1][j];
			else  //选与不选的较大值
				dp[i][j] = max(dp[i - 1][j],dp[i - 1][j - w[i]] + v[i]);
		}
	}
}
void Buildx(){//回推求最优解 x[i]为1的为装入背包的物品
	int i = n,j = W;
	bestv = 0;
	while(i >= 0){
		if(dp[i][j] != dp[i - 1][j]){
			x[i] = 1;
			bestv += v[i];
			j = j - w[i];
		}else
			x[i] = 0;
		i --;
	}
}

//贪心 按单位性价比
void greedysolution(){
	bestv = 0;//初始化为0
	int weight = W;
	memset(x,0,sizeof(x));//初始化解向量
	int i = 1;
	while(A[i].w <= weight){
		x[i] = 1;
		weight -= A[i].w;
		bestv += A[i].v;
		i ++;
	}
}

//回溯法
int Bound(int k){//计算分支节点k的上界
	remain_v = 0;
	while(k <= n){
		remain_v += v[k];
		k ++;
	}
	return remain_v + now_v;
}
void Backtrack(int t){//t为扩展结点在树中所在的层次
	if(t > n){//是否到达叶子节点 
		for(int i = 1; i <= n; i ++)
			best_x[i] = x[i];//记录回溯的最优情况
		best_v = now_v;//记录回溯中的最优价值
		return;
	}
	//约束条件剪枝：在扩展结点处剪去不满足约束的子树
	if(now_w + w[t] <= W){// 约束条件 判断是否满足放入条件 放入考虑左子树，否则考虑右子树 
		x[t] = 1;
		now_w += w[t];
		now_v += v[t];
		Backtrack(t + 1);//再进行下一个节点的分析
		now_w -= w[t];//在到达叶子节点后进行回溯一个节点
		now_v -= v[t];
	}
	if(Bound(t + 1) > best_v){//限界条件剪枝：剪去得不到最优解的子树 
		//如果放入t后不满足约束条件则进行到此处，然后判断若当前价值加剩余价值没有最优，则不用再比下去了
		x[t] = 0;
		Backtrack(t + 1);
	}
}
void tracksolution(int W,int n){
	int sum_w = 0;
	int sum_v = 0;
	best_v = 0;
	for(int i = 0; i < n; i ++){
		sum_w += w[i];
		sum_v += v[i];
	}
	//迭代 从1开始
	Backtrack(1);
    /*cout << "选取物品号为：" << endl;
    for (int i = 1; i <= n; i++) {
        if(x[i] == 1)
            cout << i << " ";
    }
	cout << "总价值为：" << best_v << endl;*/
}
//展示结果
void show(){
	printf("选取物品号为:");
	for(int i = 1; i <= n; i ++)
		if(x[i] == 1)
			printf("%d ",i);
	printf("\n");
	printf("总价值为%d\n",bestv);
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "0/1背包问题" << endl;
	cout << "请输入物品个数与背包总容量 n和W" << endl;
	cin >> n >> W;
	/*
	//先测试各算法的正确性
	cout << "请依次输入各物品的重量与价值"<< endl;
	for(int i = 1; i <= n; i ++)
		cin >> w[i] >> v[i];
	for(int i = 1; i <= n; i ++){
		A[i].w = w[i];
		A[i].v = v[i];
		A[i].p = (double)A[i].v / A[i].w;
	}
	forcesolution(1);
	cout <<"蛮力法的结果"<< endl;
	show();
	cout << endl;
	dpsolution();
	Buildx();
	cout <<"动态规划的结果"<< endl;
	show();
	cout << endl;
	cout <<"回溯法的结果"<< endl;
	tracksolution(W,n);
	cout << endl;
	sort(A + 1, A + n + 1);//排序 按照性价比排序 在数据结构中已经定义
    greedysolution();
	cout <<"贪心法的结果"<< endl;
	show();*/

	//毫秒级别的时间性能分析
	LARGE_INTEGER frequency;
    LARGE_INTEGER start_time;
    LARGE_INTEGER end_time;
    double elapsed_time;

    QueryPerformanceFrequency(&frequency);

	// 蛮力法
    double total_force_time = 0.0;
    for (int measurement = 0; measurement < 10; measurement++) {
        for (int i = 1; i <= n; i++) {
            A[i].w = rand() % 100;
            A[i].v = rand() % 100;
            A[i].p = (double)A[i].v / A[i].w;
        }

        QueryPerformanceCounter(&start_time);
        forcesolution(1);
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_force_time += elapsed_time;
    }

    double average_force_time = total_force_time / 10;
    cout << "蛮力法平均执行时间: " << average_force_time << " 毫秒" << endl;
    // 动态规划
    double total_dp_time = 0.0;
    for (int measurement = 0; measurement < 10; measurement++) {//每个算法执行十次，求平均时间
        for (int i = 0; i < n; i++) {//先生成样本
            w[i] = rand() % 100;
            v[i] = rand() % 100;
        }

        QueryPerformanceCounter(&start_time);
        dpsolution();
        Buildx();
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_dp_time += elapsed_time;
    }

    double average_dp_time = total_dp_time / 10;
    cout << "动态规划平均执行时间: " << average_dp_time << " 毫秒" << endl;

    // 贪心
    double total_greedy_time = 0.0;
    for (int measurement = 0; measurement < 10; measurement++) {
        for (int i = 1; i <= n; i++) {
            A[i].w = rand() % 100;
            A[i].v = rand() % 100;
            A[i].p = (double)A[i].v / A[i].w;
        }

        QueryPerformanceCounter(&start_time);
        sort(A + 1, A + n + 1);//排序 按照性价比排序 在数据结构中已经定义
        greedysolution();
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_greedy_time += elapsed_time;
    }

    double average_greedy_time = total_greedy_time / 10;
    cout << "贪心算法平均执行时间: " << average_greedy_time << " 毫秒" << endl;

    // 回溯法
    double total_bb_time = 0.0;
    for (int measurement = 0; measurement < 10; measurement++) {
        for (int i = 1; i <= n; i++) {
            w[i] = rand() % 100;
            v[i] = rand() % 100;
        }

        QueryPerformanceCounter(&start_time);
        tracksolution(W, n);
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_bb_time += elapsed_time;
    }

    double average_bb_time = total_bb_time / 10;
    cout << "回溯法平均执行时间: " << average_bb_time << " 毫秒" << endl;

	system("pause");
    return 0;
}
