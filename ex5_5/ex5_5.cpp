#include "stdafx.h"
#include <stdlib.h>
#define MAXNUM 30

//合并函数,将两段有序表排序为一段有序表
//数组pArray中表A先存放，接着是表B，且B紧挨着A存放
//aStart指表A第一个元素的数组下标
//aCount指表A的元素个数，bCount指表B的元素个数
void merge(int *pArray, int aStart, int aCount, int bCount)
{
	int i = aStart;
	int j = aStart + aCount;	//将表B的第一个元素的数组下标设为j
	int k, temp;
	while (j < aStart + aCount + bCount && i < j)
	{
		//若B的首位元素大于等于A的末位元素，则表有序，退出循环
		//此处的A指的是数组下标在 aStart~j-1 范围内的元素
		//B指的是数组下标>=j 的元素
		if (pArray[j] >= pArray[j - 1])
			break;

		//否则，将B的首位元素移动到正确位置，
		else if (pArray[j] < pArray[i])
		{
			temp = pArray[j];
			for (k = j; k > i; k--)
				pArray[k] = pArray[k - 1];
			pArray[k] = temp;
			j++;
		}
		i++;
	}
}

//归并函数，先以数组中每个元素为子表，调用合并函数两两合并，
//然后继续把新表两两合并，直到最后合并成一个大表，完成归并排序
//aStart指表A第一个元素的数组下标
//aCount指表A的元素个数，bCount指表B的元素个数
void unit(int *pArray, int arrayLength)
{
	int j = 1;

	//第一次进行两两合并时，表A和表B的长度必均为1，故设aCount初值为1
	//此后每对新表两两合并时，表A长度必变为原来2倍，表B的长度需要进行一些控制
	for (int aCount = 1; aCount < arrayLength; aCount *= 2)
	{
		//假设需进行n次两两合并，则前n-1次合并时，表B的长度一定与A的长度相等
		int bCount = aCount;

		//第一次对新表两两合并，表A首位即aStart必为0，然后aStart依次后移2*aCount
		for (int aStart = 0; aStart < arrayLength - 1; aStart += 2 * aCount)
		{
			//在最后一次合并时，若bCount仍等于aCount,
			//则可能会越界，若越界，则修改表B长度
			if (aStart + 2 * aCount > arrayLength)
				bCount = arrayLength - aStart - aCount;
			merge(pArray, aStart, aCount, bCount);
		}

		//每完成一次两两合并后将数组元素输出，以检验合并过程是否正确
		printf("\n\n  第%-2d次排序：", j++);
		for (int i = 0; i < arrayLength; i++)
			printf("%-3d  ", pArray[i]);
	}
}

int main()
{
	int numArray[MAXNUM];
	int arrayLength = -1;

	//从键盘读入数值
	printf("Please input numbers(input \"q\" to quit): ");
	while (arrayLength < MAXNUM - 1 && scanf("%d", &numArray[++arrayLength]));

	printf("\n\n    原始数据：");
	for (int i = 0; i < arrayLength; i++)
		printf("%-3d  ", numArray[i]);
	printf("\n\n");

	//调用归并函数完成归并
	unit(numArray, arrayLength);

	printf("\n\n\n\n    最终数据：");
	for (int i = 0; i < arrayLength; i++)
		printf("%-3d  ", numArray[i]);

	printf("\n\n\n");
	system("pause");
    return 0;
}

