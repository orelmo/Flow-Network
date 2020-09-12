#include "Queue.h"
#include<iostream>
using namespace std;

Queue::Queue()
{
	m_Head = new ListNode();
	m_Tail = m_Head;
}

Queue::~Queue()
{
	MakeEmpty();
	delete m_Head;
}

void Queue::MakeEmpty()
{//make empty queue.
	ListNode* currentNode = m_Head;
	ListNode* toDelete;
	while (currentNode != nullptr)
	{
		toDelete = currentNode;
		currentNode = currentNode->GetNext();
		delete toDelete;
	}
	m_Head = new ListNode();
	m_Tail = m_Head;
}

bool Queue::IsEmpty() const
{//return true if the queue is empty.
	return m_Head==m_Tail;
}

void Queue::EnQueue(int data)
{//insert a new node with value "data" to the queue.
	ListNode* newNode = new ListNode(data);
	m_Tail->InsertAfter(newNode);
	m_Tail = newNode;
}

int Queue::DeQueue()
{//delete the first node in the queue and return it.
	if (IsEmpty())
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	ListNode* temp = m_Head->DeleteAfter();
	int item = temp->GetData();
	if (m_Tail == temp)
	{
		m_Tail = m_Head;
	}
	delete temp;
	return item;
}
