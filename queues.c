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

#pragma endregion

#pragma region Queues Functions
#pragma region Array Based
// string Queus Funcs
void EnqueueArrStr(QueueStringArr *queue, char *value)
{
    if (queue->size < 0)
    {
        queue->size = 0;
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
char *DequeueArrStr(QueueStringArr *queue)
{
    char *val = (char *)malloc(sizeof(char) * (strlen(queue->array[queue->frontIndex]) + 1));
    if (!val)
    {
        printf("Unabled to allocate memory\n");
        exit(1);
    }
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

char *DequeueListStr(QueueStringList *head)
{
    QueueStringList *tmp = head->next;
    head->next = tmp->next;
    if (head->next)
        head->next->previous = NULL;
    else
        head->tail = NULL;
    char *val = strdup(tmp->val);
    free(tmp);
    return val;
}

int IsQueueStringEmpty(QueueStringList *head)
{
    return head->next == NULL;
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
}
int DequeueListInt(QueueIntList *head)
{
    QueueIntList *tmp = head->next;
    head->next = tmp->next;
    if (head->next)
        head->next->previous = NULL;
    else
        head->tail = NULL;
    int val = tmp->val;
    free(tmp);
    return val;
}

int IsQueueIntEmpty(QueueIntList *head)
{
    return head->next == NULL;
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