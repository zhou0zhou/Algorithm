// 实验6 贪心.cpp : 定义控制台应用程序的入口点。
//合并字符串（哈夫曼编码）prime 
//https://blog.csdn.net/xiangjunyes/article/details/106026830?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169949879516800185847742%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=169949879516800185847742&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-8-106026830-null-null.142^v96^pc_search_result_base6&utm_term=%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95%20%E5%90%88%E5%B9%B6%E5%AD%97%E7%AC%A6%E4%B8%B2%20%E5%93%88%E5%A4%AB%E6%9B%BC%E7%BC%96%E7%A0%81&spm=1018.2226.3001.4187
//前缀码：对每一个字符规定一个0，1串作为其代码 并要求任意字符的代码都不是其他字符代码的前缀 前缀码能够保证有且只有一种唯一的译码结果
//所以对于给定的字符集，哈夫曼编码问题就转换为：寻找使平均码长达到最小的前缀编码的问题
//0/1背包 背包
//https://blog.csdn.net/qq_67764134/article/details/129903263?ops_request_misc=&request_id=&biz_id=102&utm_term=%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95%E6%B1%8201%E8%83%8C%E5%8C%85&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-129903263.142^v96^pc_search_result_base8&spm=1018.2226.3001.4187
//https://blog.csdn.net/qq_43561370/article/details/108210766?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_utm_term~default-0-108210766-blog-129903263.235^v38^pc_relevant_default_base3&spm=1001.2101.3001.4242.1&utm_relevant_index=3
//活动安排
//https://blog.csdn.net/m0_71272694/article/details/128058744?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169986601716777224428107%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169986601716777224428107&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_click~default-2-128058744-null-null.142^v96^pc_search_result_base8&utm_term=%E6%B4%BB%E5%8A%A8%E5%AE%89%E6%8E%92&spm=1018.2226.3001.4187

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <Windows.h>
using namespace std;

#define MAXCODELEN 100		//最大字符编码数组长度
#define MAXHAFF	100			//最大哈夫曼结点结构体数组个数
#define MAXCODE 100			//最大哈夫曼编码结构体数组的个数
#define MAXWEIGHT 10000     //最大平均码长

//1.哈夫曼编码
typedef struct Haffman{
	int weight;
	char ch;
	int parent;
	int leftchild;
	int rightchild;
}HaffmaNode;

typedef struct Code{
	int code[MAXCODELEN];
	int start;				//从哪个位置开始
}HaffmaCode;

HaffmaNode haffman[MAXHAFF];
HaffmaCode code[MAXCODE];

void buildHaffman(int all){ //构造哈夫曼树的过程
	//初始化前首先将每个节点的权重置0,父节点 左右孩子都-1
	for(int i = 0; i < all * 2 - 1; i ++){
		haffman[i].weight = 0;
		haffman[i].parent = -1;
		haffman[i].leftchild = -1;
		haffman[i].rightchild = -1;
	}
	cout << "请输入需要哈夫曼编码的字符和权重大小" << endl;
	for(int i = 0; i < all;i ++){
		cout <<"请分别输入第" << i <<"个哈夫曼字符和权重" << endl;
		cin >> haffman[i].ch;
		cin >> haffman[i].weight;
	}

	//每次需要找出最小的权重的结点，生成新的结点 需要all - 1次合并
	int x1,x2,w1,w2;
	for(int i = 0; i < all - 1;i ++){
		x1 = x2 = -1;
		w1 = w2 = MAXWEIGHT;

		for(int j  = 0;j < all + i; ++ j){		//每次在all + i次里遍历 得到最小权重的结点
			if(haffman[j].parent == -1 && haffman[j].weight < w1){//每次最小的更新的话 要把上次最小的给次小的
				w2 = w1;
				x2 = x1;
				x1 = j;
				w1 = haffman[j].weight;
			}else if(haffman[j].parent == -1 && haffman[j].weight < w2){ //更新次小的 只需更新w2就行
				x2 = j;
				w2 = haffman[j].weight;
			}
		}
		//每次找到最小的两个结点要合并
		haffman[all + i].leftchild = x1;
		haffman[all + i].rightchild = x2;
		haffman[all + i].weight = w1 + w2;
		haffman[x1].parent = all + i;
		haffman[x2].parent = all + i;
		cout << "x1是 " << x1 << " x1的父亲是" << haffman[x1].parent << endl;
		cout << "x2是 " << x2 << " x2的父亲是" << haffman[x2].parent << endl;
		cout << "新结点是" << all + i << " 新结点的权重是" << haffman[all + i].weight << endl;
	}
}

