#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure of a node in the binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Recursive insertion function
struct Node* recursiveInsert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = recursiveInsert(root->left, data);
    } else if (data > root->data) {
        root->right = recursiveInsert(root->right, data);
    }
    return root;
}

// Iterative insertion function
struct Node* iterativeInsert(struct Node* root, int data) {
    struct Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }

    struct Node* current = root;
    struct Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            free(newNode); // Avoid duplicate values
            return root;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

// In-order traversal to verify correctness
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Function to free the tree
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main function to compare performance
int main() {
    struct Node* root1 = NULL; // Root for recursive insertion
    struct Node* root2 = NULL; // Root for iterative insertion
    int data[] = {30, 20, 40, 10, 25, 35, 50, 5, 15, 45};
    int n = sizeof(data) / sizeof(data[0]);
    clock_t start, end;

    // Measuring recursive insertion time
    start = clock();
    for (int i = 0; i < n; i++) {
        root1 = recursiveInsert(root1, data[i]);
    }
    end = clock();
    double recursiveTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Recursive insertion time: %f seconds\n", recursiveTime);

    // Measuring iterative insertion time
    start = clock();
    for (int i = 0; i < n; i++) {
        root2 = iterativeInsert(root2, data[i]);
    }
    end = clock();
    double iterativeTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Iterative insertion time: %f seconds\n", iterativeTime);

    // Display the trees (optional)
    printf("In-order traversal of the tree after recursive insertions: ");
    inorderTraversal(root1);
    printf("\n");

    printf("In-order traversal of the tree after iterative insertions: ");
    inorderTraversal(root2);
    printf("\n");

    // Free the trees
    freeTree(root1);
    freeTree(root2);

    // Comparison result
    if (recursiveTime < iterativeTime) {
        printf("Recursive insertion is faster.\n");
    } else {
        printf("Iterative insertion is faster.\n");
    }

    return 0;
}