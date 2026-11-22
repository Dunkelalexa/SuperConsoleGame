#include "Row.h"
#include "Utility.h"

Row::Row()
{
	head = nullptr;									//initialize it as nullptr
	tail = nullptr;
	count = 0;										//initialize the count at 0
}

Row::~Row()											//the destructor is going to release all the memory row used when created
{
	NodeBall* nodeToDelete = head;					//we start at the head of the list
	
	while (nodeToDelete != nullptr)					//nullpointer is the end of the list thats why we use it for the while
	{
		NodeBall* nextNode= nodeToDelete->next;		//nextnode is saving the address of the next node
		delete nodeToDelete;						//we delete de node
		nodeToDelete = nextNode;					//since w already had the address of the next node saved we simply move there
		
	}

}
