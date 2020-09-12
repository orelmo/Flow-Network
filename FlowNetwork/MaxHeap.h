#ifndef _HEAP_H_
#define _HEAP_H_
#include "HeapNode.h"

class MaxHeap
{
private:
	HeapNode* m_HeapArr;
	int m_MaxSize;
	int m_HeapSize;

	static int left(int nodeIndex);
	static int right(int nodeIndex);
	static int parent(int nodeIndex);
	static void swap(int* node1, int* node2);
	static void swap(HeapNode* node1, HeapNode* node2);
	void fixHeap(int nodeIndex, int* vertexPosInHeap);

public:
	MaxHeap(HeapNode* heapArr, int heapArrSize, int* vertexPosInHeap);
	~MaxHeap();

	void Build(HeapNode* heapArr, int heapArrSize, int* vertexPosInHeap);
	HeapNode DeleteMax(int* vertexPosInHeap);
	bool IsEmpty() const;
	void IncreaseKey(int place, int newKey, int* vertexPosInHeap, int numberOfVerterxes);
};
#endif // !_HEAP_H_