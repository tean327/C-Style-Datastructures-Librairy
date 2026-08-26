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
QueueStringArr *CreateQueueStringArr();
void EnqueueArrStr(QueueStringArr *queue, char *value);
ReturnStrValue DequeueArrStr(QueueStringArr *queue);
// Int queues Funcs
QueueIntArr *CreateQueueIntArr();
void EnqueueArrInt(QueueIntArr *queue, int value);
ReturnIntValue DequeueArrInt(QueueIntArr *queue);
#pragma endregion
#pragma region List Based
// string Queus Funcs
QueueStringList *CreateQueueString();
void EnqueueListStr(QueueStringList *head, char *value);
ReturnStrValue DequeueListStr(QueueStringList *head);
void DestroyQueueListString(QueueStringList *head);
int IsQueueStringEmpty(QueueStringList *head);
// Int queues Funcs
QueueIntList *CreateQueueInt();
void EnqueueListInt(QueueIntList *head, int value);
ReturnIntValue DequeueListInt(QueueIntList *head);
void DestroyQueueListInt(QueueIntList *head);
int IsQueueIntEmpty(QueueIntList *head);
#pragma endregion
#endif