#include "datastructures.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    StackArrInt *stack = (StackArrInt *)malloc(sizeof(StackArrInt));
    stack->indexOfTop = 0;
    stack->array[stack->indexOfTop] = 0;
    printf("%i\n", PeekArrInt(stack));
    PushArrInt(stack, 5);
    printf("%i\n", PeekArrInt(stack));
    PopArrInt(stack);
    printf("%i\n", PeekArrInt(stack));
}