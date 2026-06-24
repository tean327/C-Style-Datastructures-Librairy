#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void AddAtEndOfListChar(char *value, ListChar *head)
{
    ListChar *newNode = (ListChar *)malloc(sizeof(ListChar));
    if (newNode == NULL)
    {
        printf("Unable to allocate memory for new node\n");
        // Exit will end the program with the code 1
        exit(1);
    }
    newNode->VALUE = value;
    newNode->next = NULL;

    if (head->next == NULL)
    {
        head->next = newNode;
    }
    else
    {
        ListChar *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
        return;
    }
}

/// @brief This function is used to only check if a value is inside a list
/// @param head the head of the list
/// @param value the value you want to check if it's inside
/// @return Returns 1 if the value is inside else 0 if it's not
int IsInsideListChar(ListChar *head, char *value)
{
    ListChar *searchNode = head;
    while (searchNode->next != NULL)
    {
        if (strcmp(searchNode->VALUE, value) == 0)
        {
            return 1;
        }
        searchNode = searchNode->next;
    }
    return 0;
}

/// @brief This function is used to get the node from a list based on a parameter value it can also be used to check if a value is inside a list but it's quite to big for only that
/// @param head the head of the list
/// @param value the value you want to check if it's inside
/// @return Returns the node whose value is equal to the parameter if the value is inside else null if it's not
ListChar *GetListCharNodeFromValue(ListChar *head, char *value)
{
    ListChar *searchNode = head;
    while (searchNode->next != NULL)
    {
        if (strcmp(searchNode->VALUE, value) == 0)
        {
            return searchNode;
        }
        searchNode = searchNode->next;
    }
    return NULL;
}

