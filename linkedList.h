#ifndef LINKEDLISTS_H_
#define LINKEDLISTS_H_

#define DEFINE_LIST(type)                                                                                                          \
    typedef struct type##_list_node                                                                                                \
    {                                                                                                                              \
        type VALUE;                                                                                                                \
        /*destroy sert a pointer vers une fonction pour détruire les valeurs de la liste (free notamment)mais par exemple         \
         pour une list de int il ne faut surtout pas les free donc dans ce cas la ou envoie un pointeur NULL dans createlist*/     \
        void (*destroy)(void *);                                                                                                   \
        /* besoin de passer par une fonction auxiliaire pour strcmp car elle prend des paramètres de types cont char* et nn char* \
        et sinonca compile pas                                                                                                     \
        de cette manière on peut garder la mutabilité des char* avec la comparaison*/                                            \
        int (*compare)(type, type);                                                                                                \
        struct type##_list_node *next;                                                                                             \
    } type##_ListNode;                                                                                                             \
                                                                                                                                   \
    type##_ListNode *type##CreateList(void (*destroyFunc)(void *), int (*compareFunc)(type, type))                                 \
    {                                                                                                                              \
        type##_ListNode *head = (type##_ListNode *)malloc(sizeof(type##_ListNode));                                                \
        if (!head)                                                                                                                 \
        {                                                                                                                          \
            printf("Unabled to allocated memory for -list\n");                                                                     \
            return NULL;                                                                                                           \
        }                                                                                                                          \
        head->next = NULL;                                                                                                         \
        head->destroy = destroyFunc;                                                                                               \
        head->compare = compareFunc;                                                                                               \
        return head;                                                                                                               \
    }                                                                                                                              \
                                                                                                                                   \
    /*If type is a string you need to pass strdup(value) as parameter*/                                                            \
    void type##AddAtEndOfList(type##_ListNode *head, type value)                                                                   \
    {                                                                                                                              \
        type##_ListNode *newNode = (type##_ListNode *)malloc(sizeof(type##_ListNode));                                             \
        if (newNode == NULL)                                                                                                       \
        {                                                                                                                          \
            printf("Unable to allocate memory for new node\n");                                                                    \
            exit(1);                                                                                                               \
        }                                                                                                                          \
        newNode->VALUE = value;                                                                                                    \
        newNode->next = NULL;                                                                                                      \
        newNode->compare = head->compare;                                                                                          \
        newNode->destroy = head->destroy;                                                                                          \
        if (head->next == NULL)                                                                                                    \
        {                                                                                                                          \
            head->next = newNode;                                                                                                  \
        }                                                                                                                          \
        else                                                                                                                       \
        {                                                                                                                          \
            type##_ListNode *current = head->next;                                                                                 \
            while (current->next != NULL)                                                                                          \
            {                                                                                                                      \
                current = current->next;                                                                                           \
            }                                                                                                                      \
            current->next = newNode;                                                                                               \
        }                                                                                                                          \
    }                                                                                                                              \
    type##_ListNode *type##GetListNodeFromValue(type##_ListNode *head, type value)                                                 \
    {                                                                                                                              \
        type##_ListNode *searchNode = head->next;                                                                                  \
        while (searchNode != NULL)                                                                                                 \
        {                                                                                                                          \
            if (searchNode->compare)                                                                                               \
            {                                                                                                                      \
                if (searchNode->compare(searchNode->VALUE, value) == 0)                                                            \
                {                                                                                                                  \
                    return searchNode;                                                                                             \
                }                                                                                                                  \
            }                                                                                                                      \
            else                                                                                                                   \
            {                                                                                                                      \
                if (searchNode->VALUE == value)                                                                                    \
                {                                                                                                                  \
                    return searchNode;                                                                                             \
                }                                                                                                                  \
            }                                                                                                                      \
            searchNode = searchNode->next;                                                                                         \
        }                                                                                                                          \
        return NULL;                                                                                                               \
    }                                                                                                                              \
    void type##FreeListMemory(type##_ListNode *head)                                                                               \
    {                                                                                                                              \
        type##_ListNode *tmp;                                                                                                      \
        while (head != NULL)                                                                                                       \
        {                                                                                                                          \
            tmp = head;                                                                                                            \
            head = head->next;                                                                                                     \
            /*ici test de "l'existence" de la fonction destroy si elle est pas null                                                \
             cela veut dire que  et VALUE doit etre free et donc on doit appelé destroy*/                                         \
            if (tmp->destroy)                                                                                                      \
                tmp->destroy((void *)tmp->VALUE);                                                                                  \
            free(tmp);                                                                                                             \
        }                                                                                                                          \
    }

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

#pragma region List Functions
// string List functions
void AddAtEndOfListChar(char *value, ListChar *head);
int IsInsideListChar(ListChar *head, char *value);
ListChar *GetListCharNodeFromValue(ListChar *head, char *value);
void FreeListCharMemory(ListChar *head);
// Int list functions
void AddAtEndOfListInt(int value, ListInt *head);
int IsInsideListInt(ListInt *head, int value);
ListInt *GetListIntNodeFromValue(ListInt *head, int value);
void FreeListIntMemory(ListInt *head);
#pragma endregion
#endif