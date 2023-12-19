// 实验5 减治法.cpp : 定义控制台应用程序的入口点。
//堆排序 并用它解决TOPK问题
//选择问题——求无序序列的第K小元素   https://blog.csdn.net/m0_63064861/article/details/130470253
//假币问题——已知一个轻的假币的情况  zst_2001 
//习题7.2
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <cstdlib>
using namespace std;	

//堆排序（大根堆）
//数组下标从0开始的话，r[i]的左孩子下标为2i+1,右孩子为2i+2
//筛选法 当前筛选节点的编号为k,堆中最后一个结点的编号是n，且结点k的左右子树均是堆
void SiftHeap(int r[],int k,int n){
	int i,j,temp;
	i = k;
	j = 2 * i + 1;    //j为i的左子树
	while(j < n){   //筛选还没有到叶子节点
		if(j < n - 1 && r[j] < r[j+1])//比较左右孩子哪个大
			j++;
		if(r[i] > r[j])//此时父节点比左右孩子较大者还大
			break;
		else{          //交换父节点与较大孩子 然后在数组中的下标也要换
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
		SiftHeap(r,i,n);      //初建堆，最后一个分支的下标是(n-1)/2

	for(i = 1;i <= n - 1;i ++){      //重建堆 反复交换结点与第一个根节点 只需要调节到根节点
		temp = r[0];
		r[0] = r[n-i];
		r[n-i] = temp;
		SiftHeap(r,0,n-i);
	}
}

//选择问题——求无序序列的第K小元素
int a[100];
int select(int left,int right,int k){
	//找到了第k小元素
	if (left >= right)
		return a[left];
	int i = left;//从左到右的指针
	int j = right;//从右到左的指针
	int pivot = a[left];//把最左边的元素作为分界数据
 
	while (true) {
		//寻找左边大于pivot的数
		do {
			i++;
		} while (a[i]<pivot);
		//寻找右边小于pivot的数
		do {
			j--;
		} while (a[j] > pivot);
 
		if (i >= j)
			break;//没有发现交换对象
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

//假币问题
int getCounterfeitCoin(int coins[],int first,int last){
	int firstSum = 0,lastSum = 0;
	int i;
	if(first == last - 1){//此时只剩两枚硬币
		if(coins[first] < coins[last])
			return first;
		return last;
	}
	if((last - first + 1) % 2 == 0){//偶数枚硬币 比较前半和后半的重量
		for(i = first; i < (last - first) / 2 + 1; i ++)
			firstSum += coins[i];
		for(i = first + (last - first) / 2 + 1;i < last + 1; i ++)
			lastSum += coins[i];
		if(firstSum < lastSum)//分情况递归
			return getCounterfeitCoin(coins,first,first + (last - first) / 2);
		else 
			return getCounterfeitCoin(coins,first + (last - first) / 2 + 1, last);
	}else{//奇数枚硬币
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

//习题7.2
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
	cout << "堆排序结果如下"<< endl;
	HeapSort(arr,10);
	for(int i = 0; i < 10; i ++)
		cout << arr[i] << " ";
	cout << endl;

	//选择第K小元素测试数据
	int n = 10;
	for (int i = 0; i < n; i++)
        a[i] = rand() % 1000; 
	printf("随机生成的数组是:\n");
	for(int i = 0; i < 10; i ++)
		cout << arr[i] << " ";
	cout << endl;
	int k = 3;
	printf("第%d小的元素是%d\n",k,select(0,n - 1,k));

	//假币测试数据
	int coins[] = {1,0,1,1,1,1,1,1};
	int index = getCounterfeitCoin(coins,0,7);
	printf("第%d枚是假币\n",index + 1);

	system("pause");
	return 0;
}

