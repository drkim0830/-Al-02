#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NUM 10000;

int insertion_count = 0;
int merge_count = 0;
int quick_count = 0;

void InsertionSort(int arr[], int p, int r);
void MergeSort(int arr[], int p, int r);
void MergeSortWithInsertionSort(int arr[], int p, int r);
void Merge(int arr[], int p, int mid, int r);

void QuickSort(int arr[], int p, int r);
void QuickRandSort(int arr[], int p, int r);
int partition(int arr[], int p, int r);

int Rand_Partition(int arr[], int p, int r);
int Random(int p, int r);

void swap(int arr[], int i, int j);

void printAll(int arr[], int test_num);

int main() {
    char testcase[10];
	printf(">> test case num (100 / 1000 / 10000)\n>> Input : ");
	scanf("%s", testcase);
	
	int test_num = atoi(testcase);
	
	char inputFileName[100] = "test_";
	char *format = ".txt";
	strcat(inputFileName, testcase);
	strcat(inputFileName, format);
	
	int mode;
	printf(">> Input Sort Mode \n [0 : Merge Sort, 1 : Merge+Insertion Sort, 2 : Quick Sort, 3 : Quiick_Random Sort ] : ");
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
		MergeSort(arr, 0 , test_num-1);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
		printf("Merge_sort count : %d\n", merge_count); 
		printf("Merge Sort Time : %f\n", time);
		output_FD = freopen("merge.txt", "w", stdout);
	}
	else if (mode == 1) {
		MergeSortWithInsertionSort(arr, 0 , test_num-1);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
		printf("Merge_sort count : %d\n", merge_count);
		printf("Insertion Sort count : %d\n", insertion_count);
		printf("Merge Sort With Insertion Sort Time : %f\n", time);
		output_FD = freopen("merge_insertion.txt", "w", stdout);
	}
	else if (mode == 2) {
		QuickSort(arr, 0, test_num - 1);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
		printf("Quick_sort count : %d\n", quick_count);
		printf("Quick Sort(Partition) Time : %.4f\n", time);
		output_FD = freopen("quick.txt", "w", stdout);
	}
	else if (mode == 3) {
		QuickRandSort(arr, 0, test_num - 1);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
		printf("Quick_sort count : %d\n", quick_count);
		printf("Quick Sort(Randomize Partition) Time : %.4f\n", time);
		output_FD = freopen("quick_rand.txt", "w", stdout);
	}
	else {
		printf("Mode Error!");
		exit(1);
	}

	printAll(arr, test_num);
	
	fclose(input_FD);
	
	return 0;
}

void printAll(int arr[], int test_num) {
	int i;
	for (i = 0; i < test_num; i++) {
		printf("%d\n", arr[i]);
	}
}

int getSizeArr(int arr[]) {
	int i;
	int max = MAX_NUM;
	for (i = 0; i < max; i++) {
		if (arr[i] < 0)
			return i;
	} 
}

void InsertionSort(int arr[], int p, int r) {
	int i, j;
	int key;
	insertion_count++;
	for (j = p + 1; j <= r; j++) {
		key = arr[j];
		i = j - 1;
		while (i >= p && arr[i] > key) {
			arr[i + 1] = arr[i];
			i--;
		}
		arr[i + 1] = key;
	}
}

void MergeSort(int arr[], int p, int r) {
	merge_count++;
	if (p < r) {
		int mid = (p + r) / 2;
		
		MergeSort(arr, p, mid);
		MergeSort(arr, mid+1, r);
		Merge(arr, p, mid, r);
	}
}

void MergeSortWithInsertionSort(int arr[], int p, int r) {
	merge_count++;
	if ((r-p) <= 20) {
		InsertionSort(arr, p, r);
	}
	else{
		int mid = (p + r) / 2;

		MergeSortWithInsertionSort(arr, p, mid);
		MergeSortWithInsertionSort(arr, mid + 1, r);
		Merge(arr, p, mid, r);
	}
}

void Merge(int arr[], int p, int mid, int r) {
	int k;
	int i = p;
	int j = mid + 1;
	int arrSize = getSizeArr(arr);
	int *sortArr = (int *)malloc(sizeof(int) * arrSize);

	for (k = p; k <= r; k++) {
		if (i <= mid && (j > r || arr[i] <= arr[j])) {
			sortArr[k] = arr[i];
			i++;
		}
		else {
			sortArr[k] = arr[j];
			j++;
		}
	}
	for (i = p; i <= r; i++) {
		arr[i] = sortArr[i];
	}
}
void QuickSort(int arr[], int p, int r) {
	quick_count++;
	int q;
	if (p<r) {
		q = partition(arr, p, r);
		QuickSort(arr, p, q - 1);
		QuickSort(arr, q + 1, r);
	}
}

void QuickRandSort(int arr[], int p, int r) {
	quick_count++;
	int q;
	if (p < r) {
		q = Rand_Partition(arr, p, r);
		QuickRandSort(arr, p, q - 1);
		QuickRandSort(arr, q + 1, r);
	}
}

int partition(int arr[], int p, int r) {
	int x, i, j;
	x = arr[r];
	i = p - 1;
		
	for (j = p; j < r; j++) {
		if (arr[j] <= x) {
			i++;
			swap(arr, i, j);
		}
	}
	swap(arr, i + 1, r);
		
	return i + 1;
}

int Rand_Partition(int arr[], int p, int r) {
	int x, i, j;

	/* p~r 사이에 있는 수를 index를 pivot으로 설정*/
	int rand_index = Random(p, r);
	/* 해당 하는 수를 r과 swap함으로써 p~r까지 Quick Sort 과정이 동일*/
	swap(arr, rand_index, r);

	x = arr[r];
	i = p - 1;
	for (j = p; j < r; j++) {
		if (arr[j] <= x) {
			i++;
			swap(arr, i, j);
		}
	}
	swap(arr, i + 1, r);

	return i + 1;
}

int Random(int p, int r) {
	srand(time(NULL));
	int random = (rand() % (r - p)) + p;

	return random;
}

void swap(int arr[], int i, int j) {
	int temp;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}