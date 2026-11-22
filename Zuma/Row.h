#pragma once


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
};