// ���η�.cpp : �������̨Ӧ�ó������ڵ㡣
//1.�鲢�������������ķ��η��� ϣ������
//2.���̸�������
//�ο����� https://blog.csdn.net/weixin_46379561/article/details/118914830?ops_request_misc=&request_id=&biz_id=102&utm_term=4x4%E7%9A%84%E6%A3%8B%E7%9B%98%E8%A6%86%E7%9B%96%E9%97%AE%E9%A2%98%E6%89%A7%E8%A1%8C%E8%BF%87%E7%A8%8B&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-118914830.142^v96^pc_search_result_base8&spm=1018.2226.3001.4187
//3.��������� ���ݽṹ������Fundament.cpp
//�ο���https://blog.csdn.net/weixin_44533129/article/details/103125495?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169829073016800222827648%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=169829073016800222827648&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-5-103125495-null-null.142^v96^pc_search_result_base8&utm_term=%E6%9C%80%E8%BF%91%E5%AF%B9%E9%97%AE%E9%A2%98&spm=1018.2226.3001.4187
//4.ϰ��6.2 ��һ����������Ԫ��
//5.ϰ��6.6 �жϸ���ֵ�Ƿ���n * n�����ξ�����

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

int board[128][128];//ģ������
int tile = 1;//���ڱ���Ѹ��ǵķ���

//1.�ϲ����� ϣ������
//�ϲ�r[s]~r[m]��r[m+1]~r[t]����������������
void Merge(int r[],int s,int m,int t){
	int r1[99];
	int i = s,j = m + 1,k = s;
	while(i <= m && j <= t){//����С��������r1[k]��
		if(r[i] <= r[j]) r1[k++] = r[i++];
		else r1[k++] = r[j++];
	}
	while(i <= m)//�����һ�������е�ʣ���¼
		r1[k++] = r[i++];
	while(j <= t)//����ڶ��������е�ʣ���¼
		r1[k++] = r[j++];
	for(i = s;i <= t; i ++)//���ϲ��������r
		r[i] = r1[i];
}
//�鲢���� ������ r[s]~r[t]���й鲢����
void MergeSort(int r[],int s,int t){
	if(s == t) return ;
	else{
		int m = (s + t)/2;
		MergeSort(r,s,m);
		MergeSort(r,m + 1,t);
		Merge(r,s,m,t);
	}
}

//�������� ����
int Partition(int r[],int first,int end){
	int temp,i = first,j = end;
	while(i < j){
		while(i < j && r[i] <= r[j]) j --;//���Ҳ�ɨ��
		if(i < j){ //����С��¼������ǰ��
			temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			i ++;
		}
		while(i < j && r[i] <= r[j]) i ++;//�����ɨ��
		if(i < j){ //���ϴ��¼����������
			temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			j --;
		}
	}
	return i; //������ֵ��¼��λ��
}

//��������
void QuickSort(int r[],int first,int end){
	if (first < end){
		int pivot = Partition(r,first,end);
		QuickSort(r,first,pivot - 1);
		QuickSort(r,pivot + 1,end);
	}
}
//ϣ������
void shellsort(int data[],int n){//data�Ǵ��������� ����Ϊn
	int *delta,k,i,t,dk,j; //delta �ǲ������� delta1 = n/2 ֮��ÿ����2 deltak = 1
	k = n;//k ����������
	delta = (int *)malloc(sizeof(int) * (n/2));//�����Log n��Ԫ��
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

//2.���̸����㷨
// (tr,tc)��ʾ���̵����Ͻ�����(��ȷ������λ��), (dr,dc)��ʾ���ⷽ���λ��, size=2^kȷ�����̴�С
void ChessBoard(int tr, int tc, int dr, int dc, int size){
    // �ݹ����
    if (size == 1)
        return;
    int s = size / 2; //�ָ�����
    int t = tile++;   //t��¼����������
    
	//���ΰ������� ���� ���� ���µ�˳�򸲸� ֱ��ÿһ�鶼�������

    if (dr < tr + s && dc < tc + s)    // �ж����ⷽ���ڲ�����������
        ChessBoard(tr, tc, dr, dc, s); //���ⷽ������������ �ݹ鴦��������
    else{
        board[tr + s - 1][tc + s - 1] = t;             // ��t�ŵ�L�͹��Ƹ������½�
        ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s); // �ݹ鸲�����෽��
    }
    // �ж����ⷽ���ڲ�����������
    if (dr < tr + s && dc >= tc + s)
        ChessBoard(tr, tc + s, dr, dc, s);
    else{
        board[tr + s - 1][tc + s] = t;
        ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);
    }
    // �ж����ⷽ���ڲ�����������
    if (dr >= tr + s && dc < tc + s)
        ChessBoard(tr + s, tc, dr, dc, s);
    else{
        board[tr + s][tc + s - 1] = t;
        ChessBoard(tr + s, tc, tr + s, tc + s - 1, s);
    }

    // �ж����ⷽ���ڲ�����������
    if (dr >= tr + s && dc >= tc + s)
        ChessBoard(tr + s, tc + s, dr, dc, s);
    else{
        board[tr + s][tc + s] = t;
        ChessBoard(tr + s, tc + s, tr + s, tc + s, s);
    }
}

