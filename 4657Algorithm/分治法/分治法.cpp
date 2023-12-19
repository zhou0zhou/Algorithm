// 分治法.cpp : 定义控制台应用程序的入口点。
//1.归并排序与快速排序的分治方法 希尔排序
//2.棋盘覆盖问题
//参考博客 https://blog.csdn.net/weixin_46379561/article/details/118914830?ops_request_misc=&request_id=&biz_id=102&utm_term=4x4%E7%9A%84%E6%A3%8B%E7%9B%98%E8%A6%86%E7%9B%96%E9%97%AE%E9%A2%98%E6%89%A7%E8%A1%8C%E8%BF%87%E7%A8%8B&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-118914830.142^v96^pc_search_result_base8&spm=1018.2226.3001.4187
//3.最近对问题 数据结构定义在Fundament.cpp
//参考：https://blog.csdn.net/weixin_44533129/article/details/103125495?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169829073016800222827648%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=169829073016800222827648&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-5-103125495-null-null.142^v96^pc_search_result_base8&utm_term=%E6%9C%80%E8%BF%91%E5%AF%B9%E9%97%AE%E9%A2%98&spm=1018.2226.3001.4187
//4.习题6.2 求一个数组的最大元素
//5.习题6.6 判断给定值是否在n * n的整形矩阵中

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
#define min(x,y) ((x) < (y) ? (x) : (y))
#define INF 32767
#define MAXN 20
#define N 4

int board[128][128];//模拟棋盘
int tile = 1;//用于编号已覆盖的方格

//1.合并排序 希尔排序
//合并r[s]~r[m]与r[m+1]~r[t]两个已排序子序列
void Merge(int r[],int s,int m,int t){
	int r1[99];
	int i = s,j = m + 1,k = s;
	while(i <= m && j <= t){//将较小的数放入r1[k]中
		if(r[i] <= r[j]) r1[k++] = r[i++];
		else r1[k++] = r[j++];
	}
	while(i <= m)//处理第一个子序列的剩余记录
		r1[k++] = r[i++];
	while(j <= t)//处理第二个子序列的剩余记录
		r1[k++] = r[j++];
	for(i = s;i <= t; i ++)//将合并结果传回r
		r[i] = r1[i];
}
//归并排序 对序列 r[s]~r[t]进行归并排序
void MergeSort(int r[],int s,int t){
	if(s == t) return ;
	else{
		int m = (s + t)/2;
		MergeSort(r,s,m);
		MergeSort(r,m + 1,t);
		Merge(r,s,m,t);
	}
}

//快速排序 划分
int Partition(int r[],int first,int end){
	int temp,i = first,j = end;
	while(i < j){
		while(i < j && r[i] <= r[j]) j --;//从右侧扫描
		if(i < j){ //将较小记录交换到前面
			temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			i ++;
		}
		while(i < j && r[i] <= r[j]) i ++;//从左侧扫描
		if(i < j){ //将较大记录交换到后面
			temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			j --;
		}
	}
	return i; //返回轴值记录的位置
}

//快速排序
void QuickSort(int r[],int first,int end){
	if (first < end){
		int pivot = Partition(r,first,end);
		QuickSort(r,first,pivot - 1);
		QuickSort(r,pivot + 1,end);
	}
}
//希尔排序
void shellsort(int data[],int n){//data是待排序数组 长度为n
	int *delta,k,i,t,dk,j; //delta 是步长数组 delta1 = n/2 之后每个除2 deltak = 1
	k = n;//k 是排序趟数
	delta = (int *)malloc(sizeof(int) * (n/2));//最多有Log n个元素
	i = 0;
	do{
		k = k / 2;
		delta[i ++] = k;
	}while(k > 1);

	i = 0;
	while((dk = delta[i]) > 0){
		for(k = delta[i]; k < n; ++k)
			if(data[k - dk] > data[k]){
				t = data[k];
				for(j = k - dk;j >= 0 && t < data[j]; j -= dk)
					data[j + dk] = data [j];
				data[j + dk] = t;
			}
			++ i;
	}
}

