#include "datastructures.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    StackListInt head;
    StackListInt *node1 = (StackListInt *)malloc(sizeof(StackListInt));
    node1->val = 1;
    head = *node1;
    printf("HEAD%i\n", head);
    PushListInt(&head, 2);
    printf("HEAD%i\n", head);
}