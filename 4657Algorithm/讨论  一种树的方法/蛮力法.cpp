// 蛮力法.cpp : 定义控制台应用程序的入口点。
//1.一种树的生成方法：生成组合（子集）与排列
//2.课后习题5.5 删除重复元素 
//3.模拟KMP&BF算法

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

/*int n = 5; // 字符集的大小
int r = 3; // 组合或排列的长度
vector<int> x(n + 1); // 存储当前组合或排列

void output() {
    for (int i = 1; i <= r; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

//生成子集树
//t是树的层数 n是元素的个数 x是数组 存储子集的表达方法
void subsetTree(int t, int k) {
	//t 表示当前生成组合的位置，k 表示上一个选择的字符的下标。
    if (t > r) {
        output();
        return;
    }
    
    for (int i = k + 1; i <= n; i++) {
        x[t] = i;
        subsetTree(t + 1, i);
    }
}

void generateCombinations() {
    subsetTree(1, 0);
}

//生成全排列
bool isLegal(int t) { //判断是否是叶子节点
    for (int i = 1; i < t; i++) {
        if (x[i] == x[t]) {
            return false;
        }
    }
    return true;
}

void permutationTree(int t) {
    if (t > r) {
        output();
        return;
    }

    for (int i = 1; i <= n; i++) {
        x[t] = i;
        if (isLegal(t)) {
            permutationTree(t + 1);
        }
    }
}

void generatePermutations() {
    permutationTree(1);
}

//遍历子集树需要O(2~n)计算时间
/*void backtrack(int t){
	if(t > n) output(x);
	else 
		for(int i = 0; i <= 1; i ++){
			x[t] = i;
			backtrack(t+1);
		}
}
//遍历排列树需要O(n!)计算时间
void backtrack(int t){
	if(t > n) output(x);
	else
		for(int i = t;i <= n; i ++){
			swap(x[t],x[i]);
			if(legal(t)) backtrack(t+1);
			swap(x[t],x[i]);
		}
}
*/
/*
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "生成的所有子集:" << endl;
	generateCombinations();
	cout << endl;
	cout << "生成的全排列:" << endl;
	generatePermutations();
	system("pause");
	return 0;
}

*/
//课后习题5.5
//删除数组中的重复元素设计算法,在数组r[n]中删除重复的元素,要求移动元素的次数较少并使剩余元素间的相对次序保持不变

#define N 1000
#define FLAG 0x80000000 /*特殊标记,用最小的负数表示*/

void main( ){
	int r[N], length, i, j;
	printf("请输入数组长度:");
	scanf("%d", &length);
	printf("请依次输入数组元素：\n");
	for(i = 0; i < length; i++)
		scanf("%d", &r[i]);
	for(i = 0; i < length - 1; i++){
		if(r[i] != FLAG){
			for(j = i + 1; j < length; j++)
				if(r[j] == r[i]) r[j] = FLAG; /*遇到重复值,则先用特殊标记覆盖它*/
		}
	}
	for(i = 0; r[i] != FLAG; i++); /*找到第一个特殊标记*/
	for(j = i + 1; j < length;){ /*删除数列中的特殊标记*/
		if(r[j] != FLAG) r[i++] = r[j++];
		else j++;
	}
	length = i; /*修改删除重复值后的数列的长度*/
	for(i = 0; i < length; i++)
		printf("%-4d", r[i]);

	system("pause");
}