void FreeListCharMemory(ListChar *head)
{
    ListChar *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void AddAtEndOfListInt(int value, ListInt *head)
{
    ListInt *newNode = (ListInt *)malloc(sizeof(ListInt));
    if (newNode == NULL)
    {
        printf("Unable to allocate memory for new node\n");
        // Exit will end the program with the code 1
        exit(1);
    }
    newNode->VALUE = value;
    newNode->next = NULL;

    if (head->next == NULL)
    {
        head->next = newNode;
    }
    else
    {
        ListInt *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
        return;
    }
}

/// @brief This function is used to only check if a value is inside a list
/// @param head the head of the list
/// @param value the value you want to check if it's inside
/// @return Returns 1 if the value is inside else 0 if it's not
int IsInsideListInt(ListInt *head, int value)
{
    ListInt *searchNode = head;
    while (searchNode->next != NULL)
    {
        if (searchNode->VALUE == value)
        {
            return 1;
        }
        searchNode = searchNode->next;
    }
    return 0;
}

/// @brief This function is used to get the node from a list based on a parameter value it can also be used to check if a value is inside a list but it's quite to big for only that
/// @param head the head of the list
/// @param value the value where you want to get the node based of
/// @return Returns the node if the value is inside else null if it's not
ListInt *GetListIntNodeFromValue(ListInt *head, int value)
{
    ListInt *searchNode = head;
    while (searchNode->next != NULL)
    {
        if (searchNode->VALUE == value)
        {
            return searchNode;
        }
        searchNode = searchNode->next;
    }
    return NULL;
}

void FreeListIntMemory(ListInt *head)
{
    ListInt *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
#pragma endregion

#pragma region Stack Functions
#pragma region List Based Stack
void PushListInt(StackListInt **head, int value)
{
    StackListInt *newNode = (StackListInt *)malloc(sizeof(StackListInt));
    newNode->next = *head;
    newNode->val = value;
    *head = newNode;
}

int PopListInt(StackListInt **head)
{
    StackListInt *popNode = (StackListInt *)malloc(sizeof(StackListInt));
    popNode = *head;
    while (popNode->next->next != NULL)
    {
        popNode = popNode->next;
    }
    int val = popNode->next->val;
    free(popNode->next);
    popNode->next = NULL;
    return val;
}

int PeekListInt(StackListInt **head)
{
    StackListInt *popNode = (StackListInt *)malloc(sizeof(StackListInt));
    popNode = *head;
    while (popNode->next != NULL)
    {
        popNode = popNode->next;
    }
    return popNode->val;
}

void PushListString(StackListString **head, char *value)
{
    StackListString *newNode = (StackListString *)malloc(sizeof(StackListString));
    newNode->next = *head;
    strcpy(newNode->val, value);
    *head = newNode;
}

char *PopListString(StackListString **head)
{
    StackListString *popNode = (StackListString *)malloc(sizeof(StackListString));
    popNode = *head;
    while (popNode->next->next != NULL)
    {
        popNode = popNode->next;
    }
    char *val;
    strcpy(val, popNode->next->val);
    free(popNode->next);
    popNode->next = NULL;
    return val;
}

char *PeekListString(StackListString **head)
{
    StackListString *peekNode = (StackListString *)malloc(sizeof(StackListString));
    peekNode = *head;
    while (peekNode->next != NULL)
    {
        peekNode = peekNode->next;
    }
    return *&peekNode->val;
}
#pragma endregion
#pragma region Array Based Stack
void PushArrInt(StackArrInt *stack, int value)
{
    if (stack->indexOfTop + 1 <= 50)
        stack->array[++stack->indexOfTop] = value;
}

int PopArrInt(StackArrInt *stack)
{
    int val = stack->array[stack->indexOfTop];
    stack->array[stack->indexOfTop] = (int)NULL;
    stack->indexOfTop--;
    return val;
}

int PeekArrInt(StackArrInt *stack)
{
    return stack->array[stack->indexOfTop];
}

void PushArrString(StackArrString *stack, char *value)
{
    if (stack->indexOfTop + 1 <= 50)
        strcpy(stack->array[++stack->indexOfTop], value);
}

char *PopArrString(StackArrString *stack)
{
    char *val;
    strcpy(stack->array[stack->indexOfTop], val);
    stack->array[stack->indexOfTop] = (char *)NULL;
    stack->indexOfTop--;
    return val;
}

char *PeekArrString(StackArrString *stack)
{
    return stack->array[stack->indexOfTop];
}
#pragma endregion
#pragma endregion

#pragma region Queues Functions
#pragma region Array Based
// string Queus Funcs
void EnqueueArrStr(QueueStringArr *queue, char *value)
{
    if (queue->size == (int)NULL)
    {
        queue->size = -1;
        queue->frontIndex = 0;
    }
    if (queue->size + 1 <= 50)
    {
        queue->array[++queue->size] = (char *)malloc(sizeof(char *) * strlen(value));
        strcpy(queue->array[queue->size], value);
    }
}
char *DequeueArrStr(QueueStringArr *queue)
{
    char *val = (char *)malloc(sizeof(char) * 25);
    strcpy(val, queue->array[queue->frontIndex]);
    for (int i = 0; i < queue->size - 1; i++)
    {
        strcpy(queue->array[i], queue->array[i + 1]);
    }
    queue->size--;
    return val;
}
// Int queues Funcs
void EnqueueArrInt(QueueIntArr *queue, int value)
{
    if (queue->size == (int)NULL)
    {
        queue->size = -1;
        queue->frontIndex = 0;
    }
    if (queue->size + 1 <= 50)
    {
        queue->array[++queue->size] = value;
    }
}
int DequeueArrInt(QueueIntArr *queue)
{
    int val = queue->array[queue->frontIndex];
    for (int i = 0; i < queue->size - 1; i++)
    {
        queue->array[i] = queue->array[i + 1];
    }
    queue->size--;
    return val;
}
#pragma endregion
#pragma region List Based
// string Queus Funcs
void EnqueueListStr(QueueStringList *head, char *value)
{
    QueueStringList *newNode = (QueueStringList *)malloc(sizeof(QueueStringList));
    newNode->val = (char *)malloc(sizeof(char) * strlen(value));
    printf("gre\n");
    strcpy(newNode->val, value);
    newNode->next = NULL;
    if (head->next == NULL)
    {
        head->next = newNode;
        newNode->previous = head;
        return;
    }

    QueueStringList *tmp = (QueueStringList *)malloc(sizeof(QueueStringList));
    tmp = head;
    while (tmp->next != NULL)
    {
        printf("here\n");
        printf("here%p\n", tmp->next);
        tmp = tmp->next;
    }
    printf("hereeee\n");
    tmp->next = newNode;
    newNode->previous = tmp;
    free(tmp);
}
QueueStringList *DequeueListStr(QueueStringList *head)
{
    QueueStringList *tmp = (QueueStringList *)malloc(sizeof(QueueStringList));
    QueueStringList *returnNode = (QueueStringList *)malloc(sizeof(QueueStringList));
    tmp = head;
    while (tmp->previous != NULL)
    {
        tmp = tmp->previous;
    }
    returnNode = tmp;
    tmp->previous->previous = NULL;
    free(tmp);
    return returnNode;
}
// Int queues Funcs
void EnqueueListInt(QueueIntList *head, int value)
{
}
void DequeueListInt(QueueIntList *head)
{
}
#pragma endregion

void AddAtEndOfListItem(Item *value, ListItem *head)
{
    ListItem *newNode = (ListItem *)malloc(sizeof(ListItem));
    if (newNode == NULL)
    {
        printf("Unable to allocate memory for new node\n");
        // Exit will end the program with the code 1
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;

    ListItem *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}

/// @brief This function is used to get the node from a list based on a parameter value it can also be used to check if a value is inside a list but it's quite to big for only that
/// @param head the head of the list
/// @param value the value you want to check if it's inside
/// @return Returns the node whose value is equal to the parameter if the value is inside else null if it's not
ListItem *GetListItemNodeFromValue(ListItem *head, char *value, int key)
{
    ListItem *searchNode = head->next;
    while (searchNode != NULL)
    {
        if (strcmp(searchNode->value->data, value) == 0 && searchNode->value->key == key)
        {
            return searchNode;
        }
        searchNode = searchNode->next;
    }
    return NULL;
}

void FreeListItemMemory(ListItem *head)
{
    ListItem *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->value->data);
        free(tmp->value);
        free(tmp);
    }
}

HashTable *CreateHashTable(int tableSize)
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (table == NULL)
    {
        printf("Unable to allocate memory for new table\n");
        exit(1);
    }
    table->size = tableSize;
    table->hashData = malloc(tableSize * sizeof(ListItem *));
    if (table->hashData == NULL)
    {
        printf("Unable to allocate memory for new table data\n");
        exit(1);
    }

    for (int i = 0; i < tableSize; i++)
    {
        table->hashData[i] = (ListItem *)malloc(sizeof(ListItem));
        if (table->hashData[i] == NULL)
        {
            printf("Unable to allocate memory for new list item\n");
            exit(1);
        }
        table->hashData[i]->next = NULL;
        table->hashData[i]->value = NULL;
    }
    return table;
}

void DestroyHashTable(HashTable *table)
{
    for (int i = 0; i < table->size; i++)
    {
        FreeListItemMemory(table->hashData[i]);
    }
    free(table->hashData);
    free(table);
}
unsigned int hash(char *str, int hashSize)
{
    int sum = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        sum += str[i];
    }
    return sum % hashSize;
}

void InsertIntoHashTable(char *str, HashTable *table)
{
    int key = hash(str, table->size);
    Item *newItem = (Item *)malloc(sizeof(Item));
    if (newItem == NULL)
    {
        printf("Unable to allocate memory for new item\n");
        exit(1);
    }
    newItem->data = strdup(str);
    newItem->key = key;
    AddAtEndOfListItem(newItem, table->hashData[key]);
    table->count++;
}

ListItem *GetItemInsideTable(HashTable *table, char *str)
{
    int key = hash(str, table->size);
    return GetListItemNodeFromValue(table->hashData[key], str, key);
}
#pragma endregion