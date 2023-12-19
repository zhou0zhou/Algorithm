// ʵ��6 ̰��.cpp : �������̨Ӧ�ó������ڵ㡣
//�ϲ��ַ��������������룩prime 
//https://blog.csdn.net/xiangjunyes/article/details/106026830?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169949879516800185847742%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=169949879516800185847742&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-8-106026830-null-null.142^v96^pc_search_result_base6&utm_term=%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95%20%E5%90%88%E5%B9%B6%E5%AD%97%E7%AC%A6%E4%B8%B2%20%E5%93%88%E5%A4%AB%E6%9B%BC%E7%BC%96%E7%A0%81&spm=1018.2226.3001.4187
//ǰ׺�룺��ÿһ���ַ��涨һ��0��1����Ϊ����� ��Ҫ�������ַ��Ĵ��붼���������ַ������ǰ׺ ǰ׺���ܹ���֤����ֻ��һ��Ψһ��������
//���Զ��ڸ������ַ��������������������ת��Ϊ��Ѱ��ʹƽ���볤�ﵽ��С��ǰ׺���������
//0/1���� ����
//https://blog.csdn.net/qq_67764134/article/details/129903263?ops_request_misc=&request_id=&biz_id=102&utm_term=%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95%E6%B1%8201%E8%83%8C%E5%8C%85&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-129903263.142^v96^pc_search_result_base8&spm=1018.2226.3001.4187
//https://blog.csdn.net/qq_43561370/article/details/108210766?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_utm_term~default-0-108210766-blog-129903263.235^v38^pc_relevant_default_base3&spm=1001.2101.3001.4242.1&utm_relevant_index=3
//�����
//https://blog.csdn.net/m0_71272694/article/details/128058744?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169986601716777224428107%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169986601716777224428107&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_click~default-2-128058744-null-null.142^v96^pc_search_result_base8&utm_term=%E6%B4%BB%E5%8A%A8%E5%AE%89%E6%8E%92&spm=1018.2226.3001.4187

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <Windows.h>
using namespace std;

#define MAXCODELEN 100		//����ַ��������鳤��
#define MAXHAFF	100			//�����������ṹ���������
#define MAXCODE 100			//������������ṹ������ĸ���
#define MAXWEIGHT 10000     //���ƽ���볤

//1.����������
typedef struct Haffman{
	int weight;
	char ch;
	int parent;
	int leftchild;
	int rightchild;
}HaffmaNode;

typedef struct Code{
	int code[MAXCODELEN];
	int start;				//���ĸ�λ�ÿ�ʼ
}HaffmaCode;

HaffmaNode haffman[MAXHAFF];
HaffmaCode code[MAXCODE];

void buildHaffman(int all){ //������������Ĺ���
	//��ʼ��ǰ���Ƚ�ÿ���ڵ��Ȩ����0,���ڵ� ���Һ��Ӷ�-1
	for(int i = 0; i < all * 2 - 1; i ++){
		haffman[i].weight = 0;
		haffman[i].parent = -1;
		haffman[i].leftchild = -1;
		haffman[i].rightchild = -1;
	}
	cout << "��������Ҫ������������ַ���Ȩ�ش�С" << endl;
	for(int i = 0; i < all;i ++){
		cout <<"��ֱ������" << i <<"���������ַ���Ȩ��" << endl;
		cin >> haffman[i].ch;
		cin >> haffman[i].weight;
	}

	//ÿ����Ҫ�ҳ���С��Ȩ�صĽ�㣬�����µĽ�� ��Ҫall - 1�κϲ�
	int x1,x2,w1,w2;
	for(int i = 0; i < all - 1;i ++){
		x1 = x2 = -1;
		w1 = w2 = MAXWEIGHT;

		for(int j  = 0;j < all + i; ++ j){		//ÿ����all + i������� �õ���СȨ�صĽ��
			if(haffman[j].parent == -1 && haffman[j].weight < w1){//ÿ����С�ĸ��µĻ� Ҫ���ϴ���С�ĸ���С��
				w2 = w1;
				x2 = x1;
				x1 = j;
				w1 = haffman[j].weight;
			}else if(haffman[j].parent == -1 && haffman[j].weight < w2){ //���´�С�� ֻ�����w2����
				x2 = j;
				w2 = haffman[j].weight;
			}
		}
		//ÿ���ҵ���С���������Ҫ�ϲ�
		haffman[all + i].leftchild = x1;
		haffman[all + i].rightchild = x2;
		haffman[all + i].weight = w1 + w2;
		haffman[x1].parent = all + i;
		haffman[x2].parent = all + i;
		cout << "x1�� " << x1 << " x1�ĸ�����" << haffman[x1].parent << endl;
		cout << "x2�� " << x2 << " x2�ĸ�����" << haffman[x2].parent << endl;
		cout << "�½����" << all + i << " �½���Ȩ����" << haffman[all + i].weight << endl;
	}
}

