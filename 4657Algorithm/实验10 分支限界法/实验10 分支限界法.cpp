// 实验10 分支限界法.cpp : 定义控制台应用程序的入口点。
//https://blog.csdn.net/sc2333/article/details/106523626
//https://blog.csdn.net/weixin_53522240/article/details/122371260?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522170192026616800197014087%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=170192026616800197014087&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-122371260-null-null.142^v96^pc_search_result_base8&utm_term=01%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E5%88%86%E6%94%AF%E7%95%8C%E9%99%90%E6%B3%95c&spm=1018.2226.3001.4187

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <Windows.h>
using namespace std;

struct node{
	int cv,cw;//当前价值和当前重量
	int step;//第step个物品
	int *x;
	float upcv;//上界
	bool operator < (const node &b) const{//运算符重载 按照上界排列
		return upcv < b.upcv;
	}
};
typedef struct{
	int w,v,no;
}goods;//物品

int n,w;//物品个数，背包容量
goods *a;
int bv,*x,*bx;//最优值，当前解，最优解

int cmp(goods a,goods b){
	return a.v * b.w >= a.w * b.v;//按单位价值排序
}
float bound(node st){//搜索限界函数
	//采用贪心法求得背包问题的最优值
	int i,m = w - st.cw;
	float b = st.cv;
	for(i = st.step;i <= n && a[i].w <= m; i ++){
		b += a[i].v;
		m -= a[i].w;
	}
	if(i <= n)
		b += (m * 1.0/a[i].w) * a[i].v;
	return b;
}

void pfs(){//优先队列搜索函数
	node now,next;
	int i,ns;
	priority_queue <node> Q;//定义优先队列Q并初始化
	now.cv = now.cw = 0;
	now.step = 1;
	now.x = new int[now.step];
	now.upcv = bound(now);
	Q.push(now);//进队列
	while(!Q.empty()){//队不空
		now = Q.top();
		Q.pop();
		if(now.upcv <= bv)//当该节点的最大上界比当前最优值小时直接结束
			break;
		//否则 更新最优值的解
		ns = now.step;
		if(ns == n + 1){
			if(now.cv > bv){
				bv = now.cv;
				for(int i = 1;i <= n;i ++)//解向量
					bx[i] = now.x[i];
			}
			continue;
		}

		//1 - branch 右子树
		if(a[ns].w + now.cw <= w){
			next.cv = now.cv + a[ns].v;
			next.cw = now.cw + a[ns].w;
			next.step = ns + 1;
			next.upcv = now.upcv;
			next.x = new int [next.step];
			for(int i = 1; i < ns; i ++)
				next.x[i] = now.x[i];
			next.x[ns] = 1;
			Q.push(next);
		}

		//0 - branch 左子树
		next.cv = now.cv;
		next.cw = now.cw;
		next.step = ns + 1;
		float t = bound(next);
		if(t > bv){
			next.upcv = t;
			next.x = new int[ns];
			for(int i = 1; i < ns; i ++)
				next.x[i] = now.x[i];
			next.x[now.step] = 0;
			Q.push(next);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
	cout << "请输入物品数目n与背包容量w" << endl;
	cin >> n >> w;
	//毫秒级别的时间性能分析
	LARGE_INTEGER frequency;
    LARGE_INTEGER start_time;
    LARGE_INTEGER end_time;
    double elapsed_time;

    QueryPerformanceFrequency(&frequency);

	// 分支限界法
    double total_force_time = 0.0;
    for (int measurement = 0; measurement < 10; measurement++) {
		x = new int[n + 1];
		bx = new int[n + 1];
		a = new goods[n + 1];
        for (int i = 1; i <= n; i++) {
            a[i].w = rand() % 100;
            a[i].v = rand() % 100;
            a[i].no = i;
        }

        QueryPerformanceCounter(&start_time);
		sort(a + 1,a + 1 + n,cmp);
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_force_time += elapsed_time;
		delete []x;
		delete []bx;
		delete []a;
    }

    double average_force_time = total_force_time / 10;
    cout << "分支限界法平均执行时间: " << average_force_time << " 毫秒" << endl;
	
	/*cout << "请依次输入物品重量:" << endl;
	for( int i = 1;i <= n;i ++)
		cin >> a[i].w;
	cout << "请依次输入物品价值:" << endl;
	for(int i = 1;i <= n;i ++)
		cin >> a[i].v;
	for(int i = 1;i < n + 1; i ++)
		a[i].no = i;
	sort(a + 1,a + 1 + n,cmp);
	pfs();
	for(int i = 1; i < n + 1; i ++)
		x[a[i].no] = bx[i];//序号还原
	cout << "最大价值是" << bv << endl;
	cout << "最优解是（1表示选取该物品，0表示不选）" << endl;
	for(int i = 1; i < n + 1; i ++)
		printf("%d ",x[i]);
	printf("\n");*/

	system("pause");
	return 0;
}

