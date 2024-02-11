//Tree traversal in C
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct node {
    char data[20];
    struct node *left;
    struct node *right;
}NODE;

NODE *newNode(char *x){//function to create a new node
NODE *n;
char y;
n = (NODE*) malloc(sizeof(NODE));

strcpy(n->data, x);
n->left = NULL;
n->right = NULL;
}
void infix(NODE* n){//L->N->R
if(n==NULL)
    return;
infix(n->left);//traverse the left child in inorder recursively
printf("%s ", n->data);getch();//visit the root
infix(n->right);//traverse the right child in inorder recursively
}
void prefix(NODE* n){//N->L->R
if(n==NULL)
    return;

printf("%s ", n->data);getch();//visit the root
prefix(n->left);//traverse the left child in preorder recursively
prefix(n->right);//traverse the right child in preorder recursively

}
void postfix(NODE* n){//L->R->N
if(n==NULL)
    return;
postfix(n->left);//traverse the left child in postorder recursively
postfix(n->right);//traverse the right child in postorder recursively
printf("%s ", n->data);getch();//visit the root

}
int main(){
NODE *root;
root = newNode("/");
root->left=newNode("+");
root->left->left = newNode("a");
root->left->right = newNode("d");
root->right = newNode("*");
root->right->right = newNode("b");
root->right->left = newNode("c");
printf("\nPrefix Traversal: ");
prefix(root);
printf("\nInfix Traversal: ");
infix(root);
printf("\nPostfix Traversal: ");
postfix(root);
return 0;
getch();
}
