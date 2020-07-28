// Sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stopwatch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <time.h>
#include <random>



using namespace std;
#define SIZE 10
int iTemp[SIZE] = { 0 };

//버블-선택-삽입-셸-퀵-병합-힙-도수-기수
template<typename T>
void print(const T& v, const char* message = "")
{
	typename T::const_iterator it;
	std::cout << message;
	std::cout << "( ";
	for (it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << ' ';
	}
	std::cout << " )" << std::endl;
}

void RandomNumber(int* );

void BubleSort(int* ,int);

void SelectSort(int* ,int);

void InsertSort(int*, int);

void ShellSort(int*, int);

void QuickSort(int*, int, int);

int QuickSubSort(int*, int, int);

void MargeSort(int*, int, int);

void HeapSort(int*, int);


int main()
{
	int iRandom[SIZE] = { 0 };
	int iTest[SIZE] = { 2,8,7,6,5,9,4,3,10,1 };
	
	stopwatch sort;
	//RandomNumber(iRandom);

	//BubleSort(iRandom,SIZE);

	//SelectSort(iRandom, SIZE);

	//InsertSort(iRandom, SIZE);
	
	//ShellSort(iRandom, SIZE);

	//QuickSort(iRandom, 0, SIZE - 1);

	//MargeSort(iRandom, 0, SIZE);

	//sort.setStartTime();
	//sort.setEndTime();

	HeapSort(iTest,SIZE);


	for (int i = 0; i < SIZE; i++)
	{
		cout << iTest[i] << " ";
	}


	//cout << endl;

	//cout << "걸린시간 :"<<sort.getElapsesedTime();

    return 0;
}

//Number_Random_shuffle 
void RandomNumber(int* iRandom)
{
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> dis(1, SIZE); // 원하는 범위의 숫자

	int icase;
	for (size_t i = 0; i < SIZE; i++)
	{
		icase = dis(gen);
		iRandom[i] = icase;
	}
}

void BubleSort(int* arr,int size)
{
	for (int i = 1; i < size-1; i++)
	{
		for (int j = 1; j < size ; j++)
		{
			if (arr[j-1] > arr[j])
			{
				swap(arr[j - 1], arr[j]);
				cout << arr[j - 1] <<" <swap >" <<arr[j] << endl;
			}
		}
	}
	for (int k = 0; k < size; k++)
	{
		cout << arr[k] << " ";
	}
}

void SelectSort(int* arr, int size)
{
	for (int i = 0; i < size-1; i++)
	{
		int min = i;
		for (int j = i+1; j < size; j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}

		if (arr[min] != arr[i])
		{
			swap(arr[i], arr[min]);
		}


	}



	for (int i = 0; i < size; i++)
	{
		cout<<arr[i]<<" ";
	}
}

void InsertSort(int *arr, int size)
{
	int temp = 0;

	for (int i = 1 ; i < size; i++)
	{
		temp = i;
		while (arr[temp] < arr[temp-1])
		{
			swap(arr[temp], arr[temp - 1]);
			temp --;
		}
	}

}

void ShellSort(int *arr, int size)
{
	int mid = size / 2;
	int j = 0, i=0;
	while (mid > 0)
	{
		for (int i = mid; i < size; i++)
		{
			int temp = arr[i];
			for (j = i; j >= mid &&arr[j - mid] > temp; j -= mid)
			{
				swap(arr[j], arr[j - mid]);
			}
		}
		mid /= 2;
	}
}

void QuickSort(int *arr, int left, int right)
{
	if (left >= right)
		return;

	int center = QuickSubSort(arr, left, right);
		QuickSort(arr, left, center - 1);
		QuickSort(arr, center + 1, right);

}

int QuickSubSort(int *arr, int left, int right)
{
	int pivot = arr[right] , iIndex = left;
	for (int i = left; i < right; i++)
	{
		if (arr[i] < pivot)
		{
			swap(arr[i], arr[iIndex]);
			iIndex++;
		}
	}
	swap(arr[right], arr[iIndex]);

	return iIndex;
}

void MargeSort(int *arr, int left,int right)
{
	int iMid = (left + right) / 2;

	if (right - left == 1) return;
	else if (right - left == 2)
	{
		if (arr[left] > arr[left+1])
			swap(arr[left], arr[left+1]);
	}
	else
	{
		MargeSort(arr, left, iMid);
		MargeSort(arr, iMid, right);

		int leftIndex = left;
		int rightIndex = iMid;
		int i = leftIndex;

		while (leftIndex < iMid && rightIndex < right)
		{
			if (arr[leftIndex] > arr[rightIndex]) //오른쪽 작을떄
			{
				iTemp[i] = arr[rightIndex];
				rightIndex++;
			}
			else                                  //왼쪽 작을떄
			{
				iTemp[i] = arr[leftIndex];
				leftIndex++;
			}
			i++;
		}

		for ( ; leftIndex < iMid; leftIndex++,i++)
		{
			iTemp[i] = arr[leftIndex];
		}
		for (; rightIndex < right; rightIndex++,i++)
		{
			iTemp[i] = arr[rightIndex];
		}

		for (i = left; i < right; i++)
		{
			arr[i] = iTemp[i];
		}


	}
	


}

void HeapSort(int *arr, int size)
{
	int node = 0, parent = 0;


	for (int i = 1; i < size; i++)
	{
		node = i;
		while (node != 0)
		{
			parent = (node - 1) / 2;
			if (arr[parent] < arr[node])
				swap(arr[parent], arr[node]);

			node = parent;
		}
	
		for (int i = size - 1; i >= 0; i--)
		{
			//가장큰값을 맨뒤로 보내기
			swap(arr[0], arr[i]);
			parent = 0;
			//힙구조로만들기 
			do {
				node = 2 * parent + 1;
				if (arr[node] < arr[node + 1] && node < i - 1) //오른쪽자식값이 더크다면 ++ 아니라면 왼쪽값이라는뜻
					node++;

				if (arr[parent] < arr[node] && node < i) //자식이 크면 교환
					swap(arr[parent], arr[node]);

				parent = node;
			} while (node<i);
		}
	}
}