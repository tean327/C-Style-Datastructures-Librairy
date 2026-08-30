#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    struct list_queue_int *tail;
} QueueIntList;

typedef struct list_queue_string
{
    char *val;
    struct list_queue_string *previous;
    struct list_queue_string *next;
    struct list_queue_string *tail;
} QueueStringList;

typedef struct valueInt
{
    int val;
    int state; /* 0 == ok else not ok*/
} ReturnIntValue;

typedef struct valueStr
{
    char *val;
    int state; /* 0 == ok else not ok*/
} ReturnStrValue;

#pragma endregion

#pragma region Queues Functions
#pragma region Array Based
// string Queus Funcs

QueueStringArr *CreateQueueStringArr()
{
    QueueStringArr *queue = (QueueStringArr *)malloc(sizeof(QueueStringArr));
    if (!queue)
    {
        printf("Unabled to allocate memory for queue string arr\n");
        return NULL;
    }
    queue->frontIndex = -1;
    queue->size = -1;
    return queue;
}

void EnqueueArrStr(QueueStringArr *queue, char *value)
{
    if (queue->size < 0)
    {
        queue->size = -1;
        queue->frontIndex = 0;
    }
    if (queue->size + 1 < 50)
    {
        queue->array[++queue->size] = (char *)malloc(sizeof(char) * (strlen(value) + 1));
        if (!queue->array[queue->size])
        {
            printf("Unabled to allocate memory\n");
            exit(1);
        }
        strcpy(queue->array[queue->size], value);
    }
}
ReturnStrValue DequeueArrStr(QueueStringArr *queue)
{
    if (queue->size < 0)
    {
        return (ReturnStrValue){
            NULL, /*value*/
            0     /*state*/
        };
    }
    char *val = (char *)malloc(sizeof(char) * (strlen(queue->array[queue->frontIndex]) + 1));
    if (!val)
    {
        printf("Unabled to allocate memory\n");
        return (ReturnStrValue){
            NULL, /*value*/
            0     /*state*/
        };
    }

    strcpy(val, queue->array[queue->frontIndex]);

    for (int i = 0; i < queue->size; i++)
    {
        printf("Iteration n°%d, i: %s, i+1: %s\n", i, queue->array[i], queue->array[i + 1]);
        strcpy(queue->array[i], queue->array[i + 1]);
    }
    free(queue->array[queue->size--]);
    return (ReturnStrValue){
        val, /*value*/
        1    /*state*/
    };
}

// Int queues Funcs
QueueIntArr *CreateQueueIntArr()
{
    QueueIntArr *queue = (QueueIntArr *)malloc(sizeof(QueueIntArr));
    if (!queue)
    {
        printf("Unabled to allocate memory for queue int arr\n");
        return NULL;
    }
    queue->frontIndex = -1;
    queue->size = -1;
    return queue;
}

void EnqueueArrInt(QueueIntArr *queue, int value)
{
    if (queue->size < 0)
    {
        queue->size = 0;
        queue->frontIndex = 0;
    }
    if (queue->size + 1 < 50)
    {
        queue->array[++queue->size] = value;
    }
}

ReturnIntValue DequeueArrInt(QueueIntArr *queue)
{
    if (queue->size < 0)
    {
        (ReturnIntValue){
            0, /*value*/
            0  /*state*/
        };
    }
    int val = queue->array[queue->frontIndex];
    for (int i = 0; i < queue->size; i++)
    {
        queue->array[i] = queue->array[i + 1];
    }
    queue->size--;
    return (ReturnIntValue){
        val, /*value*/
        1    /*state*/
    };
    ;
}
#pragma endregion
#pragma region List Based
// string Queus Funcs
int IsQueueStringEmpty(QueueStringList *head)
{
    return head->next == NULL;
}

QueueStringList *CreateQueueString()
{
    QueueStringList *q = malloc(sizeof(QueueStringList));
    q->next = NULL;
    q->previous = NULL;
    q->tail = NULL;
    return q;
}

void EnqueueListStr(QueueStringList *head, char *value)
{
    QueueStringList *newNode = (QueueStringList *)malloc(sizeof(QueueStringList));
    if (!newNode)
    {
        printf("Unable to allocate memory for queue item");
        exit(1);
    }
    newNode->val = (char *)malloc(sizeof(char) * (strlen(value) + 1));
    if (!newNode->val)
    {
        printf("Unable to allocate memory for queue val");
        exit(1);
    }
    strcpy(newNode->val, value);
    newNode->next = NULL;
    newNode->previous = NULL;

    if (head->next == NULL)
    {
        head->next = newNode;
        newNode->previous = NULL;
        head->tail = newNode;
        return;
    }

    QueueStringList *tmp = head->tail;
    head->tail = newNode;
    tmp->next = newNode;
    newNode->previous = tmp;
}

ReturnStrValue DequeueListStr(QueueStringList *head)
{
    if (IsQueueStringEmpty(head))
    {
        return (ReturnStrValue){
            NULL,
            0 /*state*/
        };
    }
    QueueStringList *tmp = head->next;
    head->next = tmp->next;
    if (head->next)
    {
        head->next->previous = NULL;
        head->tail = head->next;
    }
    else
        head->tail = NULL;
    char *val = strdup(tmp->val);
    free(tmp->val);
    free(tmp);
    return (ReturnStrValue){
        val,
        1 /*state*/
    };
}

void DestroyQueueListString(QueueStringList *head)
{
    QueueStringList *tmp = head;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->val);
        free(tmp);
    }
}

// Int queues Funcs

int IsQueueIntEmpty(QueueIntList *head)
{
    return head->next == NULL;
}

QueueIntList *CreateQueueInt()
{
    QueueIntList *q = malloc(sizeof(QueueIntList));
    q->next = NULL;
    q->previous = NULL;
    q->tail = NULL;
    return q;
}

void EnqueueListInt(QueueIntList *head, int value)
{
    QueueIntList *newNode = (QueueIntList *)malloc(sizeof(QueueIntList));
    if (!newNode)
    {
        printf("Unable to allocate memory for queue item");
        exit(1);
    }
    newNode->val = value;
    newNode->next = NULL;

    if (head->next == NULL)
    {
        head->next = newNode;
        newNode->previous = NULL;
        head->tail = newNode;
        return;
    }

    QueueIntList *tmp = head->tail;
    head->tail = newNode;
    tmp->next = newNode;
    newNode->previous = tmp;
    printf("%p\n", newNode);
}

ReturnIntValue DequeueListInt(QueueIntList *head)
{
    if (IsQueueIntEmpty(head))
    {
        return (ReturnIntValue){
            0,
            0 /*state*/
        };
    }
    QueueIntList *tmp = head->next;
    head->next = tmp->next;
    if (head->next)
    {
        head->next->previous = NULL;
        head->tail = head->next;
    }
    else
        head->tail = NULL;
    int val = tmp->val;
    free(tmp);
    return (ReturnIntValue){
        val,
        1 /*state*/
    };
}

void DestroyQueueListInt(QueueIntList *head)
{
    QueueIntList *tmp = head;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
#pragma endregion
#pragma endregion