//2.棋盘覆盖算法
// (tr,tc)表示棋盘的左上角坐标(即确定棋盘位置), (dr,dc)表示特殊方块的位置, size=2^k确定棋盘大小
void ChessBoard(int tr, int tc, int dr, int dc, int size){
    // 递归出口
    if (size == 1)
        return;
    int s = size / 2; //分割棋盘
    int t = tile++;   //t记录本层骨牌序号
    
	//依次按照左上 右上 左下 右下的顺序覆盖 直到每一块都覆盖完毕

    if (dr < tr + s && dc < tc + s)    // 判断特殊方格在不在左上棋盘
        ChessBoard(tr, tc, dr, dc, s); //特殊方格在左上棋盘 递归处理子棋盘
    else{
        board[tr + s - 1][tc + s - 1] = t;             // 用t号的L型骨牌覆盖右下角
        ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s); // 递归覆盖其余方格
    }
    // 判断特殊方格在不在右上棋盘
    if (dr < tr + s && dc >= tc + s)
        ChessBoard(tr, tc + s, dr, dc, s);
    else{
        board[tr + s - 1][tc + s] = t;
        ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);
    }
    // 判断特殊方格在不在左下棋盘
    if (dr >= tr + s && dc < tc + s)
        ChessBoard(tr + s, tc, dr, dc, s);
    else{
        board[tr + s][tc + s - 1] = t;
        ChessBoard(tr + s, tc, tr + s, tc + s - 1, s);
    }

    // 判断特殊方格在不在右下棋盘
    if (dr >= tr + s && dc >= tc + s)
        ChessBoard(tr + s, tc + s, dr, dc, s);
    else{
        board[tr + s][tc + s] = t;
        ChessBoard(tr + s, tc + s, tr + s, tc + s, s);
    }
}

//3.最近对问题
int sign(double x){ //返回数值的符号
	if(x > 0) return 1;
	else if(x < 0) return -1;
	else return 0;
}

double sqr(double x){ //求x的平方
	return x*x;
}

class Point{
public:
	double x;
	double y;
	Point(){}
	Point(double x1,double y1){
		x = x1;
		y = y1;
	}
	void disp(){
		printf("(%g,%g)",x,y);
	}
	friend double Distance(Point p1,Point p2);//求两个点的距离
};

double Distance(Point p1,Point p2){
	return sqrt((p1.x - p2.x) * (p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y));
}
//3.1蛮力法直接遍历
double ClosestPoints(vector<Point> a,int leftindex,int rightindex){
	int i,j;
	double d,mindist = INF;
	for(i = leftindex;i <= rightindex; i++){
		for(j = i + 1;j <= rightindex;j ++){
			d = Distance(a[i],a[j]);
			if(d < mindist)
				mindist = d;
		}
	}
		return mindist;
}
void display(vector<Point> a,int leftindex,int rightindex){
	int i;
	for(i = leftindex;i <= rightindex;i ++)
		a[i].disp();
	cout << endl;
}
//3.2 分治法 三种情况 递归
bool pointxcmp(Point &p1,Point &p2){//用于按X坐标递增排序
	return p1.x < p2.x;
}

bool pointycmp(Point &p1,Point &p2){//用于按Y坐标递增排序
	return p1.y < p2.y;
}
//求a[leftindex..rightindex]中最近点对的距离
double ClosestPoints11(vector<Point> &a,vector<Point> &b,int leftindex,int rightindex){
	vector<Point> leftb,rightb,b1;
	int i,j,midindex;
	double d1,d2,d3 = INF,d;
	if((rightindex - leftindex+1) <= 3){ //少于四个点 直接蛮力法
		d = ClosestPoints(a,leftindex,rightindex);
		return d;
	}
	midindex = (leftindex + rightindex)/2;//求中间位置
	for(i = 0;i < b.size();i ++)//将b中点集分为左右两部分
		if(b[i].x < a[midindex].x)
			leftb.push_back(b[i]);
		else rightb.push_back(b[i]);
	d1 = ClosestPoints11(a,leftb,leftindex,midindex);
	d2 = ClosestPoints11(a,rightb,midindex+1,rightindex);
	d = min(d1,d2);//当前最小距离为两个点都在左半部分或者右半部分的最小值
	//求一个在左，一个在右的情况下的最小距离
	for(i = 0;i < b.size();i ++)
		//将b中间宽度为2*d的带状区域内的子集复制到b1中
		if(fabs(b[i].x - a[midindex].x)<=d)
			b1.push_back(b[i]);
	double tmpd3;
	for(i = 0; i < b1.size();i ++) //求b1中最近点对
		for(j = i + 1;j < b1.size(); j ++){
			if(b1[j].y - b1[i].y >= d) break;
			tmpd3 = Distance(b1[i],b1[j]);
			if(tmpd3<d3)
				d3 = tmpd3;
		}
	d = min(d,d3);
	return d;
}
//求a[leftindex..rightindex]中最近点对的距离
double ClosestPoints1(vector<Point> &a,int leftindex,int rightindex){
	int i;
	vector<Point> b;
	vector<Point>::iterator it;
	printf("排序前：\n");
	for(it = a.begin();it != a.end();it++)
		(*it).disp();
	printf("\n");
	sort(a.begin(),a.end(),pointxcmp);//按x坐标从小到大排序
	printf("按x坐标排序后：\n");
	for(it = a.begin(); it != a.end();it++)
		(*it).disp();
	printf("\n");

	for(i = 0;i < a.size();i ++) //将a中点集复制到b中
		b.push_back(a[i]);

	sort(a.begin(),a.end(),pointycmp);//按y坐标从小到大排序
	printf("按y坐标排序后：\n");
	for(it = a.begin(); it != a.end();it++)
		(*it).disp();
	printf("\n");
	return ClosestPoints11(a,b,0,a.size()-1);
}
//6.2
int findMax(int arr[],int left,int right){
	if(left == right)
		return arr[left];
	int mid = (left + right) / 2;
	int maxleft = findMax(arr,left,mid);
	int maxright = findMax(arr,mid + 1,right);
	return (maxleft > maxright) ? maxleft : maxright;
}

