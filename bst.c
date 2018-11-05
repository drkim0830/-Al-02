#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node{
	int data;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
} Node;

Node* newNode(int data);

Node* tree_insert(Node *node, int key);
Node* tree_R_search(Node *node, int data);
Node* tree_I_search(Node *node, int data);

Node* successor(Node *node);
Node* tree_minimum(Node *node);
Node* predecessor(Node *node);
Node* tree_maximum(Node *node);

void tree_delete(Node *node, int data);
void transplant(Node *node, Node *u, Node *v);
void printInorder(Node *node);
void printBST(Node *node);

void balance_median_insert(int arr[], int p, int r);
void median_insert(int arr[]);
void QuickSort(int arr[], int p, int r);
int partition(int arr[], int p, int r);
void swap(int arr[], int i, int j);

/* Function protoypes */
void printLevelOrder(Node* root);
void printGivenLevel(Node* root, int level); 
int height(Node* node); 

Node *root = NULL;

int main(){
	int i = 0;
    char input[256];
    char *input_data;
    char inputFileName[256];
    printf(">> Input Test File Name : ");
    scanf("%s", inputFileName);

    FILE *input_FD;
    FILE *output_FD;
    clock_t start, end;
    float time;

    input_FD = fopen(inputFileName, "r");
    if (input_FD == NULL){
        printf("Could not open file %s",inputFileName);
        return 1;
    }
    start = clock();
    while( !feof( input_FD ) ){
        input_data = fgets(input, sizeof(input), input_FD);
        if(input_data == NULL) break;
		int x = atoi(input_data);
        if(i == 0){
				root = tree_insert(root, x);
			}
		else{
			tree_insert(root, x);
		}
	}
	end = clock();
	time = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Time : %f\n", time);
	
	printf("Level Order : \n");
	printLevelOrder(root);

	output_FD = freopen("inorderTree.txt", "w", stdout);
	printInorder(root);

	fclose(output_FD);
	fclose(input_FD);

	return 0;
}

Node* newNode(int data){
	Node *new_node = (Node *)malloc(sizeof(Node));
    if(new_node == NULL)
    {
        fprintf (stderr, "error memory!! (create_node)\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
	new_node->parent = NULL;

    return new_node;
}

Node* tree_insert(Node *node, int data){
	Node *temp = (Node *)malloc(sizeof(Node));

	// if the tree is empty, return a new node
	if (node == NULL) return newNode(data);

	if(data < node->data){
		temp = tree_insert(node->left, data);
		node->left = temp;
		temp->parent = node;
	}
	else if(data > node->data){
		temp = tree_insert(node->right, data);
		node->right = temp;
		temp->parent = node;
	}

	return node;
}

/*Recursive Search*/
Node* tree_R_search(Node *node, int data){
	if(node){
		if(data == node->data)
			return node;
		if(data < node->data)
			return tree_R_search(node->left, data);
		else
			return tree_R_search(node->right, data);
	}
	else
		return NULL;
}

/*Iterative Search*/
Node* tree_I_search(Node *node, int data){
	while (node != NULL && data != node->data){
		if(data < node->data)
			node = node->left;
		else
			node = node->right;
	}
	return node;
}

Node* succsesor(Node *node){
	if(node->right != NULL){
		return tree_minimum(node->right);
	}

	Node *y = node->parent;
	while( y != NULL && node == y->right){
		node = y;
		y = y->parent;
	}
	return y;
}

Node* tree_minimum(Node *node){
	Node *current = node;
	while(current->left != NULL){
		current = current->left;
	}

	return current;
}

Node* predecessor(Node *node){
	if(node->left != NULL){
		return tree_maximum(node->left);
	}
	Node *y = node->parent;
	while(y != NULL && node == y->left){
		node = y;
		y = y->parent;
	}

	return y;
}

Node* tree_maximum(Node *node){
	Node *current = node;
	while(current->right != NULL){
		current = current->right;
	}
	return current;
}

void tree_delete(Node *node, int data){
	Node *z = (Node *)malloc(sizeof(Node));
	z = tree_R_search(node, data);
	//z = tree_I_search(node, data);
	if(z->left == NULL)
		transplant(node, z, z->right);
	else if(z->right == NULL)
		transplant(node, z, z->left);
	else{
		Node *y = tree_minimum(z->right);
		if(y->parent != z){
			transplant(node, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(node, z, y);
		y->left = z->left;
		y->left->parent = y;
	}
}

void transplant(Node *node, Node *u, Node *v){
	//if u == root
	if(u->parent == NULL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if(v != NULL)
		v->parent = u->parent;
}
void printInorder(Node *node){
	if(node){
		printInorder(node->left);
		printf("%d\n", node->data);
		printInorder(node->right);
	}
}

void QuickSort(int arr[], int p, int r) {
   int q;
   if (p<r) {
      q = partition(arr, p, r);
      QuickSort(arr, p, q - 1);
      QuickSort(arr, q + 1, r);
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
void swap(int arr[], int i, int j) {
   int temp;
   temp = arr[i];
   arr[i] = arr[j];
   arr[j] = temp;
}

  
/* Function to print level order traversal a tree*/
void printLevelOrder(Node* root) 
{ 
    int h = height(root); 
    int i; 
    for (i=1; i<=h; i++) {
        printGivenLevel(root, i);
		printf("\n");
	}
} 
  
/* Print nodes at a given level */
void printGivenLevel(Node* root, int level) 
{ 
    if (root == NULL){
		printf("- ");
        return; 
	}
    if (level == 1) 
        printf("%d ", root->data); 
    else if (level > 1) 
    { 
        printGivenLevel(root->left, level-1); 
        printGivenLevel(root->right, level-1); 
    } 
} 
  
/* Compute the "height" of a tree -- the number of 
    nodes along the longest path from the root node 
    down to the farthest leaf node.*/
int height(Node* node) 
{ 
    if (node==NULL) 
        return 0; 
    else
    { 
        /* compute the height of each subtree */
        int lheight = height(node->left); 
        int rheight = height(node->right); 
  
        /* use the larger one */
        if (lheight > rheight) 
            return(lheight+1); 
        else return(rheight+1); 
    } 
} 
