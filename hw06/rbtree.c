#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RED 'R'
#define BLACK 'B'

typedef struct RBNode
{
    int data;
    char color;

    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
} RBNode;
RBNode* NILNode();
RBNode* newNode(int data);
void rb_tree_insert(RBNode *node, RBNode *z);
void rb_tree_fixup(RBNode *node, RBNode *z);
void left_rotate(RBNode *node, RBNode *z);
void right_rotate(RBNode *node, RBNode *z);

void printInorder(RBNode *root);
void printLevelOrder(RBNode *root);
void printGivenLevel(RBNode *root, int level);
int height(RBNode* node);

RBNode *NIL;
RBNode *root;

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
    NIL = NILNode();
    root = NIL;
    start = clock();
    while( !feof( input_FD ) ){
        input_data = fgets(input, sizeof(input), input_FD);
        if(input_data == NULL) break;
        int data = atoi(input_data);
        RBNode *z = newNode(data);
        rb_tree_insert(root, z);
	}
    end = clock();
    time = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Time : %f\n", time);

    printf("Level Order : \n");
    printLevelOrder(root);
    
    // printf("\nIn Order : \n");
    // printInorder(root);

    output_FD = freopen("levelOrderTree.txt", "w", stdout);
    printLevelOrder(root);
    stdout = fdopen(0, "w");
    output_FD = freopen("inorderTree.txt", "w", stdout);
    printInorder(root);

    fclose(output_FD);
    fclose(input_FD);

    return 0;
}

RBNode* NILNode(){
    RBNode *nil = (RBNode *)malloc(sizeof(RBNode));

    nil->color = BLACK;

    return nil;
}

RBNode* newNode(int data){
    RBNode *new_node = (RBNode *)malloc(sizeof(RBNode));
    if(new_node == NULL){
        fprintf(stderr, "error memory! (create node)\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NIL;
    new_node->right = NIL;
    new_node->parent = NIL;

    return new_node;
}

void rb_tree_insert(RBNode *node, RBNode *z){
    RBNode *y = NIL;
    RBNode *x = node;
    while(x != NIL){
        y = x;
        if(z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if(y == NIL)
        root = z;
    else if( z->data < y->data)
        y->left = z;
    else
        y->right = z;
    z->left = NIL;
    z->right = NIL;
    z->color = RED;
    rb_tree_fixup(node, z);
}

void rb_tree_fixup(RBNode *node, RBNode *z){
    RBNode *y = (RBNode *)malloc(sizeof(RBNode));

    while(z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->right){
                    z = z->parent;
                    left_rotate(node, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(node, z->parent->parent);
            }
        }
        else{
            y = z->parent->parent->left;
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    right_rotate(node, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(node, z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void left_rotate(RBNode *node, RBNode *z){
    RBNode *p = z->parent;
    RBNode *y = z->right;
    
    z->right = y->left;
    if( y->left != NIL)
        y->left->parent = z;
    y->parent = z->parent;
    if(z->parent == NIL)
        root = y;
    else if(z == z->parent->left)
        z->parent->left = y;
    else
        z->parent->right = y;

    y->left = z;
    z->parent = y;
}

void right_rotate(RBNode *node, RBNode *z){
    RBNode *p = z->parent;
    RBNode *y = z->left;

    z->left = y->right;
    if( y->right != NIL)
        y->right->parent = z;
    y->parent = z->parent;
    if(z->parent == NIL)
        root = y;
    else if(z == z->parent->left)
        z->parent->left = y;
    else
        z->parent->right = y;
    
    y->right = z;
    z->parent = y;
}

void printInorder(RBNode *root){
    if(root != NIL){
        printInorder(root->left);
        printf("%d\n", root->data);
        printInorder(root->right);
    }
}

void printLevelOrder(RBNode *root){
    int h = height(root);
    int i;
    for(i = 1; i <= h; i++){
        printGivenLevel(root, i);
        printf("\n");
    }
}

void printGivenLevel(RBNode *root, int level){
    if(root == NULL){
        printf("- ");
        return;
    }
    if(level == 1){
        if(root == NIL)
            printf("(NIL) ");
        else
            printf("(%d, %c) ", root->data, root->color);

    }
    else if(level > 1){
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

int height(RBNode *node){
    if(node == NULL)
        return 0;
    else{
        int lheight = height(node->left);
        int rheight = height(node->right);

        if(lheight > rheight)
            return(lheight + 1);
        else
            return(rheight + 1);
    }
}