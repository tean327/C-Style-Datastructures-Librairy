#ifndef HASH_TABLES_H
#define HASH_TABLES_H

#include"linkedList.h"

#define DEFINE_HASH_TABLE(type)                                                                     \
    typedef struct type##_NodeHashTable  type##_HashTable; /*Déclaration anticipé du struct hashTable*/                                                                          \
    typedef struct type##_NodeItem                                                                  \
    {                                                                                               \
        int key;                                                                                    \
        type data;                                                                                  \
        type##_HashTable* table;                                                                                            \
    } type##_Item;                                                                                  \
                                                                                                    \
    typedef type##_Item* type##_ItemPtr;                                                            \
                                                                                                    \
    DEFINE_LIST(type##_ItemPtr)                                                                     \
                                                                                                    \
    struct type##_NodeHashTable                                                             \
    {                                                                                               \
        type##_ItemPtr_ListNode **hashData;                                                         \
        int size;                                                                                   \
        int count;                                                                                  \
        unsigned int (*hash)(type, int);                                                            \
        /*destroy sert a pointer vers une fonction pour détruire les valeurs de la liste (free notamment)mais par exemple                                           \
         pour une list de int il ne faut surtout pas les free donc dans ce cas la ou envoie un pointeur NULL dans createlist*/                                       \
        void (*destroy)(type *);                                                                                                                                     \
        /* besoin de passer par une fonction auxiliaire pour strcmp car elle prend des paramètres de types cont char* et nn char*                                   \
        et sinonca compile pas                                                                                                                                       \
        de cette manière on peut garder la mutabilité des char* avec la comparaison*/                                                                                \
        int (*compare)(type, type);                                                                                                                                  \
        type (*copy)(type);                                                                   \
    };                                                                             \
                                                                                                    \
                                                                                                    \
    type##_ItemPtr type##_copyItem(type##_ItemPtr item)                                             \
    {                                                                                               \
        type##_ItemPtr cp = malloc(sizeof(type##_Item));                                               \
        if(!cp)                                                                                     \
            return NULL;                                                                            \
        cp->table = item->table;                                                                    \
                                                                                               \
        if(item->table && item->table->copy)                                                                                    \
            cp->data = item->table->copy(item->data);                                                            \
        cp->key = item->key;                                                                        \
        return cp;                                                                                  \
    }                                                                                               \
                                                                                                    \
    void type##_FreeItem(type##_Item** a)                                                                   \
    {                                                                                               \
        if( (*a)->table && (*a)->table->destroy)(*a)->table->destroy(&(*a)->data);                                                                       \
        free(*a);                                                                                            \
    }                                                                                               \
                                                                                                    \
    int type##_CompareItems(type##_ItemPtr a, type##_ItemPtr b)                                     \
    {                                                                                               \
        if(a->table && a->table->compare)                                                                                 \
        {                                                                                           \
            return a->table->compare(a->data, b->data);                                                       \
        }                                                                                           \
        return a->data != b->data;                                                                  \
    }                                                                                               \
                                                                                                    \
    type##_HashTable *type##_CreateHashTable(int tableSize, unsigned int (*hashFunc)(type, int), void (*destroyFunc)(type *), int (*compareFunc)(type, type), type (*copy)(type))             \
    {                                                                                               \
        type##_HashTable *table = (type##_HashTable *)malloc(sizeof(type##_HashTable));             \
        if (!table)                                                                                 \
        {                                                                                           \
            printf("Unable to allocate memory for new table\n");                                    \
            return NULL;                                                                            \
        }                                                                                           \
        table->size = tableSize;                                                                    \
        table->hash = hashFunc;                                                                                \
        table->destroy = destroyFunc;                                                                                \
        table->copy = copy;                                                                                \
        table->compare = compareFunc;                                                                                \
                                                                                                    \
        table->hashData = malloc(tableSize * sizeof(type##_ItemPtr_ListNode *));                    \
        if (!table->hashData)                                                                       \
        {                                                                                           \
            printf("Unable to allocate memory for new table data\n");                               \
            free(table);                                                                            \
            return NULL;                                                                            \
        }                                                                                           \
                                                                                                    \
        for (int i = 0; i < tableSize; i++)                                                         \
        {                                                                                           \
            table->hashData[i] = type##_ItemPtrCreateList(type##_FreeItem, type##_CompareItems, NULL);\
            if (!table->hashData[i])                                                                \
            {                                                                                       \
                printf("Unable to allocate memory for new list item\n");                            \
                free(table->hashData);                                                              \
                free(table);                                                                        \
                return NULL;                                                                        \
            }                                                                                       \
            table->hashData[i]->next = NULL;                                                        \
            table->hashData[i]->VALUE = NULL;                                                       \
            table->hashData[i]->tail = NULL;                                                        \
        }                                                                                           \
        return table;                                                                               \
    }                                                                                               \
                                                                                                    \
    void type##_DestroyHashTable(type##_HashTable **table)                                           \
    {                                                                                              \
        for (int i = 0; i < (*table)->size; i++)                                                       \
        {                                                                                           \
            type##_ItemPtrFreeListMemory(&(*table)->hashData[i]);                                      \
        }                                                                                           \
        free((*table)->hashData);                                                                      \
        free(*table);                                                                                \
    }                                                                                               \
                                                                                                    \
    void type##_InsertIntoHashTable(type val, type##_HashTable *table)                             \
    {                                                                                               \
        int key = table->hash(val, table->size);                                                    \
        type##_Item *newItem = (type##_Item *)malloc(sizeof(type##_Item));                          \
        if (!newItem)                                                                               \
        {                                                                                           \
            printf("Unable to allocate memory for new item\n");                                     \
        }                                                                                           \
        else                                                                                        \
        {                                                                                           \
            newItem->table = table;                                                                             \
            if(table->copy)                                                                                \
            {                                                                                       \
                newItem->data = table->copy(val);                                                          \
                if(!newItem->data)                                                                      \
                {                                                                                       \
                    free(newItem);                                                                      \
                }                                                                                       \
                else                                                                                    \
                {                                                                                       \
                    newItem->key = key;                                                                 \
                    type##_ItemPtrAddAtEndOfList(table->hashData[key], newItem);                        \
                }                                                                                       \
            }                                                                                           \
            else                                                                                        \
            {                                                                                           \
                newItem->data = val;                                                                    \
                newItem->key = key;                                                                 \
                type##_ItemPtrAddAtEndOfList(table->hashData[key], newItem);                        \
            }                                                                                           \
        }                                                                                               \
    }                                                                                                   \
                                                                                                        \
    type##_ItemPtr_ListNode *type##_GetItemInsideTable(type##_HashTable *table, type val)                   \
    {                                                                                                   \
        if(!table->hash) return NULL;                                                                   \
        int key = table->hash(val, table->size);                                                        \
        type##_Item item = {key, val, table};                                            \
        return type##_ItemPtrGetListNodeFromValue(table->hashData[key], &item);                           \
    }                                                                                                   \
                                                                                                        \
    void type##_DeleteFromHashTable(type##_HashTable *table, type val)                                         \
    {                                                                                                   \
        if(!table->hash) return;                                                                   \
        int key = table->hash(val, table->size);                                                        \
                                                                                                        \
        type##_ItemPtr_ListNode *searchNode = table->hashData[key];                                  \
                                                                                                        \
        while (searchNode->next)                                                                        \
        {                                                                                               \
            if(table->compare)                                                                          \
            {                                                                                      \
                if (table->compare(searchNode->next->VALUE->data, val) == 0)                                \
                {                                                                                           \
                    type##_ItemPtr_ListNode* tmp = searchNode->next;                                     \
                    searchNode->next = searchNode->next->next;                                              \
                                                                                                            \
                    if(table->hashData[key]->tail == tmp)                                                   \
                        table->hashData[key]->tail = searchNode;                                            \
                                                                                                            \
                    if(tmp->VALUE)                                                                          \
                    {                                                                                       \
                        if(table->destroy &&tmp->VALUE->data) table->destroy(&tmp->VALUE->data);                                        \
                        type##_FreeItem(&tmp->VALUE);                                                                   \
                    }                                                                                       \
                    free(tmp);                                                                              \
                    break;                                                                                  \
                }                                                                                           \
            }                                                                                               \
            else                                                                                            \
            {                                                                                               \
                if (searchNode->next->VALUE->data == val)                                                   \
                {                                                                                           \
                    type##_ItemPtr_ListNode* tmp = searchNode->next;                                     \
                    searchNode->next = searchNode->next->next;                                              \
                                                                                                            \
                    if(table->hashData[key]->tail == tmp)                                                   \
                        table->hashData[key]->tail = searchNode;                                            \
                                                                                                            \
                    if(tmp->VALUE)                                                                          \
                    {                                                                                       \
                        if(table->destroy &&tmp->VALUE->data) table->destroy(&tmp->VALUE->data);                                        \
                        type##_FreeItem(&tmp->VALUE);                                                                   \
                    }                                                                                       \
                    free(tmp);                                                                              \
                    break;                                                                                \
                }                                                                                           \
            }                                                                                        \
            searchNode = searchNode->next;                                                              \
        }                                                                                               \
    }                                                                                                   


#pragma region HashTables
typedef struct NodeItem
{
    int key;
    char *data;
} Item;

typedef struct listHashItem
{
    Item *value;
    struct listHashItem *next;
    struct listHashItem *tail;
} ListItem;

typedef struct NodeHashTable
{
    ListItem **hashData;
    int size;
    int count;
} HashTable;
#pragma endregion

// #pragma region HashTable
// HashTable *CreateHashTable(int tableSize);
// void DestroyHashTable(HashTable *table);
// unsigned int hash(char *str, int hashSize);
// void InsertIntoHashTable(char *str, HashTable *table);
// int AddAtEndOfListItem(Item *value, ListItem *head);
// ListItem *GetListItemNodeFromValue(ListItem *head, char *value);
// void FreeListItemMemory(ListItem *head);
// ListItem *GetItemInsideTable(HashTable *table, char *str);
// void DeleteFromHashTable(HashTable *table, char *str);
// #pragma endregion
#endif