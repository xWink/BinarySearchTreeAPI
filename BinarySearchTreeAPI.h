/**
 ************************
 * Name: Shawn Kaplan
 * ID: 9066499
 * Date: March. 19, 2020
 * Assignment: A4
 ************************
**/

#ifndef BST_API_H
#define BST_API_H

#include <stdio.h>
#include <stdlib.h>

typedef struct bstNode {
    void* data;
    struct bstNode* left;
    struct bstNode* right;
} BSTNode;

typedef struct bst {
    BSTNode* root;
    int dataSize;
    int (*compareFunction)(const void* a, const void* b);
    void (*deleteFunction)(void* data);
    void (*printFunction)(void* data);
} BST;

/**
 * Creates a new binary search tree.
 * @param dataSize - the size of the datatype stored in the tree
 * @param compareFunction - a pointer to a function used to compare stored data
 * @param deleteFunction - a pointer to a function used to delete stored data
 * @param printFunction - a pointer to a function used to print stored data
 * @return a pointer to a newly allocated binary search tree
 */
BST* createBST(
    int dataSize,
    int (*compareFunction)(const void* a, const void* b),
    void (*deleteFunction)(void* data),
    void (*printFunction)(void* data));

/**
 * Deletes an entire binary search tree, including its data.
 * @param tree - the tree to be deleted
 */
void deleteBST(BST* tree);

/**
 * Deletes a subtree of a binary search tree.
 * @param node - the root of the subtree
 * @param deleteFunction - a pointer to the function used to delete node data
 */
void deleteSubtree(BSTNode* node, void (*deleteFunction)(void* data));

/**
 * Prints a binary search tree in ascending order starting from a given node.
 * @param tree - the tree which contains the nodes whose data will be printed
 * @param node - the root node of the subtree (or entire tree) to be printed
 */
void printBST(BST* tree, BSTNode* node);

/**
 * Creates a new node for a binary search tree which contains the given data.
 * @param data - the pointer to the data that will be stored by the new node
 * @return a pointer to a new binary search tree node with null children and
 *         a data pointer pointing to the given data
 */
BSTNode* createBSTNode(void* data);

/**
 * Creates a new node with given data and inserts the node to a binary search tree.
 * @param tree - the tree which will contain the new data node
 * @param data - the data which will be inserted to the tree
 */
void insertData(BST* tree, void* data);

/**
 * Deletes all occurences of a given data value in a binary search tree.
 * @param tree - the tree to have its data deleted
 * @param data - a pointer to data with the same values as what will be deleted
 */
void deleteData(BST* tree, void* data);

/**
 * Deletes all occurences of a given data value starting from a given root node
 * in a binary search tree.
 * @param tree - the tree to have its data deleted
 * @param node - the root node of the subtree which will be searched
 * @param data - a pointer to data with the same values as what will be deleted
 * @return the new root node of the tree
 */
BSTNode* deleteDataRecursive(BST* tree, BSTNode* node, void* data);

/**
 * Finds the lowest value node below a given root node.
 * @param node - the root of the subtree whose lowest value node will be found
 * @return the node furthest down and to the left of the root
 */
BSTNode* findMin(BSTNode* node);

/**
 * Finds a node with a matching data value in a binary search tree.
 * @param tree - the tree to be searched
 * @param data - the data which is being searched for in the tree
 * @return the first node found to contain the same value as data
 */
BSTNode* findData(BST* tree, void* data);

#endif
