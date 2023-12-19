// ������.cpp : �������̨Ӧ�ó������ڵ㡣
//1.һ���������ɷ�����������ϣ��Ӽ���������
//2.�κ�ϰ��5.5 ɾ���ظ�Ԫ�� 
//3.ģ��KMP&BF�㷨

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

/*int n = 5; // �ַ����Ĵ�С
int r = 3; // ��ϻ����еĳ���
vector<int> x(n + 1); // �洢��ǰ��ϻ�����

void output() {
    for (int i = 1; i <= r; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

//�����Ӽ���
//t�����Ĳ��� n��Ԫ�صĸ��� x������ �洢�Ӽ��ı�﷽��
void subsetTree(int t, int k) {
	//t ��ʾ��ǰ������ϵ�λ�ã�k ��ʾ��һ��ѡ����ַ����±ꡣ
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

//����ȫ����
bool isLegal(int t) { //�ж��Ƿ���Ҷ�ӽڵ�
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

//�����Ӽ�����ҪO(2~n)����ʱ��
/*void backtrack(int t){
	if(t > n) output(x);
	else 
		for(int i = 0; i <= 1; i ++){
			x[t] = i;
			backtrack(t+1);
		}
}
//������������ҪO(n!)����ʱ��
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
	cout << "���ɵ������Ӽ�:" << endl;
	generateCombinations();
	cout << endl;
	cout << "���ɵ�ȫ����:" << endl;
	generatePermutations();
	system("pause");
	return 0;
}

*/
//�κ�ϰ��5.5
//ɾ�������е��ظ�Ԫ������㷨,������r[n]��ɾ���ظ���Ԫ��,Ҫ���ƶ�Ԫ�صĴ������ٲ�ʹʣ��Ԫ�ؼ����Դ��򱣳ֲ���

#define N 1000
#define FLAG 0x80000000 /*������,����С�ĸ�����ʾ*/

void main( ){
	int r[N], length, i, j;
	printf("���������鳤��:");
	scanf("%d", &length);
	printf("��������������Ԫ�أ�\n");
	for(i = 0; i < length; i++)
		scanf("%d", &r[i]);
	for(i = 0; i < length - 1; i++){
		if(r[i] != FLAG){
			for(j = i + 1; j < length; j++)
				if(r[j] == r[i]) r[j] = FLAG; /*�����ظ�ֵ,�����������Ǹ�����*/
		}
	}
	for(i = 0; r[i] != FLAG; i++); /*�ҵ���һ��������*/
	for(j = i + 1; j < length;){ /*ɾ�������е�������*/
		if(r[j] != FLAG) r[i++] = r[j++];
		else j++;
	}
	length = i; /*�޸�ɾ���ظ�ֵ������еĳ���*/
	for(i = 0; i < length; i++)
		printf("%-4d", r[i]);

	system("pause");
}