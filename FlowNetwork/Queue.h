#ifndef _QUEUE_H
#define _QUEUE_H
#include "ListNode.h"

class Queue
{
	ListNode* m_Head;
	ListNode* m_Tail;
public:
	Queue();
	~Queue();

	void MakeEmpty();
	bool IsEmpty() const;
	void EnQueue(int data);
	int DeQueue();
};
#endif // !_QUEUE_H

