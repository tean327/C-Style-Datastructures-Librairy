#ifndef HASH_TABLES_H
#define HASH_TABLES_H

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

#pragma region HashTable
HashTable *CreateHashTable(int tableSize);
void DestroyHashTable(HashTable *table);
unsigned int hash(char *str, int hashSize);
void InsertIntoHashTable(char *str, HashTable *table);
void AddAtEndOfListItem(Item *value, ListItem *head);
ListItem *GetListItemNodeFromValue(ListItem *head, char *value, int key);
void FreeListItemMemory(ListItem *head);
ListItem *GetItemInsideTable(HashTable *table, char *str);
#pragma endregion
#endif