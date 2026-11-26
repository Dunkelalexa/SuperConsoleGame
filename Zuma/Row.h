#pragma once
#include "Utility.h"


struct NodeBall
{
	char color;			//saves the color of the ball
	NodeBall* prev;
	NodeBall* next;

	NodeBall(char clr) 
	{
		color = clr;
		prev = nullptr;
		next = nullptr;
	}
};

class Row
{
private:

	NodeBall* head;
	NodeBall* tail;

	int count;

public:
	Row() 
	{
		head = nullptr;										//initialize it as nullptr
		tail = nullptr;
		count = 0;
	}

	~Row() 
	{
		NodeBall* nodeToDelete = head;						//we start at the head of the list

		while (nodeToDelete != nullptr)						//nullpointer is the end of the list thats why we use it for the while
		{
			NodeBall* nextNode = nodeToDelete->next;		//nextnode is saving the address of the next node
			delete nodeToDelete;							//we delete de node
			nodeToDelete = nextNode;						//since w already had the address of the next node saved we simply move there

		}
	}

	Row(const Row&) = delete;								//we delete the copy constructor
	Row& operator = (const Row&) = delete;					//we also delete the equal assigment opertor

	void AddAtHead(char color)
	{
		NodeBall* nodetoAdd = new NodeBall(color);

		if (head != nullptr)
		{
			nodetoAdd->next = head;
			head->prev = nodetoAdd;
		}
		head = nodetoAdd;

		if (tail == nullptr)
		{
			tail = nodetoAdd;
		}
		count++;
	}

	void AddAtTail(char color)
	{
		NodeBall* nodetoAdd = new NodeBall(color);
		if (tail != nullptr)
		{
			nodetoAdd->prev = tail;
			tail->next = nodetoAdd;
		}

		tail = nodetoAdd;
		if (head == nullptr)
		{
			head = nodetoAdd;
		}

		count++;
	}

	void Insert(int index, char color) 
	{
		if (index < 0 || index > count) 
		{
			return;
		}

		if (index == 0)
		{
			AddAtHead(color);
			return;
		}

		if (index == count)
		{
			AddAtTail(color);
			return;
		}

		NodeBall* nodetoAdd = new NodeBall(color);
		NodeBall* trackingNode = head;
		for (int i = 0; i < index; i++)
		{
			trackingNode = trackingNode->next;
		}

		nodetoAdd->next = trackingNode;
		nodetoAdd->prev = trackingNode->prev;

		trackingNode->prev->next = nodetoAdd;
		trackingNode->prev = nodetoAdd;

		count++;
	}

	void RemoveFirst() 
	{
		if (head == nullptr) 
		{
			return;
		}

		NodeBall* nodeToRemove = head;
		head = head->next;

		if (head != nullptr) {
			head->prev = nullptr;
		}
		else
		{
			tail = nullptr;
		}

		delete nodeToRemove;
		count--;
		
	}

	void RemoveLast() 
	{
		if (tail == nullptr)
		{
			return;
		}

		NodeBall* nodeToRemove = tail;
		tail = tail->prev;

		if (tail != nullptr) 
		{
			tail->next = nullptr;
		}
		else
		{
			head = nullptr;
		}

		delete nodeToRemove;
		count--;
	}

	void RemoveAt(int index) 
	{
		if (index < 0 || index >= count) 
		{
			return;
		}

		if (index == 0)
		{
			RemoveFirst();
			return;
		}

		if (index == count -1)
		{
			RemoveLast();
			return;
		}

		NodeBall* trackingNode = head;
		for (int i = 0; i < index; i++)
		{
			trackingNode = trackingNode->next;
		}

		trackingNode->prev->next = trackingNode->next;
		trackingNode->next->prev = trackingNode->prev;

		delete trackingNode;
		count--;

	}

	int GetCount() const {
		return count;
	}

	char GetColorAt(int index) const 
	{
		if (index < 0 || index >= count)
		{
			return '\0';
		}

		NodeBall* trackingNode = head;
		for (int i = 0; i < index; i++)
		{
			trackingNode = trackingNode->next;
		}

		return trackingNode->color;
	}


	int CountSameLeft (int index) const
	{
		if (index < 0 || index >= count)
		{
			return 0;
		}
		NodeBall* trackingNode = head;
		for (int i = 0; i < index; i++)
		{
			trackingNode = trackingNode->next;
		}

		char targetColor = trackingNode->color;								//saves the color
		int countLeft = 0;													//is going to save the count of the bal to the left

		NodeBall* leftNode = trackingNode->prev;							//leftNode is going to move to the left of the ball we just inserted
		while (leftNode != nullptr && leftNode->color == targetColor)		//we keep going as leftnode is NOT null and the color of the ball is the same as the target color
		{
			countLeft++;													//the count increases when we find a ball of the same color
			leftNode = leftNode->prev;										//we move to the next ball
		}
		return countLeft;													//this is the important number, we will need to know if we have more than 3 balls of the same color together
	}

	int CountSameRight (int index) const 
	{
		if(index < 0 || index >= count)
		{
			return 0;
		}
		NodeBall* trackingNode = head;
		for (int i = 0; i < index; i++)
		{
			trackingNode = trackingNode->next;
		}

		char targetColor = trackingNode->color;								
		int countRight = 0;													

		NodeBall* rightNode = trackingNode->next;							
		while (rightNode != nullptr && rightNode->color == targetColor)		
		{
			countRight++;													
			rightNode = rightNode->next;										
		}
		return countRight;
	}

	int RemoveGroup(int index, int minSize)				//we pass the index where the new ball is inserted, minSize is the number of balls required to trigger the remove group
	{
		if (index < 0 || index >= count)				//check the index is valid
		{
			return 0;
		}

		int left = CountSameLeft(index);				//is calling countsameleft and saving the int in left
		int right = CountSameRight(index);				//is calling countsameright and saving the int in right
		int GroupTotal = left + 1 + right;				//doing the math to get the group that is going to be deleted, the 1 is the ball w just inserted

		if (GroupTotal < minSize) {						//checks the group total is enough to be deleted
			return 0;
		}

		int startIndex = index - left;					//we only go to the left to find where the group starts

		for (int i = 0; i < GroupTotal; i++)			//for as long as i is less than the group total
		{
			RemoveAt(startIndex);						//we call remove at and we pass the start index wich is the index where the firs ball of our group to delete is
		}

		return GroupTotal;


	}

	//for testing the row functions
	void PrintForward()
	{
		NodeBall* current = head;					//we start at the first node

		while (current != nullptr)					//until we pass the last node
		{
			LOG(current->color << " -> ");			//print the color of this node
			current = current->next;				//move to the next node
		}
		LOG_LN("nullptr");							//mark the end of the list
	}

	void PrintBackward()
	{
		NodeBall* current = tail;					//we start at the last node

		while (current != nullptr)					//until we pass the first node
		{
			LOG(current->color << " -> ");
			current = current->prev;				//move to the previous node
		}
		LOG_LN("nullptr");
	}
};