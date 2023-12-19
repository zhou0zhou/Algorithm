// ʵ��5 ���η�.cpp : �������̨Ӧ�ó������ڵ㡣
//������ ���������TOPK����
//ѡ�����⡪�����������еĵ�KСԪ��   https://blog.csdn.net/m0_63064861/article/details/130470253
//�ٱ����⡪����֪һ����ļٱҵ����  zst_2001 
//ϰ��7.2
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <cstdlib>
using namespace std;	

//�����򣨴���ѣ�
//�����±��0��ʼ�Ļ���r[i]�������±�Ϊ2i+1,�Һ���Ϊ2i+2
//ɸѡ�� ��ǰɸѡ�ڵ�ı��Ϊk,�������һ�����ı����n���ҽ��k�������������Ƕ�
void SiftHeap(int r[],int k,int n){
	int i,j,temp;
	i = k;
	j = 2 * i + 1;    //jΪi��������
	while(j < n){   //ɸѡ��û�е�Ҷ�ӽڵ�
		if(j < n - 1 && r[j] < r[j+1])//�Ƚ����Һ����ĸ���
			j++;
		if(r[i] > r[j])//��ʱ���ڵ�����Һ��ӽϴ��߻���
			break;
		else{          //�������ڵ���ϴ��� Ȼ���������е��±�ҲҪ��
			temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			i = j;
			j = 2 * i + 1;
		}
	}
}

void HeapSort(int r[],int n){
	int i,temp;
	for(i = (n - 1) / 2;i >= 0;i --)
		SiftHeap(r,i,n);      //�����ѣ����һ����֧���±���(n-1)/2

	for(i = 1;i <= n - 1;i ++){      //�ؽ��� ��������������һ�����ڵ� ֻ��Ҫ���ڵ����ڵ�
		temp = r[0];
		r[0] = r[n-i];
		r[n-i] = temp;
		SiftHeap(r,0,n-i);
	}
}

//ѡ�����⡪�����������еĵ�KСԪ��
int a[100];
int select(int left,int right,int k){
	//�ҵ��˵�kСԪ��
	if (left >= right)
		return a[left];
	int i = left;//�����ҵ�ָ��
	int j = right;//���ҵ����ָ��
	int pivot = a[left];//������ߵ�Ԫ����Ϊ�ֽ�����
 
	while (true) {
		//Ѱ����ߴ���pivot����
		do {
			i++;
		} while (a[i]<pivot);
		//Ѱ���ұ�С��pivot����
		do {
			j--;
		} while (a[j] > pivot);
 
		if (i >= j)
			break;//û�з��ֽ�������
		swap(a[i], a[j]);
	}
	if (j - left + 1 == k)
		return pivot;
	a[left] = a[j];
	a[j] = pivot;
	if (j - left + 1 < k)
		return select(j + 1, right, k - (j - left + 1));
	else
		return select(left, j - 1, k);
}

//�ٱ�����
int getCounterfeitCoin(int coins[],int first,int last){
	int firstSum = 0,lastSum = 0;
	int i;
	if(first == last - 1){//��ʱֻʣ��öӲ��
		if(coins[first] < coins[last])
			return first;
		return last;
	}
	if((last - first + 1) % 2 == 0){//ż��öӲ�� �Ƚ�ǰ��ͺ�������
		for(i = first; i < (last - first) / 2 + 1; i ++)
			firstSum += coins[i];
		for(i = first + (last - first) / 2 + 1;i < last + 1; i ++)
			lastSum += coins[i];
		if(firstSum < lastSum)//������ݹ�
			return getCounterfeitCoin(coins,first,first + (last - first) / 2);
		else 
			return getCounterfeitCoin(coins,first + (last - first) / 2 + 1, last);
	}else{//����öӲ��
		for(i = first; i < (last - first) / 2 ; i ++)
			firstSum += coins[i];
		for(i = first + (last - first) / 2 + 1;i < last + 1; i ++)
			lastSum += coins[i];
		if(firstSum < lastSum)
			return getCounterfeitCoin(coins,first,first + (last - first) / 2 - 1);
		else if(firstSum > lastSum)
			return getCounterfeitCoin(coins,first + (last - first) / 2 + 1, last);
		else 
			return first + (last - first) / 2;
	}
}

//ϰ��7.2
void RangeSearch(int min,int max,int a[],int low,int high){
	sort(a + low,a + high);
	int mid;
	mid = (low + high)/2;
	if(a[mid] < min)
		RangeSearch(min,max,a,mid,high);
	else if(a[mid] > max)
		RangeSearch(min,max,a,low,mid);
	else{
		for(int i = mid; a[i] >= min && i >= low;i --)
			cout << a[i] << " ";
		cout << endl;
		for(int j = mid + 1;a[j] <= max && j <= high; j ++)
			cout << a[j] << " ";
		cout << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[10] = {1,3,5,56,98,19,20,40,60,7};
	RangeSearch(1,20,a,2,9);
	int arr[10];
	for (int i = 0; i < 10; i++)
        arr[i] = rand() % 1000; 
	cout << "������������"<< endl;
	HeapSort(arr,10);
	for(int i = 0; i < 10; i ++)
		cout << arr[i] << " ";
	cout << endl;

	//ѡ���KСԪ�ز�������
	int n = 10;
	for (int i = 0; i < n; i++)
        a[i] = rand() % 1000; 
	printf("������ɵ�������:\n");
	for(int i = 0; i < 10; i ++)
		cout << arr[i] << " ";
	cout << endl;
	int k = 3;
	printf("��%dС��Ԫ����%d\n",k,select(0,n - 1,k));

	//�ٱҲ�������
	int coins[] = {1,0,1,1,1,1,1,1};
	int index = getCounterfeitCoin(coins,0,7);
	printf("��%dö�Ǽٱ�\n",index + 1);

	system("pause");
	return 0;
}

