// 实验2 复杂性的后验分析.cpp : 定义控制台应用程序的入口点。
// 选择排序 合并排序 快速排序 冒泡排序
// 计时方法 s级 ms级（clock）ms级以下 QueryPerformanceFuency 

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <stack>

using namespace std;

// 交换两个整数的函数
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 快速排序算法(递归）
void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;
        
        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        
        swap(&arr[i + 1], &arr[right]);
        int pivotIndex = i + 1;
        
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }
}
//快速排序 (非递归）
void quickSort1(int arr[], int low, int high) {
    stack<int> st; // 使用栈模拟递归调用

    st.push(low);
    st.push(high);

    while (!st.empty()) {
        // 出栈得到右边界和左边界
        int h = st.top();
        st.pop();
        int l = st.top();
        st.pop();

        // 分区操作，将待排序数组划分为两部分
        int pivot = arr[h]; // 选择最右边的元素作为基准
        int i = l - 1; // i表示小于等于基准的区间边界
        for (int j = l; j <= h - 1; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[h]); // 将基准放到正确的位置

        // 左分区入栈
        if (i - 1 > l) {
            st.push(l);
            st.push(i - 1);
        }

        // 右分区入栈
        if (i + 2 < h) {
            st.push(i + 2);
            st.push(h);
        }
    }
}

// 选择排序算法
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(&arr[i], &arr[minIndex]);
    }
}

// 合并排序算法
/*void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L[99], R[99];
    
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}*/
//归并排序非递归法
void mergeSort(int* a, int left, int right, int n){
	int* tmp = (int*)malloc(sizeof(int) * n);
	int gap = 1;
	while (gap < n){
		for (int i = 0; i <= right; i = i + 2 * gap){
			int begin1 = i, end1 = i + gap - 1, mid = i + gap - 1;
			int begin2 = mid + 1, end2 = i + 2 * gap - 1;
			int j = i;
			if (begin2 > right) break;
			if (end2 > right) end2 = right;
			while (begin1 <= end1 && begin2 <= end2){
				if (a[begin1] < a[begin2]) tmp[j++] = a[begin1++];
				else tmp[j++] = a[begin2++];
			}
			while (begin1 <= end1){
				tmp[j++] = a[begin1++];
			}
			while (begin2 <= end2){
				tmp[j++] = a[begin2++];
			}
			for (int j = i; j <= end2; j++){
				a[j] = tmp[j];
			}
		}
		gap = 2 * gap;
	}
}

// 冒泡排序算法
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
	//毫秒级分析时间
    int n = 100; // 设置数组大小
    int num_measurements = 10; // 设置每种算法测量的次数
    srand(time(NULL));

    LARGE_INTEGER frequency;
    LARGE_INTEGER start_time;
    LARGE_INTEGER end_time;
    double elapsed_time;

    int *arr = (int *)malloc(n * sizeof(int)); // 分配堆内存

    QueryPerformanceFrequency(&frequency);
    double total_quickSort_time = 0.0;

    for (int measurement = 0; measurement < num_measurements; measurement++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
        }

        QueryPerformanceCounter(&start_time);
        quickSort(arr, 0, n - 1);
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_quickSort_time += elapsed_time;
    }

    double average_quickSort_time = total_quickSort_time / num_measurements;
    printf("快速排序(递归）平均执行时间: %f 毫秒\n", average_quickSort_time);

	// 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    double total_quickSort_time1 = 0.0;
    for (int measurement = 0; measurement < num_measurements; measurement++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
        }

        QueryPerformanceCounter(&start_time);
        quickSort1(arr, 0, n-1);
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_quickSort_time1 += elapsed_time;
    }
    double average_quickSort_time1 = total_quickSort_time1 / num_measurements;
    printf("快速排序（非递归）平均执行时间: %f 毫秒\n", average_quickSort_time1);

    // 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    double total_selectionSort_time = 0.0;
    for (int measurement = 0; measurement < num_measurements; measurement++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
        }

        QueryPerformanceCounter(&start_time);
        selectionSort(arr, n);
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_selectionSort_time += elapsed_time;
    }
    double average_selectionSort_time = total_selectionSort_time / num_measurements;
    printf("选择排序平均执行时间: %f 毫秒\n", average_selectionSort_time);

    // 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    double total_mergeSort_time = 0.0;
    for (int measurement = 0; measurement < num_measurements; measurement++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
        }

        QueryPerformanceCounter(&start_time);
        mergeSort(arr, 0, n - 1, n );
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_mergeSort_time += elapsed_time;
    }
    double average_mergeSort_time = total_mergeSort_time / num_measurements;
    printf("合并排序（非递归）平均执行时间: %f 毫秒\n", average_mergeSort_time);

    // 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    double total_bubbleSort_time = 0.0;
    for (int measurement = 0; measurement < num_measurements; measurement++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
        }

        QueryPerformanceCounter(&start_time);
        bubbleSort(arr, n);
        QueryPerformanceCounter(&end_time);

        elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart * 1000.0;
        total_bubbleSort_time += elapsed_time;
    }
    double average_bubbleSort_time = total_bubbleSort_time / num_measurements;
    printf("冒泡排序平均执行时间: %f 毫秒\n", average_bubbleSort_time);

    // 释放堆内存
    free(arr);
	
    /*用于测试排序算法是否正确
    int n = 20;
    int arr[999];
    //srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // 生成0到999之间的随机整数
    }

	quickSort(arr, 0, n - 1);
	for(int i = 0;i < n; i ++)
		printf("%d ",arr[i]);
	printf("\n");

	// 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
	quickSort1(arr, 0, n-1 );
	for(int i = 0;i < n; i ++)
		printf("%d ",arr[i]);
	printf("\n");

	// 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
	selectionSort(arr, n);
	for(int i = 0;i < n; i ++)
		printf("%d ",arr[i]);
	printf("\n");

	// 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
	mergeSort(arr, 0, n-1, n );
	for(int i = 0;i < n; i ++)
		printf("%d ",arr[i]);
	printf("\n");

	// 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
	bubbleSort(arr, n);
	for(int i = 0;i < n; i ++)
		printf("%d ",arr[i]);
	printf("\n");

    /*clock_t start, end;
    double cpu_time_used;

    // 测量快速排序的执行时间
    start = clock();
    quickSort(arr, 0, n - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("快速排序执行时间: %f\n", cpu_time_used);

    // 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    // 测量选择排序的执行时间
    start = clock();
    selectionSort(arr, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("选择排序执行时间: %f\n", cpu_time_used);

    // 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    // 测量合并排序的执行时间
    start = clock();
    mergeSort(arr, 0, n - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("合并排序执行时间: %f\n", cpu_time_used);

    // 重新生成随机样本
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    // 测量冒泡排序的执行时间
    start = clock();
    bubbleSort(arr, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("冒泡排序执行时间: %f\n", cpu_time_used);*/

	getchar();

    return 0;
}