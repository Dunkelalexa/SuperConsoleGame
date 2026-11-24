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
	Row() {
		head = nullptr;									//initialize it as nullptr
		tail = nullptr;
		count = 0;
	}

	~Row() {
		NodeBall* nodeToDelete = head;					//we start at the head of the list

		while (nodeToDelete != nullptr)					//nullpointer is the end of the list thats why we use it for the while
		{
			NodeBall* nextNode = nodeToDelete->next;		//nextnode is saving the address of the next node
			delete nodeToDelete;						//we delete de node
			nodeToDelete = nextNode;					//since w already had the address of the next node saved we simply move there

		}
	}

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



	//for testing the row
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