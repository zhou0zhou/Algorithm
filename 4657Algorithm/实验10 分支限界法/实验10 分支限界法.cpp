// ʵ��10 ��֧�޽編.cpp : �������̨Ӧ�ó������ڵ㡣
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
	int cv,cw;//��ǰ��ֵ�͵�ǰ����
	int step;//��step����Ʒ
	int *x;
	float upcv;//�Ͻ�
	bool operator < (const node &b) const{//��������� �����Ͻ�����
		return upcv < b.upcv;
	}
};
typedef struct{
	int w,v,no;
}goods;//��Ʒ

int n,w;//��Ʒ��������������
goods *a;
int bv,*x,*bx;//����ֵ����ǰ�⣬���Ž�

int cmp(goods a,goods b){
	return a.v * b.w >= a.w * b.v;//����λ��ֵ����
}
float bound(node st){//�����޽纯��
	//����̰�ķ���ñ������������ֵ
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

void pfs(){//���ȶ�����������
	node now,next;
	int i,ns;
	priority_queue <node> Q;//�������ȶ���Q����ʼ��
	now.cv = now.cw = 0;
	now.step = 1;
	now.x = new int[now.step];
	now.upcv = bound(now);
	Q.push(now);//������
	while(!Q.empty()){//�Ӳ���
		now = Q.top();
		Q.pop();
		if(now.upcv <= bv)//���ýڵ������Ͻ�ȵ�ǰ����ֵСʱֱ�ӽ���
			break;
		//���� ��������ֵ�Ľ�
		ns = now.step;
		if(ns == n + 1){
			if(now.cv > bv){
				bv = now.cv;
				for(int i = 1;i <= n;i ++)//������
					bx[i] = now.x[i];
			}
			continue;
		}

		//1 - branch ������
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

		//0 - branch ������
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
	cout << "��������Ʒ��Ŀn�뱳������w" << endl;
	cin >> n >> w;
	//���뼶���ʱ�����ܷ���
	LARGE_INTEGER frequency;
    LARGE_INTEGER start_time;
    LARGE_INTEGER end_time;
    double elapsed_time;

    QueryPerformanceFrequency(&frequency);

	// ��֧�޽編
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
    cout << "��֧�޽編ƽ��ִ��ʱ��: " << average_force_time << " ����" << endl;
	
	/*cout << "������������Ʒ����:" << endl;
	for( int i = 1;i <= n;i ++)
		cin >> a[i].w;
	cout << "������������Ʒ��ֵ:" << endl;
	for(int i = 1;i <= n;i ++)
		cin >> a[i].v;
	for(int i = 1;i < n + 1; i ++)
		a[i].no = i;
	sort(a + 1,a + 1 + n,cmp);
	pfs();
	for(int i = 1; i < n + 1; i ++)
		x[a[i].no] = bx[i];//��Ż�ԭ
	cout << "����ֵ��" << bv << endl;
	cout << "���Ž��ǣ�1��ʾѡȡ����Ʒ��0��ʾ��ѡ��" << endl;
	for(int i = 1; i < n + 1; i ++)
		printf("%d ",x[i]);
	printf("\n");*/

	system("pause");
	return 0;
}

