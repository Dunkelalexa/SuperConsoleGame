#include <iostream>
#include "Utility.h"
#include "Row.h"

int main()
{
    Row row;
    row.AddAtTail('R');
    row.AddAtTail('G');
    row.AddAtTail('B');
    row.Insert(1, 'X');
    row.Insert(4, 'Y');
    row.PrintForward();
    return 0;
}