void printCode(int all){
	HaffmaCode hCode; //���浱ǰҶ�ӽڵ���ַ�����
	int curParent;	  //��ǰ���ڵ�
	int c;			  //�±��Ҷ�ӽڵ�ı��
	for(int i = 0;i < all; i ++){
		hCode.start = all - 1;
		c = i;
		curParent = haffman[i].parent;

		while(curParent != -1){		//���ڵ�Ϊ-1��Ϊ���ڵ�
			//�Ը��ڵ�����Һ����ж� ��0��1 ���ǵĻ�Ҳȡ1
			if(haffman[curParent].leftchild == c){
				hCode.code[hCode.start] = 0;
				cout << "hCode.code[" << hCode.start << "] = 0" << endl;
			}else{
				hCode.code[hCode.start] = 1;
				cout << "hCode.code[" << hCode.start << "] = 1" << endl;
			}
			hCode.start --;
			c = curParent;
			curParent = haffman[c].parent;
		}
		//�洢��ǰ��Ҷ�ӽڵ���Ϣ������ṹ����
		for(int j  = hCode.start + 1;j < all; j ++)
			code[i].code[j] = hCode.code[j];
		code[i].start = hCode.start;
	}
}

//2.0/1����
struct node{
	int v;//��ֵ
	int w;//����
}wu[100];

bool cmp1(node a,node b){//�Ƚ�����
	if(a.w == b.w)
		return a.v > b.v;
	return a.w > b.w;
}

bool cmp2(node a,node b){//�Ƚϼ�ֵ
	if(a.v == b.v)
		return a.w < b.w;
	return a.v > b.v;
}

bool cmp3(node a,node b){//��λ��ֵ
	if((a.v/a.w) == (b.v/b.w))
		return a.w < b.w;
	return (a.v/a.w) > (b.v/b.w);
}

int func1(int n,int c){ //���������̰����ֵ
	sort(wu,wu + n,cmp1);
	int value = 0;
	for(int i = 0;i < n;i ++){
		if(c >= wu[i].w){
			c -= wu[i].w;
			value += wu[i].v;
		}
	}
	return value;
}

int func2(int n,int c){ //������ֵ̰����ֵ
	sort(wu,wu + n,cmp2);
	int value = 0;
	for(int i = 0;i < n;i ++){
		if(c >= wu[i].w){
			c -= wu[i].w;
			value += wu[i].v;
		}
	}
	return value;
}

int func3(int n,int c){ //�����λ��ֵ̰����ֵ
	sort(wu,wu + n,cmp3);
	int value = 0;
	for(int i = 0;i < n;i ++){
		if(c >= wu[i].w){
			c -= wu[i].w;
			value += wu[i].v;
		}
	}
	return value;
}

int random (int n,int c){ 
	int ans = -1,m = 1000;
	int flag,b[110];
	while(m --){
		int flag2 = 0,value = 0;
		for(int i = 0;i < n; i ++)
			b[i] = 1;
		while(1){
			flag = rand() % n;
			if(b[flag] != 0){
				if(flag2 + wu[flag].w <= c){
					flag2 += wu[flag].w;
					b[flag] = 0;
					value += wu[flag].v;
				}
			}else break;
		}
		if(value > ans)
			ans = value;
		return ans;
	}
}