void printCode(int all){
	HaffmaCode hCode; //保存当前叶子节点的字符编码
	int curParent;	  //当前父节点
	int c;			  //下标和叶子节点的编号
	for(int i = 0;i < all; i ++){
		hCode.start = all - 1;
		c = i;
		curParent = haffman[i].parent;

		while(curParent != -1){		//父节点为-1即为根节点
			//对父节点的左右孩子判断 左0右1 不是的话也取1
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
		//存储当前的叶子节点信息到编码结构体里
		for(int j  = hCode.start + 1;j < all; j ++)
			code[i].code[j] = hCode.code[j];
		code[i].start = hCode.start;
	}
}

//2.0/1背包
struct node{
	int v;//价值
	int w;//重量
}wu[100];

bool cmp1(node a,node b){//比较重量
	if(a.w == b.w)
		return a.v > b.v;
	return a.w > b.w;
}

bool cmp2(node a,node b){//比较价值
	if(a.v == b.v)
		return a.w < b.w;
	return a.v > b.v;
}

bool cmp3(node a,node b){//单位价值
	if((a.v/a.w) == (b.v/b.w))
		return a.w < b.w;
	return (a.v/a.w) > (b.v/b.w);
}

int func1(int n,int c){ //按最大重量贪心求值
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

int func2(int n,int c){ //按最大价值贪心求值
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

int func3(int n,int c){ //按最大单位价值贪心求值
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

//3.活动安排
struct Act{
	int beg;//活动的开始时间
	int end;//活动的结束时间
	int index;//活动的编号
	friend ostream & operator<<(ostream &o,const Act &A);   
	friend istream & operator>>(istream &o, Act &A);
};
//运算符重载 直接用IO流输入可选活动集合
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
	//首先把活动按照活动的结束时间进行排序
	sort(acts.begin(),acts.end(),cmp);
	//在排序后的活动集合中选择可行的活动
	vector<int> res;
	res.push_back(acts[0].index);//首先选中第一个活动
	int now = 0;//当前选中的活动下标
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
	//1.哈夫曼编码测试
	/*测试用例：3 12 7 4 2 8 11
	a:Haffman Code is:0011
	b:Haffman Code is:10
	c:Haffman Code is:110
	d:Haffman Code is:000
	e:Haffman Code is:0010
	f:Haffman Code is:111
	g:Haffman Code is:01*/
	
	cout << "请输入有多少个哈夫曼字符" << endl;
	int all = 0;
	cin >> all;
	if(all == 0){
		cout << "您输入的个数有误" << endl;
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
	

	//2.贪心法求0/1背包
	/*int n,c;//n个物品，容量为c
	cout << "请输入物品总数和总容量" << endl;
	cin >> n >> c;
	cout << "请依次输入物品的重量" << endl;
	for(int i = 0;i < n; i ++)
		cin >> wu[i].w;
	cout << "请依次输入物品的价值" << endl;
	for(int i = 0; i < n; i ++)
		cin >> wu[i].v;
	cout << "按重量贪心的答案:" << func1(n,c) << endl;
	cout << "按价值贪心的答案:" << func2(n,c) << endl;
	cout << "按单位价值贪心的答案:" << func3(n,c) << endl;
	cout << "随机1000次的最大答案:" << random(n,c) << endl;
	*/

	//3.活动安排测试用例
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
	/*vector<Act> acts;//可选活动集
	cout << "请依次输入可选活动集 活动编号 开始时间 结束时间" << endl;
	copy(istream_iterator<Act>(cin),istream_iterator<Act>(),back_inserter(acts));
	cout<<endl;
	vector<int> res_act;//得出的方案中的活动编号集
	res_act = GreedySelector(acts);
	//输出结果
	cout << "活动安排顺序为:" << endl;
	copy(res_act.begin(),res_act.end(),ostream_iterator<int>(cout,"  "));
	cout<<endl;*/

	system ("pause");
	return 0;
}