//3.���������
int sign(double x){ //������ֵ�ķ���
	if(x > 0) return 1;
	else if(x < 0) return -1;
	else return 0;
}

double sqr(double x){ //��x��ƽ��
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
	friend double Distance(Point p1,Point p2);//��������ľ���
};

double Distance(Point p1,Point p2){
	return sqrt((p1.x - p2.x) * (p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y));
}
//3.1������ֱ�ӱ���
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
//3.2 ���η� ������� �ݹ�
bool pointxcmp(Point &p1,Point &p2){//���ڰ�X�����������
	return p1.x < p2.x;
}

bool pointycmp(Point &p1,Point &p2){//���ڰ�Y�����������
	return p1.y < p2.y;
}
//��a[leftindex..rightindex]�������Եľ���
double ClosestPoints11(vector<Point> &a,vector<Point> &b,int leftindex,int rightindex){
	vector<Point> leftb,rightb,b1;
	int i,j,midindex;
	double d1,d2,d3 = INF,d;
	if((rightindex - leftindex+1) <= 3){ //�����ĸ��� ֱ��������
		d = ClosestPoints(a,leftindex,rightindex);
		return d;
	}
	midindex = (leftindex + rightindex)/2;//���м�λ��
	for(i = 0;i < b.size();i ++)//��b�е㼯��Ϊ����������
		if(b[i].x < a[midindex].x)
			leftb.push_back(b[i]);
		else rightb.push_back(b[i]);
	d1 = ClosestPoints11(a,leftb,leftindex,midindex);
	d2 = ClosestPoints11(a,rightb,midindex+1,rightindex);
	d = min(d1,d2);//��ǰ��С����Ϊ�����㶼����벿�ֻ����Ұ벿�ֵ���Сֵ
	//��һ������һ�����ҵ�����µ���С����
	for(i = 0;i < b.size();i ++)
		//��b�м���Ϊ2*d�Ĵ�״�����ڵ��Ӽ����Ƶ�b1��
		if(fabs(b[i].x - a[midindex].x)<=d)
			b1.push_back(b[i]);
	double tmpd3;
	for(i = 0; i < b1.size();i ++) //��b1��������
		for(j = i + 1;j < b1.size(); j ++){
			if(b1[j].y - b1[i].y >= d) break;
			tmpd3 = Distance(b1[i],b1[j]);
			if(tmpd3<d3)
				d3 = tmpd3;
		}
	d = min(d,d3);
	return d;
}
//��a[leftindex..rightindex]�������Եľ���
double ClosestPoints1(vector<Point> &a,int leftindex,int rightindex){
	int i;
	vector<Point> b;
	vector<Point>::iterator it;
	printf("����ǰ��\n");
	for(it = a.begin();it != a.end();it++)
		(*it).disp();
	printf("\n");
	sort(a.begin(),a.end(),pointxcmp);//��x�����С��������
	printf("��x���������\n");
	for(it = a.begin(); it != a.end();it++)
		(*it).disp();
	printf("\n");

	for(i = 0;i < a.size();i ++) //��a�е㼯���Ƶ�b��
		b.push_back(a[i]);

	sort(a.begin(),a.end(),pointycmp);//��y�����С��������
	printf("��y���������\n");
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

//6.6 �������Ͻǵ�Ԫ�����������������С ÿ�αȽ϶������ų�һ��/һ��
//����M����n * n�������Ҵ��ϵ��°���������
int searchM(int M[N][N],int n,int x){
	if(n <= 0)
		return 0;//����Ϊ�գ�����
	int row = 0,rol = n - 1;//�ӵ�һ�У����һ�п�ʼ
	while(row < n && rol >= 0){
		int current = M[row][rol];
		if(current == x){
			printf("%d��%d��%d��\n",x,row,rol);
			return 1;
		}
		else if(current > x)
			rol --;//�ų���ǰ��
		else 
			row ++;//�ų���ǰ��
	}
	printf("%d�������ھ�����\n",x);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[10] = {1,3,5,56,98,19,20,40,60,7};
	cout << "�������ֵΪ��" << findMax(a,0,9) << endl;
	int b[4][4] = {1,3,5,7,2,4,6,8,3,5,7,9,4,7,9,11};
	searchM(b,4,12);
	searchM(b,4,11);
	//��������
	int n = 10;
	int arr[99];
	for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
	MergeSort(arr,0,n-1);
	cout << "�鲢����������"<< endl;
	for(int i = 0; i < n; i ++)
		cout << arr[i] << " ";
	cout << endl;

	for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
	QuickSort(arr,0,n-1);
	cout << "��������������"<< endl;
	for(int i = 0; i < n; i ++)
		cout << arr[i] << " ";
	cout << endl;

	for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
	shellsort(arr,10);
	cout << "ϣ������������"<< endl;
	for(int i = 0; i < n; i ++)
		cout << arr[i] << " ";
	cout << endl;

	//���̸���
	int boardSize = 8;                 // ���̱߳�
    ChessBoard(0, 0, 3, 3, boardSize); // (0, 0)Ϊ���㣬��СΪboardSize�����̣� ���ⷽ��λ��(3��3��
    // ��ӡ����
    int i, j;
    printf("ģ�����̸���\n\n");
    for (i = 0; i < boardSize; i++)
    { 
        for (j = 0; j < boardSize; j++)
        {
            printf("%d\t", board[i][j]);
        }
        printf("\n\n\n");
    }
	/*4X4�����̸���ģ��
	int boardSize = 4;                 // ���̱߳�
    ChessBoard(0, 0, 0, 1, boardSize); // (0, 0)Ϊ���㣬��СΪboardSize�����̣� ���ⷽ��λ��(0.1��
	/*ģ��4X4��ִ�й��̣�
	�ο�����https://blog.csdn.net/weixin_46379561/article/details/118914830?ops_request_misc=&request_id=&biz_id=102&utm_term=4x4%E7%9A%84%E6%A3%8B%E7%9B%98%E8%A6%86%E7%9B%96%E9%97%AE%E9%A2%98%E6%89%A7%E8%A1%8C%E8%BF%87%E7%A8%8B&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-118914830.142^v96^pc_search_result_base8&spm=1018.2226.3001.4187
	void ChessBoard(int tr, int tc, int dr, int dc, int size)
	���Ͻ������ⷽ��ʱ ���԰����½ǵ������ⷽ�� ���һ��L�͹���
	���½�                   ���Ͻ� ��...)
	*/
    // ��ӡ����
	/*
    int i, j;
    printf("ģ�����̸���\n\n");
    for (i = 0; i < boardSize; i++)
    { 
        for (j = 0; j < boardSize; j++)
        {
            printf("%d\t", board[i][j]);
        }
        printf("\n\n\n");
    }

	//�����ԵĲ���
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
	printf("�������=%g\n",mindist);*/

	system("pause");
	return 0;
}