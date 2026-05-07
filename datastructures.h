
#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

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
#pragma region stack

typedef struct array_int_stack
{
    int array[50];
    int indexOfTop;
} StackArrInt;

typedef struct list_int_stack
{
    int val;
    struct list_int_stack *next;
} StackListInt;

typedef struct array_string_stack
{
    char *array[50];
    int indexOfTop;
} StackArrString;

typedef struct list_string_stack
{
    char *val;
    struct list_string_stack *next;
} StackListString;
#pragma endregion

#pragma region Queue
typedef struct array_queue_int
{
    int array[50];
    int frontIndex;
    int size;
} QueueIntArr;

typedef struct array_queue_string
{
    char *array[50];
    int frontIndex;
    int size;
} QueueStringArr;

typedef struct list_queue_int
{
    int val;
    struct list_queue_int *previous;
    struct list_queue_int *next;
} QueueIntList;

typedef struct list_queue_string
{
    char *val;
    struct list_queue_string *previous;
    struct list_queue_string *next;
} QueueStringList;

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

#pragma region Stack Functions
#pragma region List Based Stack
// int stack funcs
void PushListInt(StackListInt **head, int value);
int PopListInt(StackListInt **head);
int PeekListInt(StackListInt **head);
// string stack funcs
void PushListString(StackListString **head, char *value);
char *PopListString(StackListString **head);
char *PeekListString(StackListString **head);
#pragma endregion
#pragma region Array Based Stack
void PushArrInt(StackArrInt *stack, int value);
int PopArrInt(StackArrInt *stack);
int PeekArrInt(StackArrInt *stack);
#pragma endregion
#pragma endregion
#endif