//6.6 矩阵右上角的元素是行中最大，列中最小 每次比较都可以排除一行/一列
//矩阵M：（n * n）从左到右从上到下按升序排列
int searchM(int M[N][N],int n,int x){
	if(n <= 0)
		return 0;//矩阵为空，返回
	int row = 0,rol = n - 1;//从第一行，最后一列开始
	while(row < n && rol >= 0){
		int current = M[row][rol];
		if(current == x){
			printf("%d在%d行%d列\n",x,row,rol);
			return 1;
		}
		else if(current > x)
			rol --;//排除当前列
		else 
			row ++;//排除当前行
	}
	printf("%d不存在于矩阵中\n",x);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[10] = {1,3,5,56,98,19,20,40,60,7};
	cout << "数列最大值为：" << findMax(a,0,9) << endl;
	int b[4][4] = {1,3,5,7,2,4,6,8,3,5,7,9,4,7,9,11};
	searchM(b,4,12);
	searchM(b,4,11);
	//三种排序
	int n = 10;
	int arr[99];
	for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
	MergeSort(arr,0,n-1);
	cout << "归并排序结果如下"<< endl;
	for(int i = 0; i < n; i ++)
		cout << arr[i] << " ";
	cout << endl;

	for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
	QuickSort(arr,0,n-1);
	cout << "快速排序结果如下"<< endl;
	for(int i = 0; i < n; i ++)
		cout << arr[i] << " ";
	cout << endl;

	for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
	shellsort(arr,10);
	cout << "希尔排序结果如下"<< endl;
	for(int i = 0; i < n; i ++)
		cout << arr[i] << " ";
	cout << endl;

	//棋盘覆盖
	int boardSize = 8;                 // 棋盘边长
    ChessBoard(0, 0, 3, 3, boardSize); // (0, 0)为顶点，大小为boardSize的棋盘； 特殊方块位于(3，3）
    // 打印棋盘
    int i, j;
    printf("模拟棋盘覆盖\n\n");
    for (i = 0; i < boardSize; i++)
    { 
        for (j = 0; j < boardSize; j++)
        {
            printf("%d\t", board[i][j]);
        }
        printf("\n\n\n");
    }
	/*4X4的棋盘覆盖模拟
	int boardSize = 4;                 // 棋盘边长
    ChessBoard(0, 0, 0, 1, boardSize); // (0, 0)为顶点，大小为boardSize的棋盘； 特殊方块位于(0.1）
	/*模拟4X4的执行过程：
	参考博客https://blog.csdn.net/weixin_46379561/article/details/118914830?ops_request_misc=&request_id=&biz_id=102&utm_term=4x4%E7%9A%84%E6%A3%8B%E7%9B%98%E8%A6%86%E7%9B%96%E9%97%AE%E9%A2%98%E6%89%A7%E8%A1%8C%E8%BF%87%E7%A8%8B&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-118914830.142^v96^pc_search_result_base8&spm=1018.2226.3001.4187
	void ChessBoard(int tr, int tc, int dr, int dc, int size)
	左上角无特殊方块时 可以把右下角当作特殊方块 添加一个L型骨盘
	左下角                   右上角 （...)
	*/
    // 打印棋盘
	/*
    int i, j;
    printf("模拟棋盘覆盖\n\n");
    for (i = 0; i < boardSize; i++)
    { 
        for (j = 0; j < boardSize; j++)
        {
            printf("%d\t", board[i][j]);
        }
        printf("\n\n\n");
    }

	//最近点对的测试
	vector<Point> a;
	a.push_back(Point(4,10));
	a.push_back(Point(3,7));
	a.push_back(Point(9,7));
	a.push_back(Point(3,4));
	a.push_back(Point(5,6));
	a.push_back(Point(5,4));
	a.push_back(Point(6,3));
	a.push_back(Point(8,1));
	a.push_back(Point(3,0));
	a.push_back(Point(1,6));
	double mindist=ClosestPoints1(a,0,a.size()-1);
	printf("最近距离=%g\n",mindist);*/

	system("pause");
	return 0;
}