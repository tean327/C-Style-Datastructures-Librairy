#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 50

#pragma region Struct

typedef struct array_int_stack
{
    int array[ARR_SIZE];
    int indexOfTop;
} StackArrInt;

typedef struct list_int_stack
{
    int val;
    struct list_int_stack *next;
} StackListInt;

typedef struct array_string_stack
{
    char *array[ARR_SIZE];
    int indexOfTop;
} StackArrString;

typedef struct list_string_stack
{
    char *val;
    struct list_string_stack *next;
} StackListString;
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
    StackListInt *popNode = *head;
    while (popNode->next != NULL)
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
    StackListInt *popNode = *head;
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
    newNode->val = (char *)malloc(sizeof(char) * (strlen(value) + 1));
    if (!newNode->val)
    {
        printf("Unabled to allocate memory to push\n");
        exit(1);
    }
    strcpy(newNode->val, value);
    *head = newNode;
}

char *PopListString(StackListString **head)
{
    StackListString *popNode = *head;
    while (popNode->next != NULL)
    {
        popNode = popNode->next;
    }
    char *val = (char *)malloc(sizeof(char) * (strlen(popNode->next->val) + 1));
    if (!val)
    {
        printf("Unabled to allocate memory to pop\n");
        exit(1);
    }
    strcpy(val, popNode->next->val);
    free(popNode->next);
    popNode->next = NULL;
    return val;
}

char *PeekListString(StackListString *head)
{
    StackListString *peekNode = head;
    while (peekNode->next != NULL)
    {
        peekNode = peekNode->next;
    }
    return peekNode->val;
}

void DestroyStackListString(StackListString *head)
{
    StackListString *tmp = head;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->val);
        free(tmp);
    }
}

void DestroyStackListInt(StackListInt *head)
{
    StackListInt *tmp = head;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
#pragma endregion
#pragma region Array Based Stack
void PushArrInt(StackArrInt *stack, int value)
{
    if (stack->indexOfTop + 1 < ARR_SIZE)
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
    if (stack->indexOfTop + 1 < ARR_SIZE)
    {
        stack->array[++stack->indexOfTop] = (char *)malloc(sizeof(char) * (strlen(value) + 1));
        if (!stack->array[stack->indexOfTop])
        {
            printf("Unabled to allocate memory\n");
            exit(1);
        }
        strcpy(stack->array[stack->indexOfTop], value);
    }
}

char *PopArrString(StackArrString *stack)
{
    char *val = (char *)malloc(sizeof(char) * (strlen(stack->array[stack->indexOfTop]) + 1));
    if (!val)
    {
        printf("Unabled to allocate memory\n");
        exit(1);
    }
    strcpy(val, stack->array[stack->indexOfTop]);
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