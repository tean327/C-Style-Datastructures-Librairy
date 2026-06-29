
#ifndef STACKS_H_
#define STACKS_H_

#pragma region Struct

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

typedef struct valueInt
{
    int val;
    int state; /* 0 == ok else not ok*/
} ReturnIntValue;

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

typedef struct valueStr
{
    int val;
    int state; /* 0 == ok else not ok*/
} ReturnStrValue;
#pragma endregion

#pragma region Stack Functions
#pragma region List Based Stack
// int stack funcs
StackListInt *CreateIntStack();
void PushListInt(StackListInt **head, int value);
ReturnIntValue PopListInt(StackListInt **head);
ReturnIntValue PeekListInt(StackListInt **head);
void DestroyStackListInt(StackListInt *head);
// string stack funcs
StackListString *CreateStringStack();
void PushListString(StackListString **head, char *value);
ReturnStrValue PopListString(StackListString **head);
ReturnStrValue PeekListString(StackListString *head);
void DestroyStackListString(StackListString *head);
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
#endif