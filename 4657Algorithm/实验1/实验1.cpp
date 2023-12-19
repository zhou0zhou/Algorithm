// 实验1.cpp : 设计算法求两个数的最大公约数
//1.蛮力法
//2.欧几里得减法
//3.欧几里得除法
//4.质因数/子分解法

#include "stdafx.h"
#include <math.h>
#include <iostream>
using namespace std;

//法1：遍历寻找 蛮力法
int _solu1(int m,int n){
	int res = 1;
	for(int i = 2;i <= min(m,n);i ++){
		if(m % i == 0 && n % i  == 0 && i > res)
			res = i;
	}
	return res;
}
//法2：欧几里得减法： m > n ,gcd(m,n) = gcd(m-n,n) 
int _solu2(int m,int n){
	if (m == n)
		return m;
	if (m < n){
		int temp = n; n = m;m = temp;
	}
	return _solu2(m - n,n);
}
//法3：辗转相除：gcd(m,n) = gcd(n,m%n)
int _solu3(int m,int n){
	if (n == 0)  return m;
	else return _solu3( n ,m % n);
}
int _tmain(int argc, _TCHAR* argv[])
{
	cout << _solu1(3,2) << endl;
	cout << _solu2(15,5) << endl;
	cout << _solu3(27,18) <<endl;
	getchar();
	return 0;
}

