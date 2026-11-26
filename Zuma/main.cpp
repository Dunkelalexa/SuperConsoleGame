#include <iostream>
#include "Utility.h"
#include "Row.h"

int main()
{
    Row row;
    row.AddAtTail('G');
    row.AddAtTail('G');
    row.AddAtTail('G');
    row.AddAtTail('R');
    LOG_LN(row.RemoveGroup(0, 3));
    row.PrintForward();
    row.PrintBackward();
    return 0;
}