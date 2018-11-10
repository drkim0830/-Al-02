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
RBNode* rb_tree_insert(RBNode *node, int data);
RBNode* rb_tree_fix(RBNode *node);
void left_rotate(RBNode *root, RBNode *node);
void right_rotate(RBNode *root, RBNode *node);

void recoloring(RBNode *root, RBNode *node);
void restruct(RBNode *root, RBNode *node);


RBNode* grandparentNode(RBNode *node);
RBNode* uncleNode(RBNode *node);
RBNode* siblingNode(RBNode *node);


void printInorder(RBNode *root);
void printLevelOrder(RBNode *root);
void printGivenLevel(RBNode *root, int level);
int height(RBNode* node);

RBNode *root = NULL;
RBNode *NIL;

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
    start = clock();
    while( !feof( input_FD ) ){
        input_data = fgets(input, sizeof(input), input_FD);
        if(input_data == NULL) break;
        int data = atoi(input_data);
        printf("data : %d\n", data);
        if(i == 0){
            root = rb_tree_insert(root, data);
        }
        else{
            rb_tree_insert(root, data);
        }
        i++;
	}
    end = clock();
    time = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Time : %f\n", time);

    printf("Level Order : \n");
    printLevelOrder(root);
    
    printf("\nIn Order : \n");
    printInorder(root);

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
    if(root == NULL)
        new_node->color = BLACK;
    else
        new_node->color = RED;
    new_node->left = NIL;
    new_node->right = NIL;
    new_node->parent = NULL;

    return new_node;
}

RBNode* rb_tree_insert(RBNode *node, int data){
    RBNode *temp = (RBNode *)malloc(sizeof(RBNode));
    RBNode *new_node = (RBNode *)malloc(sizeof(RBNode));

    if (node == NIL || node == NULL){
        new_node = newNode(data);
        return new_node;
    } 

    if(data < node->data){
        temp = rb_tree_insert(node->left, data);
        node->left = temp;
        temp->parent = node;
    }
    else if(data > node->data){
        temp = rb_tree_insert(node->right, data);
        node->right = temp;
        temp->parent = node;
    }
    printf("temp : %d\n", temp->data);
    printf("temp parent : %d\n", temp->parent->data);

    rb_tree_fix(temp);
    printLevelOrder(root);

    return node;
}

RBNode* rb_tree_fix(RBNode *node){
    RBNode *parent = node->parent;

    if(parent == NULL){
        node->color = BLACK;
    }
    else if(parent->color == BLACK){
        return node;
    }
    else if(parent->color == RED){
        RBNode *grandparent = grandparentNode(node);
        RBNode *uncle = uncleNode(node);
        RBNode *sibling = siblingNode(node);
        RBNode *lchild = node->left;
        RBNode *rchild = node->right;

        //case 1 : Recoloring
        if(uncle->color == RED){
            grandparent->color = RED;
            parent->color = BLACK;
            uncle->color = BLACK;
            return rb_tree_fix(grandparent);
        }
        //case 2-1 : switch case 2-2
        else if(uncle->color == BLACK && parent->right == node){
            //rotate_left(parent)
            parent->right = node->left;
            if(lchild)
                lchild->parent = parent;
            node->parent = grandparent;
            grandparent->left = node;
            node->left = parent;
            parent->parent = node;
            return rb_tree_fix(parent);
        }
        //case 2-2 : Restructure
        else if(uncle->color == BLACK && parent->left == node){
            //rotate_right(parent)
            grandparent->left = sibling;
            if(sibling)
                sibling->parent = grandparent;
            parent->parent = grandparent->parent;
            if(grandparent->parent == NULL){
                root = parent;
            }
            else if(grandparent->parent->left == grandparent)
                grandparent->parent->left = parent;
            else if(grandparent->parent->right == grandparent)
                grandparent->parent->right = parent;
            parent->right = grandparent;
            grandparent->parent = parent;

            parent->color = BLACK;
            grandparent->color = RED;

            return node;
        }
    }
    return node;
}

RBNode* grandparentNode(RBNode *node){
    return node->parent->parent;
}

RBNode* uncleNode(RBNode *node){
    return siblingNode(node->parent);
}

RBNode* siblingNode(RBNode *node){
    if(node->parent->left == node)
        return node->parent->right;
    else
        return node->parent->left;
}

void printInorder(RBNode *root){
    if(root){
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