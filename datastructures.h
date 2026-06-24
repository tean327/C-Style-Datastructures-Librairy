
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

#pragma region HashTables
typedef struct NodeItem
{
    int key;
    char *data;
} Item;

typedef struct listHashItem
{
    Item *value;
    struct listHashItem *next;
} ListItem;

typedef struct NodeHashTable
{
    ListItem **hashData;
    int size;
    int count;
} HashTable;
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
// int stack funcs
void PushArrInt(StackArrInt *stack, int value);
int PopArrInt(StackArrInt *stack);
int PeekArrInt(StackArrInt *stack);
// string stack funcs
void PushArrString(StackArrString *stack, char *value);
char *PopArrString(StackArrString *stack);
char *PeekArrString(StackArrString *stack);
#pragma endregion
#pragma endregion

#pragma region Queues Functions
#pragma region Array Based
// string Queus Funcs
void EnqueueArrStr(QueueStringArr *queue, char *value);
char *DequeueArrStr(QueueStringArr *queue);
// Int queues Funcs
void EnqueueArrInt(QueueIntArr *queue, int value);
int DequeueArrInt(QueueIntArr *queue);
#pragma endregion
#pragma region List Based
// string Queus Funcs
void EnqueueListStr(QueueStringList *head, char *value);
QueueStringList *DequeueListStr(QueueStringList *head);
// Int queues Funcs
void EnqueueListInt();
void DequeueListInt();
#pragma endregion

#pragma region HashTable
HashTable *CreateHashTable(int tableSize);
void DestroyHashTable(HashTable *table);
unsigned int hash(char *str, int hashSize);
void InsertIntoHashTable(char *str, HashTable *table);
void AddAtEndOfListItem(Item *value, ListItem *head);
ListItem *GetListItemNodeFromValue(ListItem *head, char *value, int key);
void FreeListItemMemory(ListItem *head);
ListItem *GetItemInsideTable(HashTable *table, char *str);
#pragma endregion

#pragma endregion

#endif
