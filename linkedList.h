#ifndef LINKEDLISTS_H_
#define LINKEDLISTS_H_

#pragma region List
typedef struct ListIntNode
{
    int VALUE;
    struct ListIntNode *next;
} ListInt;

typedef struct ListCharNode
{
    char *VALUE;
    struct ListCharNode *next;
} ListChar;
#pragma endregion

#pragma region List Functions
// string List functions
void AddAtEndOfListChar(char *value, ListChar *head);
int IsInsideListChar(ListChar *head, char *value);
ListChar *GetListCharNodeFromValue(ListChar *head, char *value);
void FreeListCharMemory(ListChar *head);
// Int list functions
void AddAtEndOfListInt(int value, ListInt *head);
int IsInsideListInt(ListInt *head, int value);
ListInt *GetListIntNodeFromValue(ListInt *head, int value);
void FreeListIntMemory(ListInt *head);
#pragma endregion
#endif