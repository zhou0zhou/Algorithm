// ʵ��8 01������ʱ�����ܷ���.cpp : �������̨Ӧ�ó������ڵ㡣
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
#define MAXN 10000 //������Ʒ��
#define MAXW 10000 //�����������

int n,W;//n����Ʒ����������ΪW
int x[MAXN];//������
int w[MAXN],v[MAXN];//��Ʒ�����ͼ�ֵ
int bestv;//������Ž���ܼ�ֵ
//��̬�滮���ݽṹ
int dp[MAXN][MAXN];//dp[i][j]��ʾ��i����Ʒѡ������Ϊj�ı���������ֵ��
//���� ̰�����ݽṹ
struct NodeType{
	int w;
	int v;
	double p;//�Լ۱� p = v/w
	bool operator<(const NodeType& s)const{
		return p > s.p;
	}
};
NodeType A[MAXN];
//���ݷ����ݽṹ
bool best_x[MAXN];//�洢���ŷ���
int now_v;//��ǰ��ֵ
int remain_v;//ʣ���ֵ
int now_w;//��ǰ����
int best_v;//���ż�ֵ
//������
int cv,cw,cx[MAXN];
int forcesolution(int i){
	if(i > n){//�ж��ǲ���Ҷ�ӽڵ� �ǵĻ�ֱ�ӻ������
		if(bestv < cv && cw <= W){
			for(int k = 1; k <= n; k ++)
				x[k] = cx[k];//�洢����·��
			bestv = cv;
		}
		return bestv;
	}
	cw = cw + A[i].w;
	cv = cv + A[i].v;
	cx[i] = 1;//װ�뱳��
	forcesolution(i + 1);//������һ�� 

	cw = cw - A[i].w;
	cv = cv - A[i].v;
	cx[i] = 0;//��װ�뱳��
	forcesolution(i + 1);

	return bestv;
}

//��̬�滮
void dpsolution(){
	int i,j;
	for(i = 0;i <= n; i ++)//�ñ߽�����dp[i][0] = 0
		dp[i][0] = 0;
	for(j = 0;j <= n; j ++)//�ñ߽�����dp[0][j] = 0
		dp[0][j] = 0;
	for(i = 1;i <= n; i ++){
		for(j = 1; j <= W; j ++){
			if(j < w[i])
				dp[i][j] = dp[i - 1][j];
			else  //ѡ�벻ѡ�Ľϴ�ֵ
				dp[i][j] = max(dp[i - 1][j],dp[i - 1][j - w[i]] + v[i]);
		}
	}
}
void Buildx(){//���������Ž� x[i]Ϊ1��Ϊװ�뱳������Ʒ
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

//̰�� ����λ�Լ۱�
void greedysolution(){
	bestv = 0;//��ʼ��Ϊ0
	int weight = W;
	memset(x,0,sizeof(x));//��ʼ��������
	int i = 1;
	while(A[i].w <= weight){
		x[i] = 1;
		weight -= A[i].w;
		bestv += A[i].v;
		i ++;
	}
}

//���ݷ�
int Bound(int k){//�����֧�ڵ�k���Ͻ�
	remain_v = 0;
	while(k <= n){
		remain_v += v[k];
		k ++;
	}
	return remain_v + now_v;
}
void Backtrack(int t){//tΪ��չ������������ڵĲ��
	if(t > n){//�Ƿ񵽴�Ҷ�ӽڵ� 
		for(int i = 1; i <= n; i ++)
			best_x[i] = x[i];//��¼���ݵ��������
		best_v = now_v;//��¼�����е����ż�ֵ
		return;
	}
	//Լ��������֦������չ��㴦��ȥ������Լ��������
	if(now_w + w[t] <= W){// Լ������ �ж��Ƿ������������ ���뿼���������������������� 
		x[t] = 1;
		now_w += w[t];
		now_v += v[t];
		Backtrack(t + 1);//�ٽ�����һ���ڵ�ķ���
		now_w -= w[t];//�ڵ���Ҷ�ӽڵ����л���һ���ڵ�
		now_v -= v[t];
	}
	if(Bound(t + 1) > best_v){//�޽�������֦����ȥ�ò������Ž������ 
		//�������t������Լ����������е��˴���Ȼ���ж�����ǰ��ֵ��ʣ���ֵû�����ţ������ٱ���ȥ��
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
	//���� ��1��ʼ
	Backtrack(1);
    /*cout << "ѡȡ��Ʒ��Ϊ��" << endl;
    for (int i = 1; i <= n; i++) {
        if(x[i] == 1)
            cout << i << " ";
    }
	cout << "�ܼ�ֵΪ��" << best_v << endl;*/
}
//չʾ���
void show(){
	printf("ѡȡ��Ʒ��Ϊ:");
	for(int i = 1; i <= n; i ++)
		if(x[i] == 1)
			printf("%d ",i);
	printf("\n");
	printf("�ܼ�ֵΪ%d\n",bestv);
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "0/1��������" << endl;
	cout << "��������Ʒ�����뱳�������� n��W" << endl;
	cin >> n >> W;
	/*
	//�Ȳ��Ը��㷨����ȷ��
	cout << "�������������Ʒ���������ֵ"<< endl;
	for(int i = 1; i <= n; i ++)
		cin >> w[i] >> v[i];
	for(int i = 1; i <= n; i ++){
		A[i].w = w[i];
		A[i].v = v[i];
		A[i].p = (double)A[i].v / A[i].w;
	}
	forcesolution(1);
	cout <<"�������Ľ��"<< endl;
	show();
	cout << endl;
	dpsolution();
	Buildx();
	cout <<"��̬�滮�Ľ��"<< endl;
	show();
	cout << endl;
	cout <<"���ݷ��Ľ��"<< endl;
	tracksolution(W,n);
	cout << endl;
	sort(A + 1, A + n + 1);//���� �����Լ۱����� �����ݽṹ���Ѿ�����
    greedysolution();
	cout <<"̰�ķ��Ľ��"<< endl;
	show();*/

	//���뼶���ʱ�����ܷ���
	LARGE_INTEGER frequency;
    LARGE_INTEGER start_time;
    LARGE_INTEGER end_time;
    double elapsed_time;

    QueryPerformanceFrequency(&frequency);

	// ������
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
    cout << "������ƽ��ִ��ʱ��: " << average_force_time << " ����" << endl;
    // ��̬�滮
    double total_dp_time = 0.0;
    for (int measurement = 0; measurement < 10; measurement++) {//ÿ���㷨ִ��ʮ�Σ���ƽ��ʱ��
        for (int i = 0; i < n; i++) {//����������
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
    cout << "��̬�滮ƽ��ִ��ʱ��: " << average_dp_time << " ����" << endl;

    // ̰��
    double total_greedy_time = 0.0;
    for (int measurement = 0; measurement < 10; measurement++) {
        for (int i = 1; i <= n; i++) {
            A[i].w = rand() % 100;
            A[i].v = rand() % 100;
            A[i].p = (double)A[i].v / A[i].w;
        }

        QueryPerformanceCounter(&start_time);
        sort(A + 1, A + n + 1);//���� �����Լ۱����� �����ݽṹ���Ѿ�����
        greedysolution();
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_greedy_time += elapsed_time;
    }

    double average_greedy_time = total_greedy_time / 10;
    cout << "̰���㷨ƽ��ִ��ʱ��: " << average_greedy_time << " ����" << endl;

    // ���ݷ�
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
    cout << "���ݷ�ƽ��ִ��ʱ��: " << average_bb_time << " ����" << endl;

	system("pause");
    return 0;
}
