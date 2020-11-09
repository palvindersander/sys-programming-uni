#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bst.h"


Node* insertNode(Node *root, int value) {

    // find empty branch
    // insert new node

    if(root == NULL) {
        Node *new = (Node*)malloc(sizeof(struct Node));
        new->data = value;
        new->left = NULL;
        new->right = NULL;
        return new;
    }
    else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }
    else {
        root->left = insertNode(root->left, value);
    }

    return root;

}

Node* getMinimum(Node *root) {

    if(root == NULL) {
        return NULL;
    }
    else if (root->left != NULL) {
        return getMinimum(root->left);
    }
    else {
        return root;
    }

}

Node* deleteNode(Node *root, int value) {
    
    // find node to delete
    // handle no children
    // handle single child
    // handle two children

    if(root == NULL) {
        return NULL;
    }

    if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else {

        if (root->right == NULL && root->left == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL || root->right == NULL) {
            
            if(root->left != NULL) {
                Node *temp = root->left;
                free(root);
                return temp;
            }
            else {
                Node *temp = root->right;
                free(root);
                return temp;
            }

        }
        else {
            Node *temp = getMinimum(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }

    }

    return root;

}

void printSubtree(Node *N) {

    // left root right

    if(N != NULL) {
        printSubtree(N->left);
        printf("%d\n", N->data);
        printSubtree(N->right);
    }

}

int countNodes(Node *N) {

    // root left right

    int count = 0;

    if(N != NULL) {
        count = count + 1;
        count = count + countNodes(N->left);
        count = count + countNodes(N->right);
    }

    return count;

}

Node* freeSubtree(Node *N) {

    // left right root

    if(N != NULL) {
        freeSubtree(N->left);
        freeSubtree(N->right);
        free(N);
    }

    return NULL;

}

int sumSubtree(Node *N) {

    // root left right

    int count = 0;

    if(N != NULL) {
        count = count + N->data;
        count = count + sumSubtree(N->left);
        count = count + sumSubtree(N->right);
    }

    return count;
    
}