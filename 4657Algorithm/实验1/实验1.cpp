// ʵ��1.cpp : ����㷨�������������Լ��
//1.������
//2.ŷ����ü���
//3.ŷ����ó���
//4.������/�ӷֽⷨ

#include "stdafx.h"
#include <math.h>
#include <iostream>
using namespace std;

//��1������Ѱ�� ������
int _solu1(int m,int n){
	int res = 1;
	for(int i = 2;i <= min(m,n);i ++){
		if(m % i == 0 && n % i  == 0 && i > res)
			res = i;
	}
	return res;
}
//��2��ŷ����ü����� m > n ,gcd(m,n) = gcd(m-n,n) 
int _solu2(int m,int n){
	if (m == n)
		return m;
	if (m < n){
		int temp = n; n = m;m = temp;
	}
	return _solu2(m - n,n);
}
//��3��շת�����gcd(m,n) = gcd(n,m%n)
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

