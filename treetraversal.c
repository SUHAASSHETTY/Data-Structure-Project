#include <stdio.h>
#include <stdlib.h>

struct TreeNode 
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// in-order traversal of the tree
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}
//  pre-order traversal of the tree
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}
// post-order traversal of the tree
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}                   


int main() 
{
    struct TreeNode* root = createNode(10);
    root->left = createNode(8);
    root->right = createNode(16);
    root->left->left = createNode(1);
    root->left->right = createNode(9);
    root->right->left = createNode(13);
    root->right->right = createNode(15);

    //in-order traversal
    printf("In-order Traversal: ");
    inorderTraversal(root);
    printf("\n");

    //pre-order traversal
    printf("pre-order Traversal: ");
    preorderTraversal(root);
    printf("\n");

    //post-order traversal
    printf("post-order Traversal: ");
    postorderTraversal(root);
    printf("\n");
    return 0;
}
