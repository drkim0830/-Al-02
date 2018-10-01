#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ���� ���Ḯ��Ʈ ���� - MIT Licence : https://github.com/tehp/doublylinkedlist_c */

/*
Define structure Node, DoublyLinkedList
*/
typedef struct Node {
	int data;
	struct Node *next;
	struct Node *prev;

}Node;

typedef struct DoublyLinkedList
{
	unsigned int count;
	struct Node *head;
	struct Node *tail;

}DLL;

/*
Declare functions (DLL, Print, Sort)
*/
DLL *createList();
Node *createNode(DLL *list, int data);
Node *putNode(Node *target, int i);
void swapNode(Node *prevNode, Node *nextNode);

void print(Node *node);
void printAll(DLL *list);

void InsertionSort(DLL * list);
void BubbleSort(DLL * list);
void SelectionSort(DLL * list);


/*
Program Fuction for Sort
- Insertion Sort
- Bubble Sort
- Selection Sort
*/
int main() {
	
	/* �׽�Ʈ ���̽��� �ޱ� ���� ���� ���� */
     char testcase[10];
     printf(">> test case num (100 / 1000 / 10000)\n>> Input : ");
     scanf("%s", testcase);
    
	 /* �׽�Ʈ ���̽� ��ŭ �ݺ��ϱ� ���� ���� ����ȯ */
    int test_num = atoi(testcase);
     
	/* ���ϸ� ���� */
     char inputFileName[100] = "test_";
     char *format = ".txt";

	 /* ���ϸ� ���˿� ���� ���ڿ� ���� */
	strcat(inputFileName, testcase);
	strcat(inputFileName, format);
	
	/* ���� ��� ���� */
	int mode;
	printf(">> Input Sort Mode \n [0 : Insertion, 1 : Bubble, 2 : Selection ] : ");
	scanf("%d", &mode);
	
	/* ��Ʈ�� ���� ���� freopen() */
	FILE *input_FD;
	input_FD = freopen(inputFileName, "r", stdin);
	
	/* ���߿��Ḯ��Ʈ ����(�ʱ�ȭ) */
	DLL *list = createList();
	
	/* ���� ũ�⸸ŭ �Է¹��� ���� �������Ͽ� list�� �߰� */
	int i;
	for (i = 0; i < test_num; i++) {
		int x;
		scanf("%d", &x);
		createNode(list, x);
	}

	//���� �ð� ���� ����
	clock_t start, end;
	float time;

	//��� ����
	FILE *output_FD;
	
	start = clock();
	/* ���� ��Ŀ� ���� ���� */
	if (mode == 0) {
		InsertionSort(list);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
		printf("Insertion Sort ���� �ð� : %.4f\n", time);
		output_FD = freopen("insertion.txt", "w", stdout);
	}
	else if (mode == 1) {
		BubbleSort(list);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
		printf("Bubble Sort ���� �ð� : %.4f\n", time);
		output_FD = freopen("bubble.txt", "w", stdout);
	}
	else if (mode == 2) {
		SelectionSort(list);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
		printf("Selection Sort ���� �ð� : %.4f\n", time);
		output_FD = freopen("selection.txt", "w", stdout);
	}

	/* ����Ʈ ��� */
	printAll(list);

	fclose(input_FD);

	return 0;
}

/* create (a list) */
DLL *createList() {
	DLL *list;
	if ((list = (DLL*)malloc(sizeof(DLL))) == NULL) {
		fprintf(stderr, "Could not allocate memory for a new DoublyLinkedList.\n");
	}
	list->head = NULL;
	list->tail = NULL;

	list->count = 0;
	return list;
}

/* create (a node) */
Node *createNode(DLL *list, int data) {
	Node *newNode;
	if ((newNode = (Node*)malloc(sizeof(Node))) == NULL) {
		fprintf(stderr, "Could not allocate memory for a new Node.\n");
	}
	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = NULL;
	/* if this is the first node in the list, make it head, else add to end */
	if (list->count == 0) {
		list->head = newNode;
	}
	else {
		Node *move = list->head;
		while (move->next != NULL) {
			move = move->next;
		}
		move->next = newNode;
		newNode->prev = move;
	}
	list->tail = newNode;
	list->count++;
	return newNode;
}

Node *putNode(Node *target, int data) {
	Node * newNode;
	if ((newNode = (Node*)malloc(sizeof(Node))) == NULL) {
		fprintf(stderr, "Could not allocate memory for a new Node.\n");
	}
	newNode->data = data;

	Node* move = target->next;
	move->prev = newNode;
	newNode->next = move;
	target->next = newNode;
	newNode->prev = target;

	return newNode;
}


void swapNode(Node *prevNode, Node *nextNode) {
	Node *temp;
	if ((temp = (Node*)malloc(sizeof(Node))) == NULL) {
		fprintf(stderr, "Could not allocate memory for a temp node.\n");
	}
	temp->data = prevNode->data;
	prevNode->data = nextNode->data;
	nextNode->data = temp->data;
}

/* prints a node's data */
void print(Node *node) {
	fprintf(stdout, "[%d]", node->data);
}

/* traverses the list from head to tail, printing data (used in tests) */
void printAll(DLL *list) {
	Node *move = list->head;
	while (move != NULL) {
		print(move);
		move = move->next;
		if (move == list->tail) {
			break;
		}
		printf("<->");
	}
}

void InsertionSort(DLL * list) {
	Node *i, *j;
	int key;
	//for j = 2 to A.length
	for (j = list->head->next; j != NULL; j = j->next) {
		key = j->data;	// key = A[j]
		i = j->prev;	// i = j - 1
		//while i > 0 and A[i] > key
		while (i != NULL && (i->data) > key) {
			i->next->data = i->data;	//A[i+1] = A[i]
			i = i->prev;				//i = i - 1
		}
		//���� head�� �ּҰ��̸�
		if (i == NULL) {
			list->head->data = key;
		}
		else
			i->next->data = key;	//A[i+1] = key
	}
}

void BubbleSort(DLL * list) {
	Node *i, *j;
	//for i = 1 to A.length
	for (i = list->head; i != NULL; i = i->next) {
		//for j = A.lenght down to i + 1
		for (j = list->tail; j != i; j = j->prev) {
			//if A[j] < A[j - 1]
			if ((j->data) < (j->prev->data)) {
				//swap(A[j], A[j - 1]
				swapNode(j, j->prev);
			}
		}
	}
}

void SelectionSort(DLL * list) {
	Node *i, *j;
	Node *min;

	if ((min = (Node*)malloc(sizeof(Node))) == NULL) {
		fprintf(stderr, "Could not allocate memory for a min node.\n");
	}

	//for i = 1 to A.length
	for (i = list->head; i != NULL; i = i->next) {
		min = i;	//Min = i
		//for j = i+1 to A.length
		for (j = i->next; j != NULL; j = j->next) {
			//if A[j] < A[Min]
			if (j->data < min->data)
				min = j;	//Min = j
		}
		//swap(A[i], A[Min])
		swapNode(i, min);
	}
}