//3.�����
struct Act{
	int beg;//��Ŀ�ʼʱ��
	int end;//��Ľ���ʱ��
	int index;//��ı��
	friend ostream & operator<<(ostream &o,const Act &A);   
	friend istream & operator>>(istream &o, Act &A);
};
//��������� ֱ����IO�������ѡ�����
ostream & operator<<(ostream &o,const Act &A){
	o<<A.beg<<"---"<<A.end<<" ";
	return o;
}

istream & operator>>(istream &o, Act &A){
	o>>A.index>>A.beg>>A.end;
	return o;
}

bool cmp(Act & act1,Act & act2){
	if(act1.end<act2.end){
		return true;
	}else
		return false;
}

vector<int> GreedySelector(vector<Act> & acts){
	//���Ȱѻ���ջ�Ľ���ʱ���������
	sort(acts.begin(),acts.end(),cmp);
	//�������Ļ������ѡ����еĻ
	vector<int> res;
	res.push_back(acts[0].index);//����ѡ�е�һ���
	int now = 0;//��ǰѡ�еĻ�±�
	for (int i = 1; i < acts.size(); i++){
		if(acts[i].beg>=acts[now].end){
			now = i;
			res.push_back(acts[i].index);
		}
	}
	return res;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//1.�������������
	/*����������3 12 7 4 2 8 11
	a:Haffman Code is:0011
	b:Haffman Code is:10
	c:Haffman Code is:110
	d:Haffman Code is:000
	e:Haffman Code is:0010
	f:Haffman Code is:111
	g:Haffman Code is:01*/
	
	cout << "�������ж��ٸ��������ַ�" << endl;
	int all = 0;
	cin >> all;
	if(all == 0){
		cout << "������ĸ�������" << endl;
		return -1;
	}
	buildHaffman(all);
	printCode(all);
	for(int i = 0; i < all; i ++){
		cout << haffman[i].ch << ":Haffman Code is:";
		for(int j = code[i].start + 1; j < all; j ++)
			cout << code[i].code[j];
		cout << endl;
	}
	

	//2.̰�ķ���0/1����
	/*int n,c;//n����Ʒ������Ϊc
	cout << "��������Ʒ������������" << endl;
	cin >> n >> c;
	cout << "������������Ʒ������" << endl;
	for(int i = 0;i < n; i ++)
		cin >> wu[i].w;
	cout << "������������Ʒ�ļ�ֵ" << endl;
	for(int i = 0; i < n; i ++)
		cin >> wu[i].v;
	cout << "������̰�ĵĴ�:" << func1(n,c) << endl;
	cout << "����ֵ̰�ĵĴ�:" << func2(n,c) << endl;
	cout << "����λ��ֵ̰�ĵĴ�:" << func3(n,c) << endl;
	cout << "���1000�ε�����:" << random(n,c) << endl;
	*/

	//3.����Ų�������
	/*1 1 4
	2 3 5
	3 0 6
	4 5 7
	5 3 7
	6 5 9
	7 6 10
	8 8 11
	9 8 12
	10 2 13
	11 12 14

	1 4 8 11*/
	/*vector<Act> acts;//��ѡ���
	cout << "�����������ѡ��� ���� ��ʼʱ�� ����ʱ��" << endl;
	copy(istream_iterator<Act>(cin),istream_iterator<Act>(),back_inserter(acts));
	cout<<endl;
	vector<int> res_act;//�ó��ķ����еĻ��ż�
	res_act = GreedySelector(acts);
	//������
	cout << "�����˳��Ϊ:" << endl;
	copy(res_act.begin(),res_act.end(),ostream_iterator<int>(cout,"  "));
	cout<<endl;*/

	system ("pause");
	return 0;
}

