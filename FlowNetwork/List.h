#ifndef _LIST_H
#define _LIST_H
#include "ListNode.h"

class List
{
	ListNode* m_Head;
	ListNode* m_Tail;
	int m_Size;

public:
	List();
	~List();

	void MakeEmpty();
	bool IsEmpty() const;
	void AddToTail(ListNode* newNode);
	ListNode* GetHead() const;
};
#endif // !_LIST_H
