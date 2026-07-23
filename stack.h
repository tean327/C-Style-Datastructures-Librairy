
#ifndef STACKS_H_
#define STACKS_H_

#define DEFINE_LST_STACK(type)                                                                                                         \
    typedef struct type##_lst_stack                                                                                                    \
    {                                                                                                                                  \
        type val;                                                                                                                      \
        struct type##_lst_stack *next;                                                                                                 \
        /*destroy sert a pointer vers une fonction pour détruire les valeurs de la liste (free notamment)mais par exemple             \
         pour une list de int il ne faut surtout pas les free donc dans ce cas la ou envoie un pointeur NULL dans la fonction create*/ \
        void (*destroy)(void *);                                                                                                       \
        /* besoin de passer par une fonction auxiliaire pour strcmp car elle prend des paramètres de types cont char* et nn char*     \
        et sinon ca compile pas                                                                                                        \
        de cette manière on peut garder la mutabilité des char* avec la comparaison*/                                                \
        int (*compare)(type, type);                                                                                                    \
        type nullValue;                                                                                                                \
                                                                                                                                       \
    } type##_LstStack;                                                                                                                 \
                                                                                                                                       \
    typedef struct type##_value                                                                                                        \
    {                                                                                                                                  \
        type val;                                                                                                                      \
        int state; /* 0 == ok else not ok*/                                                                                            \
    } type##_ReturnValue;                                                                                                              \
                                                                                                                                       \
    type##_LstStack *type##CreateStack(void (*destroyFunc)(void *), int (*compareFunc)(type, type), type nullValue)                    \
    {                                                                                                                                  \
        type##_LstStack *head = (type##_LstStack *)malloc(sizeof(type##_LstStack));                                                    \
        if (!head)                                                                                                                     \
        {                                                                                                                              \
            printf("Unabled to allocated memory for -stack\n");                                                                        \
            return NULL;                                                                                                               \
        }                                                                                                                              \
        head->next = NULL;                                                                                                             \
        head->destroy = destroyFunc;                                                                                                   \
        head->compare = compareFunc;                                                                                                   \
        head->nullValue = nullValue;                                                                                                   \
        return head;                                                                                                                   \
    }                                                                                                                                  \
                                                                                                                                       \
    void type##_PushList(type##_LstStack *head, type value)                                                                            \
    {                                                                                                                                  \
        type##_LstStack *newNode = (type##_LstStack *)malloc(sizeof(type##_LstStack));                                                 \
        if (!newNode)                                                                                                                  \
        {                                                                                                                              \
            printf("Unabled to allocate memory");                                                                                      \
            return;                                                                                                                    \
        }                                                                                                                              \
        if (head->next)                                                                                                                \
            newNode->next = head->next;                                                                                                \
        else                                                                                                                           \
            newNode->next = NULL;                                                                                                      \
        head->next = newNode;                                                                                                          \
        newNode->val = value;                                                                                                          \
    }                                                                                                                                  \
                                                                                                                                       \
    type##_ReturnValue type##_PopList(type##_LstStack *head)                                                                           \
    {                                                                                                                                  \
        if (!head->next)                                                                                                               \
        {                                                                                                                              \
            return (type##_ReturnValue){                                                                                               \
                head->nullValue /*value*/,                                                                                             \
                1 /*state*/                                                                                                            \
            };                                                                                                                         \
        }                                                                                                                              \
        type##_LstStack *popNode = head->next;                                                                                         \
        type val = popNode->val;                                                                                                       \
        head->next = head->next->next;                                                                                                 \
        free(popNode);                                                                                                                 \
        return (type##_ReturnValue){                                                                                                   \
            val /*value*/,                                                                                                             \
            0 /*state*/                                                                                                                \
        };                                                                                                                             \
    }                                                                                                                                  \
                                                                                                                                       \
    type##_ReturnValue type##_PeekList(type##_LstStack *head)                                                                          \
    {                                                                                                                                  \
        if (head->next)                                                                                                                \
            return (type##_ReturnValue){                                                                                               \
                head->next->val /*value*/,                                                                                             \
                0 /*state*/                                                                                                            \
            };                                                                                                                         \
                                                                                                                                       \
        return (type##_ReturnValue){                                                                                                   \
            head->nullValue /*value*/,                                                                                                 \
            1 /*state*/                                                                                                                \
        };                                                                                                                             \
    }                                                                                                                                  \
                                                                                                                                       \
    void type##_DestroyStack(type##_LstStack *head)                                                                                    \
    {                                                                                                                                  \
        type##_LstStack *current = head;                                                                                               \
        while (current != NULL)                                                                                                        \
        {                                                                                                                              \
            type##_LstStack *tmp = current;                                                                                            \
            current = current->next;                                                                                                   \
            if (tmp->destroy)                                                                                                          \
                tmp->destroy((void *)tmp->val);                                                                                        \
            free(tmp);                                                                                                                 \
        }                                                                                                                              \
    }

