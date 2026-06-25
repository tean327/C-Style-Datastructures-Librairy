#ifndef QUEUES_H_
#define QUEUES_H_

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
void DestroyQueueListString(QueueStringList *head);
// Int queues Funcs
void EnqueueListInt(QueueIntList *head, int value);
QueueIntList *DequeueListInt(QueueIntList *head);
void DestroyQueueListInt(QueueIntList *head);
#pragma endregion
#endif