// ���㷨����.cpp : �������̨Ӧ�ó������ڵ㡣
//1.���ݷ� N�ʺ����� �ݹ���ǵݹ�

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>

#define N 4

int q[N + 1];	//�洢�ʺ���ڴ� q[i] ��ʾ�ûʺ�洢�ڵ�i��
int answer = 0; //������

int check(int j){											//�жϵ�j���ʺ��λ���Ƿ�Ϸ�
	int i;
	for(i = 1;i < j; i ++){
		if( q[i] == q[j] || abs(i - j) == abs(q[i] - q[j])) //ͬһ�� ��Խ��ߣ����������ľ���ֵ��ͬ��
			return 0;
	}
		return 1;
}
//�ǵݹ� ���ݷ�
void queen(){								//��� N�ʺ� ����
	int i;
	for(i = 1;i <= N;i ++)
		q[i] = 0;							//��ʼ��ÿһ���ʺ��λ��Ϊ0

	answer = 0;							//������
	int j = 1;								//��ʾ���ڰڷŵ�j���ʺ�

	while(j >= 1){
		q[j] = q[j] + 1;					//��ʼ�ڷ� ���õ�j���ʺ����һ�аڷ�

		while(q[j] <= N && !check(j)){		//�жϵ�J���ʺ��λ���Ƿ�Ϸ�
			q[j] = q[j] + 1;				//���Ϸ�������һ��λ�ðڷ�
		}

		if(q[j] <= N){						//��ʾ��j���ʺ��λ�úϷ�
			if(j == N){						//�ҵ���N�ʺ��һ���
				answer ++;
				printf("����%d: ",answer);
				for(i = 1; i <= N; i ++)
					printf("%d ",q[i]);
				printf("\n");
			}else{							//�����ڷ���һ���ʺ�
				j ++;
			}
		}
		else{				//��ʾ��j���ʺ��Ҳ����Ϸ�λ�� ������һ��λ��
			q[j] = 0;		//��ԭ��j���ʺ��λ��
			j --;			//����
		}
	}
}
//�ݹ鷨
void queen1(int j){
	int i;
	for(i = 1; i <= N; i ++){
		q[j] = i;

		if(check(j)){		//���ڷŵĻʺ�λ�úϷ�ʱ
			if(j == N){	//�ҵ�һ���
				answer ++;
				printf("����%d: ",answer);
				for(i = 1; i <= N; i ++)
					printf("%d ",q[i]);
				printf("\n");
			}else{
				queen1(j ++);//�ݹ�ڷ���һ���ʺ��λ��
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	queen();
	printf ("\n");
	//queen1(1);
	system("pause");
	return 0;
}