#include "ListNode.h"

ListNode::ListNode()
{
	m_Data =DUMMY;
	m_Next = nullptr;
}

ListNode::ListNode(int item, ListNode * ptr)
{
	m_Data = item;
	m_Next = ptr;
}

void ListNode::InsertAfter(ListNode * newNode)
{//insert a new node after this node.
	newNode->m_Next = m_Next;
	m_Next = newNode;
}

ListNode * ListNode::DeleteAfter()
{//delete the node that come after this node.
	ListNode* temp = m_Next;
	if (m_Next == nullptr)
	{
		return nullptr;
	}
	m_Next = temp->m_Next;
	return temp;
}

int ListNode::GetData() const
{//return the node data.
	return m_Data;
}

ListNode * ListNode::GetNext() const
{//return the next node.
	return m_Next;
}