#define DEFINE_ARR_STACK(type, size)                                                                                           \
    typedef struct type##_arr_stack                                                                                            \
    {                                                                                                                          \
        type array[size];                                                                                                      \
        int indexOfTop;                                                                                                        \
        /*destroy sert a pointer vers une fonction pour détruire les valeurs de la liste (free notamment)mais par exemple     \
         pour une list de int il ne faut surtout pas les free donc dans ce cas la ou envoie un pointeur NULL dans createlist*/ \
        void (*destroy)(void *);                                                                                               \
        type nullValue;                                                                                                        \
    } type##_ArrStack;                                                                                                         \
    typedef struct type##_value                                                                                                \
    {                                                                                                                          \
        type val;                                                                                                              \
        int state; /* 0 == ok else not ok*/                                                                                    \
    } type##_ReturnValue;                                                                                                      \
                                                                                                                               \
    int type##IsFull(type##_ArrStack *stack);                                                                                  \
    int type##IsEmpty(type##_ArrStack *stack);                                                                                 \
                                                                                                                               \
    type##_ArrStack *type##CreateStack(void (*destroyFunc)(void *), type nullValue)                                            \
    {                                                                                                                          \
        type##_ArrStack *stack = (type##_ArrStack *)malloc(sizeof(type##_ArrStack));                                           \
        if (!stack)                                                                                                            \
        {                                                                                                                      \
            printf("Unabled to allocated memory for -stack\n");                                                                \
            return NULL;                                                                                                       \
        }                                                                                                                      \
        stack->indexOfTop = -1;                                                                                                \
        stack->destroy = destroyFunc;                                                                                          \
        stack->nullValue = nullValue;                                                                                          \
        return stack;                                                                                                          \
    }                                                                                                                          \
                                                                                                                               \
    void type##_PushArr(type##_ArrStack *stack, type value)                                                                    \
    {                                                                                                                          \
        if (!type##IsFull(stack))                                                                                              \
            stack->array[++stack->indexOfTop] = value;                                                                         \
    }                                                                                                                          \
                                                                                                                               \
    type##_ReturnValue type##_PopArr(type##_ArrStack *stack)                                                                   \
    {                                                                                                                          \
        if (!type##IsEmpty(stack))                                                                                             \
            return (type##_ReturnValue){                                                                                       \
                stack->array[stack->indexOfTop--] /*value*/,                                                                   \
                0 /*state*/                                                                                                    \
            };                                                                                                                 \
        return (type##_ReturnValue){                                                                                           \
            stack->nullValue /*value*/,                                                                                        \
            1 /*state*/                                                                                                        \
        };                                                                                                                     \
    }                                                                                                                          \
                                                                                                                               \
    type##_ReturnValue type##_PeekArr(type##_ArrStack *stack)                                                                  \
    {                                                                                                                          \
        if (!type##IsEmpty(stack))                                                                                             \
            return (type##_ReturnValue){                                                                                       \
                stack->array[stack->indexOfTop] /*value*/,                                                                     \
                0 /*state*/                                                                                                    \
            };                                                                                                                 \
        return (type##_ReturnValue){                                                                                           \
            stack->nullValue /*value*/,                                                                                        \
            1 /*state*/                                                                                                        \
        };                                                                                                                     \
    }                                                                                                                          \
                                                                                                                               \
    int type##IsFull(type##_ArrStack *stack)                                                                                   \
    {                                                                                                                          \
        return stack->indexOfTop == size - 1;                                                                                  \
    }                                                                                                                          \
                                                                                                                               \
    int type##IsEmpty(type##_ArrStack *stack)                                                                                  \
    {                                                                                                                          \
        return stack->indexOfTop == -1;                                                                                        \
    }                                                                                                                          \
    void type##_DestroyStack(type##_ArrStack *stack)                                                                           \
    {                                                                                                                          \
        if (stack->destroy)                                                                                                    \
        {                                                                                                                      \
            for (int i = 0; i <= stack->indexOfTop; i++)                                                                       \
                stack->destroy((void *)stack->array[i]);                                                                       \
        }                                                                                                                      \
        free(stack);                                                                                                           \
    }
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