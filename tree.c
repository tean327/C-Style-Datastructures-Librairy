#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma region Tree
typedef struct tree_string
{
    char *val;
    struct tree_string *left;
    struct tree_string *right;
} TreeString;

typedef struct tree_int
{
    int val;
    struct tree_int *left;
    struct tree_int *right;
} TreeInt;
#pragma endregion
int CheckNodeChildren(TreeInt *node, TreeInt *nodeToInsert);

TreeInt *CreateTreeNodeInt(int data)
{
    TreeInt *newNode = (TreeInt *)malloc(sizeof(TreeInt));
    if (!newNode)
    {
        printf("Unabled to allocate memory for a new Tree int node\n");
        return NULL;
    }

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->val = data;

    return newNode;
}

void InsertTreeInt(TreeInt *root, int data)
{
    TreeInt *newNode = CreateTreeNodeInt(data);

    if (!newNode)
        return;

    if (!root)
    {
        root = newNode;
        return;
    }

    TreeInt *crrnt = root;
    TreeInt *nextNode = NULL;

    while (crrnt)
    {
        if (CheckNodeChildren(crrnt, newNode))
            return;
        if (nextNode)
        {
            crrnt = nextNode;
            nextNode = NULL;
        }
        else
        {
            nextNode = crrnt->left;
            crrnt = crrnt->right;
        }
    }
}

int CheckNodeChildren(TreeInt *node, TreeInt *nodeToInsert)
{
    if (!node->right)
    {
        node->right = nodeToInsert;
        return 1;
    }
    else if (!node->left)
    {
        node->left = nodeToInsert;
        return 1;
    }
    return 0;
}

// TODO
// This function need to recreate the tree when deleting a node that has children
int CheckNodeChildrenFromValue(TreeInt *node, int data)
{
    if (node->right->val == data)
    {
        TreeInt *toDelete = node->right;
        node->right = node->right->right;
        free(toDelete);
        return 1;
    }
    if (node->left->val == data)
    {
        TreeInt *toDelete = node->right;
        node->right = node->right->right;
        free(toDelete);
        return 1;
    }

    return 0;
}

void DeleteTreeInt(TreeInt *root, int data)
{
    TreeInt *crrnt = root;
    TreeInt *nextNode = NULL;

    while (crrnt)
    {
        if (CheckNodeChildrenFromValue(crrnt, data))
            return;
        if (nextNode)
        {
            crrnt = nextNode;
            nextNode = NULL;
        }
        else
        {
            nextNode = crrnt->left;
            crrnt = crrnt->right;
        }
    }
}