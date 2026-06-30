#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFINE_LIST(type)                                                              \
    typedef struct type##_list_node                                                    \
    {                                                                                  \
        type VALUE;                                                                    \
        (void *)destroy;                                                               \
        type##_list_node *next;                                                        \
    } type##ListNode;                                                                  \
                                                                                       \
    type##ListNode *CreateList((void *)destroyFunc)                                    \
    {                                                                                  \
        type##_list_node *head = (type##_list_node *)malloc(sizeof(type##_list_node)); \
        head->next = NULL;                                                             \
        head->destroy = destroyFunc;                                                   \
        return head;                                                                   \
    }                                                                                  \
                                                                                       \
    /*If type is a string you need to pass strdup(value) as parameter*/                \
    void AddAtEndOfListtype##(type * value, type##ListNode * head)                     \
    {                                                                                  \
        type##ListNode *newNode = (type##ListNode *)malloc(sizeof(type##ListNode));    \
        if (newNode == NULL)                                                           \
        {                                                                              \
            printf("Unable to allocate memory for new node\n");                        \
            exit(1);                                                                   \
        }                                                                              \
        newNode->VALUE = value;                                                        \
        newNode->next = NULL;                                                          \
                                                                                       \
        if (head->next == NULL)                                                        \
        {                                                                              \
            head->next = newNode;                                                      \
        }                                                                              \
        else                                                                           \
        {                                                                              \
            type##ListNode *current = head->next;                                      \
            while (current->next != NULL)                                              \
            {                                                                          \
                current = current->next;                                               \
            }                                                                          \
            current->next = newNode;                                                   \
        }                                                                              \
    }                                                                                  \
    type##ListNode *GetListCharNodeFromValue(type##ListNode *head, char *value)        \
    {                                                                                  \
        type##ListNode *searchNode = head->next;                                       \
        while (searchNode != NULL)                                                     \
        {                                                                              \
            if (strcmp(searchNode->VALUE, value) == 0)                                 \
            {                                                                          \
                return searchNode;                                                     \
            }                                                                          \
            searchNode = searchNode->next;                                             \
        }                                                                              \
        return NULL;                                                                   \
    }                                                                                  \
    void FreeListCharMemory(type##ListNode *head)                                      \
    {                                                                                  \
        type##ListNode *tmp;                                                           \
        while (head != NULL)                                                           \
        {                                                                              \
            tmp = head;                                                                \
            head = head->next;                                                         \
            if (tmp->destroy)                                                          \
                tmp->destroy(tmp->VALUE);                                              \
            free(tmp);                                                                 \
        }                                                                              \
    }

#pragma region Structs
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

void AddAtEndOfListChar(char *value, ListChar *head)
{
    ListChar *newNode = (ListChar *)malloc(sizeof(ListChar));
    if (newNode == NULL)
    {
        printf("Unable to allocate memory for new node\n");
        // Exit will end the program with the code 1
        exit(1);
    }
    newNode->VALUE = strdup(value);
    newNode->next = NULL;

    if (head->next == NULL)
    {
        head->next = newNode;
    }
    else
    {
        ListChar *current = head->next;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
        return;
    }
}

/// @brief This function is used to only check if a value is inside a list
/// @param head the head of the list
/// @param value the value you want to check if it's inside
/// @return Returns 1 if the value is inside else 0 if it's not
int IsInsideListChar(ListChar *head, char *value)
{
    ListChar *searchNode = head->next;
    while (searchNode != NULL)
    {
        if (strcmp(searchNode->VALUE, value) == 0)
        {
            return 1;
        }
        searchNode = searchNode->next;
    }
    return 0;
}

/// @brief This function is used to get the node from a list based on a parameter value it can also be used to check if a value is inside a list but it's quite to big for only that
/// @param head the head of the list
/// @param value the value you want to check if it's inside
/// @return Returns the node whose value is equal to the parameter if the value is inside else null if it's not
ListChar *GetListCharNodeFromValue(ListChar *head, char *value)
{
    ListChar *searchNode = head->next;
    while (searchNode != NULL)
    {
        if (strcmp(searchNode->VALUE, value) == 0)
        {
            return searchNode;
        }
        searchNode = searchNode->next;
    }
    return NULL;
}

void FreeListCharMemory(ListChar *head)
{
    ListChar *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void AddAtEndOfListInt(int value, ListInt *head)
{
    ListInt *newNode = (ListInt *)malloc(sizeof(ListInt));
    if (newNode == NULL)
    {
        printf("Unable to allocate memory for new node\n");
        // Exit will end the program with the code 1
        exit(1);
    }
    newNode->VALUE = value;
    newNode->next = NULL;

    if (head->next == NULL)
    {
        head->next = newNode;
    }
    else
    {
        ListInt *current = head->next;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
        return;
    }
}

/// @brief This function is used to only check if a value is inside a list
/// @param head the head of the list
/// @param value the value you want to check if it's inside
/// @return Returns 1 if the value is inside else 0 if it's not
int IsInsideListInt(ListInt *head, int value)
{
    ListInt *searchNode = head->next;
    while (searchNode != NULL)
    {
        if (searchNode->VALUE == value)
        {
            return 1;
        }
        searchNode = searchNode->next;
    }
    return 0;
}

/// @brief This function is used to get the node from a list based on a parameter value it can also be used to check if a value is inside a list but it's quite to big for only that
/// @param head the head of the list
/// @param value the value where you want to get the node based of
/// @return Returns the node if the value is inside else null if it's not
ListInt *GetListIntNodeFromValue(ListInt *head, int value)
{
    ListInt *searchNode = head->next;
    while (searchNode != NULL)
    {
        if (searchNode->VALUE == value)
        {
            return searchNode;
        }
        searchNode = searchNode->next;
    }
    return NULL;
}

void FreeListIntMemory(ListInt *head)
{
    ListInt *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}