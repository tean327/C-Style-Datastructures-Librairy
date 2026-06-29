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

typedef struct valueInt
{
    int val;
    int state; /* 0 == ok else not ok*/
} ReturnIntValue;

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

typedef struct valueStr
{
    int val;
    int state; /* 0 == ok else not ok*/
} ReturnStrValue;
#pragma endregion

#pragma region Stack Functions
#pragma region List Based Stack

StackListInt *CreateintStack()
{
    StackListInt *head = (StackListInt *)malloc(sizeof(StackListInt));
    if (!head)
    {
        printf("Unabled to allocate memory");
        return NULL;
    }
    head->next = NULL;
    return head;
}

void PushListInt(StackListInt *head, int value)
{
    StackListInt *newNode = (StackListInt *)malloc(sizeof(StackListInt));
    if (!newNode)
    {
        printf("Unabled to allocate memory");
        return;
    }
    if (head->next)
        newNode->next = head->next;
    else
        newNode->next = NULL;
    head->next = newNode;
    newNode->val = value;
}

ReturnIntValue PopListInt(StackListInt *head)
{
    if (!head->next)
    {
        return (ReturnIntValue){
            0 /*value*/,
            1 /*state*/
        };
    }
    StackListInt *popNode = head->next;
    int val = popNode->val;
    head->next = head->next->next;
    free(popNode);
    return (ReturnIntValue){
        val /*value*/,
        0 /*state*/
    };
}

ReturnIntValue PeekListInt(StackListInt *head)
{
    if (head->next)
        return (ReturnIntValue){
            head->next->val /*value*/,
            0 /*state*/
        };

    return (ReturnIntValue){
        0 /*value*/,
        1 /*state*/
    };
}

void DestroyStack(StackListInt *head)
{
    StackListInt *current = head;
    while (current != NULL)
    {
        StackListInt *tmp = current;
        current = current->next;
        free(tmp);
    }
}

StackListString *CreateStringStack()
{
    StackListString *head = (StackListString *)malloc(sizeof(StackListString));
    if (!head)
    {
        printf("Unabled to allocate memory");
        return NULL;
    }
    head->next = NULL;
    return head;
}

void PushListString(StackListString *head, char *value)
{
    StackListString *newNode = (StackListString *)malloc(sizeof(StackListString));
    if (!newNode)
    {
        printf("Unabled to allocate memory");
        return;
    }
    if (head->next)
        newNode->next = head->next;
    else
        newNode->next = NULL;
    head->next = newNode;
    newNode->val = strdup(value);
}

ReturnStrValue PopListInt(StackListString *head)
{
    if (!head->next)
    {
        return (ReturnStrValue){
            0 /*value*/,
            1 /*state*/
        };
    }
    StackListString *popNode = head->next;
    int val = popNode->val;
    head->next = head->next->next;
    free(popNode);
    return (ReturnStrValue){
        val /*value*/,
        0 /*state*/
    };
}

ReturnStrValue PeekListInt(StackListString *head)
{
    if (head->next)
        return (ReturnStrValue){
            head->next->val /*value*/,
            0 /*state*/
        };

    return (ReturnStrValue){
        0 /*value*/,
        1 /*state*/
    };
}

void DestroyStackListString(StackListString *head)
{
    StackListString *current = head;
    while (current != NULL)
    {
        StackListString *tmp = current;
        current = current->next;
        free(tmp->val);
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