#ifndef QUEUES_H_
#define QUEUES_H_

#define DEFINE_LST_QUEUE(type)                                                                                                                                                \
    typedef struct type##_lst_queue                                                                                                                                           \
    {                                                                                                                                                                         \
        type val;                                                                                                                                                             \
        struct type##_lst_queue *next;                                                                                                                                        \
        struct type##_lst_queue *previous;                                                                                                                                    \
        struct type##_lst_queue *tail;                                                                                                                                        \
        /*destroy sert a pointer vers une fonction pour détruire les valeurs de la liste (free notamment)mais par exemple                                                    \
         pour une list de int il ne faut surtout pas les free donc dans ce cas la ou envoie un pointeur NULL dans la fonction create*/                                        \
        void (*destroy)(void *);                                                                                                                                              \
        /* besoin de passer par une fonction auxiliaire pour strcmp car elle prend des paramètres de types cont char* et nn char*                                            \
        et sinon ca compile pas                                                                                                                                               \
        de cette manière on peut garder la mutabilité des char* avec la comparaison*/                                                                                       \
        int (*compare)(type, type);                                                                                                                                           \
        void (*print)(struct type##_lst_queue *);                                                                                                                             \
        type (*copy)(type);                                                                                                                                                   \
        type nullValue;                                                                                                                                                       \
                                                                                                                                                                              \
    } type##_LstQueue;                                                                                                                                                        \
                                                                                                                                                                              \
    typedef struct type##_value                                                                                                                                               \
    {                                                                                                                                                                         \
        type val;                                                                                                                                                             \
        int state; /* 0 == not ok else ok*/                                                                                                                                   \
    } type##_ReturnValue;                                                                                                                                                     \
                                                                                                                                                                              \
    type##_LstQueue *type##CreateQueue(void (*destroyFunc)(void *), int (*compareFunc)(type, type), void (*printFunc)(type##_LstQueue *), type (*copy)(type), type nullValue) \
    {                                                                                                                                                                         \
        type##_LstQueue *head = (type##_LstQueue *)malloc(sizeof(type##_LstQueue));                                                                                           \
        if (!head)                                                                                                                                                            \
        {                                                                                                                                                                     \
            printf("Unabled to allocated memory for -stack\n");                                                                                                               \
            return NULL;                                                                                                                                                      \
        }                                                                                                                                                                     \
        head->next = NULL;                                                                                                                                                    \
        head->previous = NULL;                                                                                                                                                \
        head->tail = NULL;                                                                                                                                                    \
        head->destroy = destroyFunc;                                                                                                                                          \
        head->compare = compareFunc;                                                                                                                                          \
        head->nullValue = nullValue;                                                                                                                                          \
        head->print = printFunc;                                                                                                                                              \
        head->copy = copy;                                                                                                                                                    \
        return head;                                                                                                                                                          \
    }                                                                                                                                                                         \
                                                                                                                                                                              \
    int type##_IsQueueStringEmpty(type##_LstQueue *head) { return head->next == NULL; }                                                                                       \
    void type##_EnqueueList(type##_LstQueue *head, type value)                                                                                                                \
    {                                                                                                                                                                         \
        type##_LstQueue *newNode = (type##_LstQueue *)malloc(sizeof(type##_LstQueue));                                                                                        \
        if (!newNode)                                                                                                                                                         \
        {                                                                                                                                                                     \
            printf("Unable to allocate memory for queue item\n");                                                                                                             \
            return;                                                                                                                                                           \
        }                                                                                                                                                                     \
        newNode->destroy = head->destroy;                                                                                                                                     \
        newNode->copy = head->copy;                                                                                                                                           \
        newNode->compare = head->compare;                                                                                                                                     \
        if (newNode->copy)                                                                                                                                                    \
            newNode->val = newNode->copy(value);                                                                                                                              \
        else                                                                                                                                                                  \
            newNode->val = value;                                                                                                                                             \
        if (!head->next)                                                                                                                                                      \
        {                                                                                                                                                                     \
            head->next = newNode;                                                                                                                                             \
            newNode->previous = NULL;                                                                                                                                         \
            head->tail = newNode;                                                                                                                                             \
            return;                                                                                                                                                           \
        }                                                                                                                                                                     \
        type##_LstQueue *tmp = head->tail;                                                                                                                                    \
        head->tail = newNode;                                                                                                                                                 \
        tmp->next = newNode;                                                                                                                                                  \
        newNode->next = NULL;                                                                                                                                                 \
        newNode->previous = tmp;                                                                                                                                              \
    }                                                                                                                                                                         \
    type##_ReturnValue type##_DequeueListStr(type##_LstQueue *head)                                                                                                           \
    {                                                                                                                                                                         \
        if (type##_IsQueueStringEmpty(head))                                                                                                                                  \
        {                                                                                                                                                                     \
            return (type##_ReturnValue){                                                                                                                                      \
                head->nullValue,                                                                                                                                              \
                0 /*state*/                                                                                                                                                   \
            };                                                                                                                                                                \
        }                                                                                                                                                                     \
        type##_LstQueue *tmp = head->next;                                                                                                                                    \
        head->next = tmp->next;                                                                                                                                               \
        if (head->next)                                                                                                                                                       \
        {                                                                                                                                                                     \
            head->next->previous = NULL;                                                                                                                                      \
            head->tail = head->next;                                                                                                                                          \
        }                                                                                                                                                                     \
        else                                                                                                                                                                  \
            head->tail = NULL;                                                                                                                                                \
        type val;                                                                                                                                                             \
        if (tmp->copy)                                                                                                                                                        \
            val = tmp->copy(tmp->val);                                                                                                                                        \
        else                                                                                                                                                                  \
            val = tmp->val;                                                                                                                                                   \
        if (tmp->destroy)                                                                                                                                                     \
            tmp->destroy((void *)tmp->val);                                                                                                                                   \
        free(tmp);                                                                                                                                                            \
        return (type##_ReturnValue){                                                                                                                                          \
            val,                                                                                                                                                              \
            1 /*state*/                                                                                                                                                       \
        };                                                                                                                                                                    \
    }                                                                                                                                                                         \
                                                                                                                                                                              \
    void type##_DestroyQueueList(type##_LstQueue *head)                                                                                                                       \
    {                                                                                                                                                                         \
        type##_LstQueue *tmp = head;                                                                                                                                          \
        while (head)                                                                                                                                                          \
        {                                                                                                                                                                     \
            tmp = head;                                                                                                                                                       \
            head = head->next;                                                                                                                                                \
            if (tmp->destroy)                                                                                                                                                 \
                tmp->destroy(tmp->val);                                                                                                                                       \
            free(tmp);                                                                                                                                                        \
        }                                                                                                                                                                     \
    }

#define DEFINE_ARR_QUEUE(type, Size)                                                                                                                                              \
    typedef struct type##_queue_arr                                                                                                                                               \
    {                                                                                                                                                                             \
        type array[Size];                                                                                                                                                         \
        struct type##_lst_queue *next;                                                                                                                                            \
        struct type##_lst_queue *previous;                                                                                                                                        \
        struct type##_lst_queue *tail;                                                                                                                                            \
        /*destroy sert a pointer vers une fonction pour détruire les valeurs de la liste (free notamment)mais par exemple                                                        \
         pour une list de int il ne faut surtout pas les free donc dans ce cas la ou envoie un pointeur NULL dans la fonction create*/                                            \
        void (*destroy)(void *);                                                                                                                                                  \
        /* besoin de passer par une fonction auxiliaire pour strcmp car elle prend des paramètres de types cont char* et nn char*                                                \
        et sinon ca compile pas                                                                                                                                                   \
        de cette manière on peut garder la mutabilité des char* avec la comparaison*/                                                                                           \
        int (*compare)(type, type);                                                                                                                                               \
        void (*print)(struct type##_queue_arr *);                                                                                                                                 \
        type (*copy)(type);                                                                                                                                                       \
        type nullValue;                                                                                                                                                           \
        int frontIndex;                                                                                                                                                           \
        int size;                                                                                                                                                                 \
    } type##_QueueArr;                                                                                                                                                            \
                                                                                                                                                                                  \
    typedef struct type##_value                                                                                                                                                   \
    {                                                                                                                                                                             \
        type val;                                                                                                                                                                 \
        int state; /* 0 == not ok else ok*/                                                                                                                                       \
    } type##_ReturnValue;                                                                                                                                                         \
    type##_QueueArr *type##_CreateArrQueue(void (*destroyFunc)(void *), int (*compareFunc)(type, type), void (*printFunc)(type##_QueueArr *), type (*copy)(type), type nullValue) \
    {                                                                                                                                                                             \
        type##_QueueArr *queue = (type##_QueueArr *)malloc(sizeof(type##_QueueArr));                                                                                              \
        if (!queue)                                                                                                                                                               \
        {                                                                                                                                                                         \
            printf("Unabled to allocate memory for queue arr");                                                                                                                   \
            return NULL;                                                                                                                                                          \
        }                                                                                                                                                                         \
        queue->frontIndex = -1;                                                                                                                                                   \
        queue->size = -1;                                                                                                                                                         \
        queue->destroy = destroyFunc;                                                                                                                                             \
        queue->compare = compareFunc;                                                                                                                                             \
        queue->print = printFunc;                                                                                                                                                 \
        queue->copy = copy;                                                                                                                                                       \
        queue->nullValue = nullValue;                                                                                                                                             \
        return queue;                                                                                                                                                             \
    }                                                                                                                                                                             \
                                                                                                                                                                                  \
    void type##_EnqueueArr(type##_QueueArr *queue, type value)                                                                                                                    \
    {                                                                                                                                                                             \
        if (queue->size < 0)                                                                                                                                                      \
        {                                                                                                                                                                         \
            queue->size = -1;                                                                                                                                                     \
            queue->frontIndex = 0;                                                                                                                                                \
        }                                                                                                                                                                         \
        if (queue->size + 1 < 50)                                                                                                                                                 \
        {                                                                                                                                                                         \
            if (queue->copy)                                                                                                                                                      \
                queue->array[++queue->size] = queue->copy(value);                                                                                                                 \
            else                                                                                                                                                                  \
                queue->array[++queue->size] = value;                                                                                                                              \
        }                                                                                                                                                                         \
    }                                                                                                                                                                             \
                                                                                                                                                                                  \
    type##_ReturnValue type##_DequeueArr(type##_QueueArr *queue)                                                                                                                  \
    {                                                                                                                                                                             \
        if (queue->size < 0)                                                                                                                                                      \
        {                                                                                                                                                                         \
            return (type##_ReturnValue){                                                                                                                                          \
                queue->nullValue, /*value*/                                                                                                                                       \
                0                 /*state*/                                                                                                                                       \
            };                                                                                                                                                                    \
        }                                                                                                                                                                         \
        type val;                                                                                                                                                                 \
        if (queue->copy)                                                                                                                                                          \
        {                                                                                                                                                                         \
            val = queue->copy(queue->array[queue->frontIndex]);                                                                                                                   \
            if (!val)                                                                                                                                                             \
            {                                                                                                                                                                     \
                return (type##_ReturnValue){                                                                                                                                      \
                    queue->nullValue, /*value*/                                                                                                                                   \
                    0                 /*state*/                                                                                                                                   \
                };                                                                                                                                                                \
            }                                                                                                                                                                     \
        }                                                                                                                                                                         \
        else                                                                                                                                                                      \
            val = queue->array[queue->frontIndex];                                                                                                                                \
        for (int i = 0; i < queue->size; i++)                                                                                                                                     \
        {                                                                                                                                                                         \
            if (queue->copy)                                                                                                                                                      \
                queue->array[i] = queue->copy(queue->array[i + 1]);                                                                                                               \
            else                                                                                                                                                                  \
                queue->array[i] = queue->array[i + 1];                                                                                                                            \
        }                                                                                                                                                                         \
        if (queue->destroy)                                                                                                                                                       \
            queue->destroy(queue->array[queue->size--]);                                                                                                                          \
        else                                                                                                                                                                      \
            queue->size--;                                                                                                                                                        \
        return (type##_ReturnValue){                                                                                                                                              \
            val, /*value*/                                                                                                                                                        \
            1    /*state*/                                                                                                                                                        \
        };                                                                                                                                                                        \
    }                                                                                                                                                                             \
    void type##_DestroyQueueArr(type##_QueueArr *queue)                                                                                                                           \
    {                                                                                                                                                                             \
        if (queue->destroy)                                                                                                                                                       \
            for (int i = 0; i <= queue->size; i++)                                                                                                                                \
                queue->destroy((void *)queue->array[i]);                                                                                                                          \
                                                                                                                                                                                  \
        free(queue);                                                                                                                                                              \
    }

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
#pragma endregion
#endif