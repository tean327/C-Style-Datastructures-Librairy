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