#ifndef _LISTNODE_H
#define _LISTNODE_H
#define DUMMY -1

class ListNode
{
	int m_Data;
	ListNode* m_Next;

public:
	ListNode();
	ListNode(int item, ListNode* ptr = nullptr);

	void InsertAfter(ListNode* newNode);
	ListNode* DeleteAfter();

	int GetData() const;
	ListNode* GetNext() const;
};
#endif // !_LISTNODE_H

