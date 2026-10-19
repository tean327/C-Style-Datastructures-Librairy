#ifndef TREE_H_
#define TREE_H_

#pragma region Structs
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

#pragma region TreeFuncs
int CheckNodeChildren(TreeInt *node, TreeInt *nodeToInsert);
TreeInt *CreateTreeNodeInt(int data);
void InsertTreeInt(TreeInt *root, int data);
#pragma endregion

#endif