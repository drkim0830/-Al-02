#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Max Heap
void MaxHeapSort(int arr[]);
void MaxHeapify(int arr[], int heap_size, int i);
void BuildMaxHeap(int arr[]);

//Min Heap
void MinHeapSort(int arr[]);
void MinHeapify(int arr[], int heap_size, int i);
void BuildMinHeap(int arr[]);

int Left(int i);
int Right(int i);

//Counting
void CountingSort(int arr[]);
int Max(int arr[]);

void printAll(int arr[]);
void swap(int arr[], int i, int j);

int test_num;
int heapify_num;

int main() {
	char testcase[10];
	printf(">> test case num (100 / 1000 / 10000)\n>> Input : ");
	scanf("%s", testcase);

	test_num = atoi(testcase);
	char inputFileName[100] = "test_";
	char *format = ".txt";
	strcat(inputFileName, testcase);
	strcat(inputFileName, format);

	int mode;
	printf(">> Input Sort Mode \n [0 : Max Heap Sort, 1 : Min Heap Sort, 2 : Conuting Sort ] : ");
	scanf("%d", &mode);

	FILE *input_FD;
	input_FD = freopen(inputFileName, "r", stdin);

	int *arr = (int *)malloc(sizeof(int) * test_num);

	int i;
	for (i = 0; i < test_num; i++) {
		int x;
		scanf("%d", &x);
		arr[i] = x;
	}
	
	clock_t start, end;
	float time;

	FILE *output_FD;

	start = clock();

	if (mode == 0) {
		MaxHeapSort(arr);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
		printf("How many times Heapify : %d\n", heapify_num);
		printf("Max Heap Sort Time : %f\n", time);
		output_FD = freopen("max_heap.txt", "w", stdout);
	}
	else if (mode == 1) {
		MinHeapSort(arr);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
		printf("How many times Heapify : %d\n", heapify_num);
		printf("Min Heap Sort Time : %f\n", time);
		output_FD = freopen("min_heap.txt", "w", stdout);
	}
	else if (mode == 2) {
		CountingSort(arr);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
		printf("Counting Sort Time : %f\n", time);
		output_FD = freopen("counting.txt", "w", stdout);
	}
	else {
		printf("Mode Error!");
		exit(1);
	}
		
	printAll(arr);
	fclose(input_FD);
	return 0;
}

void printAll(int arr[]) {
	int i;
	for (i = 0; i < test_num; i++) {
		printf("%d\n", arr[i]);
	}
}

void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void MaxHeapSort(int arr[]) {
	int heap_size = test_num;
	BuildMaxHeap(arr);
	int i;
	for (i = test_num - 1; i > 0; i--) {
		swap(arr, 0, i);
		heap_size--;
		MaxHeapify(arr, heap_size, 0);
	}
}

void BuildMaxHeap(int arr[]) {
	int heap_size = test_num;
	int i;
	for (i = (test_num / 2) - 1; i >= 0; i--) {
		MaxHeapify(arr, heap_size, i);
	}
}

void MaxHeapify(int arr[], int heap_size, int i) {
	heapify_num++;
	int largest = i;
	int left = Left(i);
	int right = Right(i);
	if (left < heap_size && arr[left] > arr[largest]) {
		largest = left;
	}
	if (right < heap_size && arr[right] > arr[largest]) {
		largest = right;
	}
	if (largest != i) {
		swap(arr, i, largest);
		MaxHeapify(arr, heap_size, largest);
	}
}

void MinHeapSort(int arr[]) {
	int heap_size = test_num;
	BuildMinHeap(arr);
	int i;
	for (i = test_num - 1; i > 0; i--) {
		swap(arr, 0, i);
		heap_size--;
		MinHeapify(arr, heap_size, 0);
	}
}

void BuildMinHeap(int arr[]) {
	int heap_size = test_num;
	int i;
	for (i = (test_num / 2) - 1; i >= 0; i--) {
		MinHeapify(arr, heap_size, i);
	}
}

void MinHeapify(int arr[], int heap_size, int i) {
	heapify_num++;
	int smallest = i;
	int left = Left(i);
	int right = Right(i);
	if (left < heap_size && arr[left] < arr[smallest]) {
		smallest = left;
	}
	if (right < heap_size && arr[right] < arr[smallest]) {
		smallest = right;
	}
	if (smallest != i) {
		swap(arr, i, smallest);
		MinHeapify(arr, heap_size, smallest);
	}
}

int Left(int i) {
	return i * 2 + 1;
}

int Right(int i) {
	return i * 2 + 2;
}

void CountingSort(int arr[]) {
	//array init
	int arrSize = test_num;
	int max_val = Max(arr);
	int *sortedArr = (int *)malloc(sizeof(int) * arrSize); 
	int *countingArr = (int *)malloc(sizeof(int) * (max_val + 1));

	int i, j;
	for (i = 0; i <= max_val; i++) {
		countingArr[i] = 0;
	}
	//각 원소의 수 
	for (j = 0; j < arrSize; j++) {
		countingArr[arr[j]]++;
	}

	//누적 합
	for (i = 1; i <= max_val; i++) {
		countingArr[i] = countingArr[i] + countingArr[i - 1];
	}

	for (j = arrSize-1; j >= 0; j--) {
		sortedArr[countingArr[arr[j]]] = arr[j];
		countingArr[arr[j]]--;
	}

	//copy sotred array to original array
	for (i = 1; i <= arrSize; i++) {
		arr[i-1] = sortedArr[i];
	}
}

int Max(int arr[]) {
	int arrSize = test_num;
	int i;
	int max = arr[0];
	for (i = 1; i < arrSize; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	return max;
}
