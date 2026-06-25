#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} ListItem;

typedef struct NodeHashTable
{
    ListItem **hashData;
    int size;
    int count;
} HashTable;
#pragma endregion

void AddAtEndOfListItem(Item *value, ListItem *head)
{
    ListItem *newNode = (ListItem *)malloc(sizeof(ListItem));
    if (newNode == NULL)
    {
        printf("Unable to allocate memory for new node\n");
        // Exit will end the program with the code 1
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;

    ListItem *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}

/// @brief This function is used to get the node from a list based on a parameter value it can also be used to check if a value is inside a list but it's quite to big for only that
/// @param head the head of the list
/// @param value the value you want to check if it's inside
/// @return Returns the node whose value is equal to the parameter if the value is inside else null if it's not
ListItem *GetListItemNodeFromValue(ListItem *head, char *value, int key)
{
    ListItem *searchNode = head->next;
    while (searchNode != NULL)
    {
        if (strcmp(searchNode->value->data, value) == 0 && searchNode->value->key == key)
        {
            return searchNode;
        }
        searchNode = searchNode->next;
    }
    return NULL;
}

void FreeListItemMemory(ListItem *head)
{
    ListItem *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->value->data);
        free(tmp->value);
        free(tmp);
    }
}

HashTable *CreateHashTable(int tableSize)
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (table == NULL)
    {
        printf("Unable to allocate memory for new table\n");
        exit(1);
    }
    table->size = tableSize;
    table->hashData = malloc(tableSize * sizeof(ListItem *));
    if (table->hashData == NULL)
    {
        printf("Unable to allocate memory for new table data\n");
        exit(1);
    }

    for (int i = 0; i < tableSize; i++)
    {
        table->hashData[i] = (ListItem *)malloc(sizeof(ListItem));
        if (table->hashData[i] == NULL)
        {
            printf("Unable to allocate memory for new list item\n");
            exit(1);
        }
        table->hashData[i]->next = NULL;
        table->hashData[i]->value = NULL;
    }
    return table;
}

void DestroyHashTable(HashTable *table)
{
    for (int i = 0; i < table->size; i++)
    {
        FreeListItemMemory(table->hashData[i]);
    }
    free(table->hashData);
    free(table);
}
unsigned int hash(char *str, int hashSize)
{
    int sum = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        sum += str[i];
    }
    return sum % hashSize;
}

void InsertIntoHashTable(char *str, HashTable *table)
{
    int key = hash(str, table->size);
    Item *newItem = (Item *)malloc(sizeof(Item));
    if (newItem == NULL)
    {
        printf("Unable to allocate memory for new item\n");
        exit(1);
    }
    newItem->data = strdup(str);
    newItem->key = key;
    AddAtEndOfListItem(newItem, table->hashData[key]);
    table->count++;
}

ListItem *GetItemInsideTable(HashTable *table, char *str)
{
    int key = hash(str, table->size);
    return GetListItemNodeFromValue(table->hashData[key], str, key);
}