#include "List.h"

List::List()
{
	m_Head = nullptr;
	m_Tail = nullptr;
	m_Size = 0;
}

List::~List()
{
	MakeEmpty();
}

void List::MakeEmpty()
{//make empty list.
	ListNode* currentNode = m_Head;
	ListNode* toDelete;
	while (currentNode != nullptr)
	{
		toDelete = currentNode;
		currentNode = currentNode->GetNext();
		delete toDelete;
	}
	m_Head = nullptr;
	m_Tail = nullptr;
	m_Size = 0;
}

bool List::IsEmpty() const
{//return true if the list is empty
	return m_Head == nullptr;
}

void List::AddToTail(ListNode * newNode)
{//add node to the end of the list.
	if (IsEmpty())
	{
		m_Head=m_Tail = newNode;
	}
	else
	{
		m_Tail->InsertAfter(newNode);
		m_Tail = newNode;
	}
	m_Size++;
}

ListNode * List::GetHead() const
{//return the first node of the list.
	return m_Head;
}
