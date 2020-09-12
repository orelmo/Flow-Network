#include "MaxHeap.h"
#include <iostream>
using namespace std;

int MaxHeap::left(int nodeIndex)
{//return the left child index
	return 2 * nodeIndex + 1;
}

int MaxHeap::right(int nodeIndex)
{//return the right child index
	return 2 * nodeIndex + 2;
}

int MaxHeap::parent(int nodeIndex)
{//return the parent index
	return (nodeIndex - 1) / 2;
}

void MaxHeap::fixHeap(int nodeIndex, int* vertexPosInHeap)
{// fix the heap form the nodeIndex to bottom
 //runing time: worst time ϴ(logn), avg time ϴ(logn).
	int max;
	int left = this->left(nodeIndex);
	int right = this->right(nodeIndex);
	if (left < m_HeapSize && m_HeapArr[left].GetWeightFromS() > m_HeapArr[nodeIndex].GetWeightFromS())//left child got bigger key then parent key
		max = left;
	else//left child is not exist or got smaller key then parent key
		max = nodeIndex;
	if (right < m_HeapSize && m_HeapArr[right].GetWeightFromS() > m_HeapArr[max].GetWeightFromS())//right child got bigger key then parent key
		max = right;
	if (max != nodeIndex)//node key is biger then one of his childern 
	{
		swap(&m_HeapArr[nodeIndex], &m_HeapArr[max]);
		swap(&vertexPosInHeap[m_HeapArr[nodeIndex].GetVertex()-1], &vertexPosInHeap[m_HeapArr[max].GetVertex()-1]);
		fixHeap(max, vertexPosInHeap);
	}
}

void MaxHeap::swap(HeapNode* node1, HeapNode* node2)
{
	HeapNode temp = *node1;
	*node1 = *node2;
	*node2 = temp;
}

void MaxHeap::swap(int* node1, int* node2)
{
	int temp = *node1;
	*node1 = *node2;
	*node2 = temp;
}

MaxHeap::~MaxHeap()
{
	if (m_HeapArr != nullptr)
	{
		delete[] m_HeapArr;
	}
}

 HeapNode MaxHeap::DeleteMax(int* vertexPosInHeap)
{//"delete" the node with max key and return it .
	if (m_HeapSize < 1)
	{
		cout << "invalid input\n";
		exit(1);
	}
	HeapNode max = m_HeapArr[0];
	--m_HeapSize;
	m_HeapArr[0] = m_HeapArr[m_HeapSize];
	vertexPosInHeap[m_HeapArr[0].GetVertex()-1] = 0;
	fixHeap(0, vertexPosInHeap);
	return max;
}

bool MaxHeap::IsEmpty() const
{//return true if the heap is empty
	return m_HeapSize==0 ? true:false ;
}

void MaxHeap::IncreaseKey(int v, int newKey,int* vertexPosInHeap,int numberOfVerterxes)
{//bubble up the heap node if his weight bigger then his parent weigth.
	if (v<=0 || v> numberOfVerterxes)
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	if ((vertexPosInHeap[v - 1] == 0 && v == m_HeapArr[0].GetVertex()) || (vertexPosInHeap[v - 1] != 0))
	{//update only vertexes that are inside the heap.
		m_HeapArr[vertexPosInHeap[v - 1]].SetWeightFromS(newKey);
	}
	while (vertexPosInHeap[v - 1] > 0 && newKey > m_HeapArr[parent(vertexPosInHeap[v-1])].GetWeightFromS())
	{//switch parent and child if his weight bigger then his parent weigth.
		int vParent = m_HeapArr[parent(vertexPosInHeap[v - 1])].GetVertex();
		swap(&m_HeapArr[vertexPosInHeap[v-1]], &m_HeapArr[parent(vertexPosInHeap[v-1])]);
		swap(&vertexPosInHeap[v-1], &vertexPosInHeap[vParent-1]);
	}
}

MaxHeap::MaxHeap(HeapNode* heapArr, int heapArrSize, int* vertexPosInHeap)
{
	Build(heapArr, heapArrSize, vertexPosInHeap);
}

void MaxHeap:: Build(HeapNode* heapArr, int heapArrSize,int* vertexPosInHeap)
{//build heap by Floid algorithm
	m_HeapArr = heapArr;
	m_HeapSize = m_MaxSize = heapArrSize;
	for (int i = heapArrSize / 2 - 1; i >= 0; --i)
	{
		fixHeap(i, vertexPosInHeap);
	}
}