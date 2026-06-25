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