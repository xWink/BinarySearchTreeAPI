/**
 ************************
 * Name: Shawn Kaplan
 * Date: March. 19, 2020
 ************************
**/

#include "BinarySearchTreeAPI.h"

BST* createBST(int dataSize, int (*compareFunction)(const void* a, const void* b), void (*deleteFunction)(void* data), void (*printFunction)(void* data)) {
    if (!compareFunction || !deleteFunction || dataSize < 0) {
        return NULL;
    }
    
    BST* tree = malloc(sizeof(BST));
    tree->root = NULL;
    tree->dataSize = dataSize;
    tree->compareFunction = compareFunction;
    tree->deleteFunction = deleteFunction;
    tree->printFunction = printFunction;
    
    return tree;
}

void deleteBST(BST* tree) {
    if (!tree) {
        return;
    }

    deleteSubtree(tree->root, tree->deleteFunction);
    free(tree);
}

BSTNode* createBSTNode(void* data) {
    BSTNode* node = malloc(sizeof(BSTNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void deleteSubtree(BSTNode* node, void (*deleteFunction)(void* data)) {
    if (!node || !deleteFunction) {
        return;
    }

    // Delete child nodes
    deleteSubtree(node->left, deleteFunction);
    deleteSubtree(node->right, deleteFunction);
    
    // Delete this node
    if (node->data) {
        deleteFunction(node->data);
    }
    free(node);
}

void insertData(BST* tree, void* data) {
    if (!tree || !data) {
        return;
    }
    
    BSTNode* currNode = tree->root;
    BSTNode* parentNode = tree->root;
    BSTNode* newNode = createBSTNode(data);
    
    // If there is no root, new node becomes the root
    if (!tree->root) {
        tree->root = newNode;
        return;
    }
    
    while (true) {
        parentNode = currNode;
        // Check left side
        if (tree->compareFunction(data, parentNode->data) < 0) {
            if ((currNode = currNode->left) == NULL) {
                parentNode->left = newNode;
                return;
            }
        }
        // Check right side
        else {
            if ((currNode = currNode->right) == NULL) {
                parentNode->right = newNode;
                return;
            }
        }
    }
}

void deleteData(BST* tree, void* data) {
    tree->root = deleteDataRecursive(tree, tree->root, data);
}

BSTNode* deleteDataRecursive(BST* tree, BSTNode* node, void* data) {
    if (!tree || !node) {
        return node;
    }
    
    // Check left children
    if (tree->compareFunction(data, node->data) < 0) {
        node->left = deleteDataRecursive(tree, node->left, data);
        return node;
    }
    // Check right children
    else if (tree->compareFunction(data, node->data) > 0) {
        node->right = deleteDataRecursive(tree, node->right, data);
        return node;
    }
    // Found match
    else {
        // If < 2 children
        if (!node->left) {
            BSTNode* temp = node->right;
            tree->deleteFunction(node->data);
            free(node);
            node = NULL;
            return temp;
        } else if (!node->right) {
            BSTNode* temp = node->left;
            tree->deleteFunction(node->data);
            free(node);
            node = NULL;
            return temp;
        }
        
        // If 2 children
        BSTNode* temp = findMin(node->right);
        memcpy(node->data, temp->data, tree->dataSize);
        node->right = deleteDataRecursive(tree, node->right, temp->data);
    } 
    return node;
}

BSTNode* findMin(BSTNode* node) {
    if (node && node->left) {
        return findMin(node->left);
    }
    
    return node;
}

BSTNode* findData(BST* tree, void* data) {
    if (!tree) {
        return NULL;
    }
    
    BSTNode* currNode = tree->root;
    BSTNode* parentNode = tree->root;
    
    // If there is no root, return NULL
    if (!tree->root) {
        return NULL;
    }

    while (true) {
        parentNode = currNode;
        // Check left side
        if (tree->compareFunction(data, parentNode->data) < 0) {
            if ((currNode = currNode->left) == NULL) {
                return NULL;
            }
        }
        // Check right side
        else if (tree->compareFunction(data, parentNode->data) > 0) {
            if ((currNode = currNode->right) == NULL) {
                return NULL;
            }
        }
        // Return match
        else {
            return currNode;
        }
    }
}

void printBST(BST* tree, BSTNode* node) {
    if (!tree || !node) {
        return;
    }
    
    if (node->left) {
        printBST(tree, node->left);
    }
    
    if (node->data) {
        tree->printFunction(node->data);
    }
    
    if (node->right) {
        printBST(tree, node->right);
    }
}
