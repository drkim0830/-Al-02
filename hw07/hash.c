#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define HashSize 97
#define HashSize2 59
#define DELETED -1

void linear_insert(int arr[], int data);
bool linear_delete(int arr[], int data);
int linear_search(int arr[], int data);

void quadratic_insert(int arr[], int data);
bool quadratic_delete(int arr[], int data);
int quadratic_search(int arr[], int data);

void double_insert(int arr[], int data);
bool double_delete(int arr[], int data);
int double_search(int arr[], int data);

int collision = 0;

int main(){
    int mode;
    printf(">> Input Hashing Mode [1 : Linear, 2: Quadratic, 3: Double] : ");
    scanf("%d", &mode);

    char input[256];
    char *input_data;
    char inputFileName[256], deleteFileName[256], searchFileName[256];
    sprintf(inputFileName, "Data1.txt");
	sprintf(deleteFileName, "Data2.txt");
	sprintf(searchFileName, "Data3.txt");

    FILE *input_FD, *delete_FD, *search_FD;
    FILE *output_FD;
    clock_t start, end;
    float time;

    input_FD = fopen(inputFileName, "r");
    delete_FD = fopen(deleteFileName, "r");
    search_FD = fopen(searchFileName, "r");

    int *hashTable = (int *)malloc(sizeof(int) * HashSize);

    //Input Data
    start = clock();
    if (input_FD == NULL){
        printf("Could not open file %s",inputFileName);
        return 1;
    }
    while( !feof( input_FD ) ){
        input_data = fgets(input, sizeof(input), input_FD);
        if(input_data == NULL) break;
        int data = atoi(input_data);
        if(mode == 1){
            linear_insert(hashTable, data);
        }
        else if(mode == 2){
            quadratic_insert(hashTable, data);
        }
        else if(mode == 3){
            double_insert(hashTable, data);
        }
        else{
            printf("[!] Mode error!\n");
            exit(1);
        }
	}
    end = clock();
    time = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Insert Data Complete\t collision times : %d\n", collision);
    printf("Insert Data Time : %f\n", time);

    //Delete Data
    collision = 0;
    start = clock();
    if (delete_FD == NULL){
        printf("Could not open file %s",deleteFileName);
        return 1;
    }
    while( !feof( delete_FD ) ){
        input_data = fgets(input, sizeof(input), delete_FD);
        if(input_data == NULL) break;
        int data = atoi(input_data);
        if(mode == 1){
            //linear_delete(hashTable, data); ver. compare
            if(linear_delete(hashTable, data))
                printf("delete %d complete\n", data);
            else
                printf("Not exist %d\n", data);
        }
        else if(mode == 2){
            //quadratic_delete(hashTable, data); ver. compare
            if(quadratic_delete(hashTable, data))
                printf("delete %d complete\n", data);
            else
                printf("Not exist %d\n", data);
        }
        else if(mode == 3){
            //double_delete(hashTable, data); ver. compare
            if(double_delete(hashTable, data))
                printf("delete %d complete\n", data);
            else
                printf("Not exist %d\n", data);
        }
        else{
            printf("[!] Mode error!\n");
            exit(1);
        }
	}
    end = clock();
    time = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Delete Data Complete\t collision times : %d\n", collision);
    printf("Delete Data Time : %f\n", time);

    //Search Data
    collision = 0;
    start = clock();
    if (search_FD == NULL){
        printf("Could not open file %s",searchFileName);
        return 1;
    }

    //Output File
    if(mode == 1){
        output_FD = freopen("linear.txt", "w", stdout);
    }
    else if(mode == 2){
        output_FD = freopen("quadratic.txt", "w", stdout);
    }
    else if(mode == 3){
        output_FD = freopen("double.txt", "w", stdout);
    }

    while( !feof( search_FD ) ){
        input_data = fgets(input, sizeof(input), search_FD);
        if(input_data == NULL) break;
        int data = atoi(input_data);
        if(mode == 1){
            int index = linear_search(hashTable, data);
            if(index == -1)
                printf("Not exist %d\n", data);
            else
                printf("%d %d\n", data, index);
        }
        else if(mode == 2){
            int index = quadratic_search(hashTable, data);
            if(index == -1)
                printf("Not exist %d\n", data);
            else
                printf("%d %d\n", data, index);
        }
        else if(mode == 3){
            int index = double_search(hashTable, data);
            if(index == -1)
                printf("Not exist %d\n", data);
            else
                printf("%d %d\n", data, index);
        }
        else{
            printf("[!] Mode error!\n");
            exit(1);
        }
	}
    end = clock();
    time = (float)(end - start) / CLOCKS_PER_SEC;
    stdout = fdopen(0, "w");
    printf("Search Data Complete\t collision times : %d\n", collision);
    printf("Search Data Time : %f\n", time);

}

void linear_insert(int arr[], int data){
    int index = data % HashSize;
    while(arr[index] != NULL){
        index = (index + 1) % HashSize;
        collision++;
    }
    arr[index] = data;
}

bool linear_delete(int arr[], int data){
    int index = data % HashSize;
    while(arr[index] != NULL){
        if(arr[index] == data){
            arr[index] = DELETED;
            return true;
        }
        else{
            index = (index + 1) % HashSize;
            collision++;
        }
    }
    return false;
}

int linear_search(int arr[], int data){
    int index = data % HashSize;
    while(arr[index] != NULL){
        if(arr[index] == data){
            return index;
        }
        else{
            index = (index + 1) % HashSize;
            collision++;
        }
    }
    return -1;
}

void quadratic_insert(int arr[], int data){
    int i = 0;
    int index = data % HashSize;
    while(arr[index] != NULL){
        i++;
        index = ((data % HashSize) + i * i) % HashSize;
        collision++;
    }
    arr[index] = data;
}

bool quadratic_delete(int arr[], int data){
    int i = 0;
    int index = data % HashSize;
    while(arr[index] != NULL){
        if(arr[index] == data){
            arr[index] = DELETED;
            return true;
        }
        else{
            i++;
            index = ((data % HashSize) + i * i) % HashSize;
            collision++;
        }
    }
    return false;
}

int quadratic_search(int arr[], int data){
    int index = data % HashSize;
    int i = 0;
    while(arr[index] != NULL){
        if(arr[index] == data){
            return index;
        }
        else{
            i++;
            index = ((data % HashSize) + i * i) % HashSize;
            collision++;
        }
    }
    return -1;
}

void double_insert(int arr[], int data){
    int index = data % HashSize;
    int i = 0;
    while(arr[index] != NULL){
        i++;
        index = ((data % HashSize) + i * (data % HashSize2)) % HashSize;
        collision++;
    }
    arr[index] = data;
}

bool double_delete(int arr[], int data){
    int index = data % HashSize;
    int i = 0;
    while(arr[index] != NULL){
        if(arr[index] == data){
            arr[index] = DELETED;
            return true;
        }
        else{
            i++;
            index = ((data % HashSize) + i * (data % HashSize2)) % HashSize;
            collision++;
        }
    }
    return false;
}

int double_search(int arr[], int data){
    int index = data % HashSize;
    int i = 0;
    while(arr[index] != NULL){
        if(arr[index] == data){
            return index;
        }
        else{
            i++;
            index = ((data % HashSize) + i * (data % HashSize2)) % HashSize;
            collision++;
        }
    }
    return -1;
}