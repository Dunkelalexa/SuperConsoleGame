#include <iostream>
#include "Utility.h"
#include "Row.h"

int main()
{
    Row row;
    row.AddAtHead('R');
    row.AddAtHead('G');
    row.AddAtTail('R');
    row.AddAtTail('G');
    row.AddAtTail('B');
    row.AddAtHead('G');
    LOG_LN(row.GetCount());
    LOG_LN(row.GetColorAt(5));
    return 0;
}