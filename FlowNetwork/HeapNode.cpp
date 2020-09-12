#include "HeapNode.h"
#include<iostream>
using namespace std;

HeapNode::HeapNode(int vert, int weightFromS)
{
	m_Vert = vert;
	m_WeightFromS = weightFromS;
}

int HeapNode::GetVertex() const
{//return vertex
	return m_Vert;
}

int HeapNode::GetWeightFromS() const
{//return the weight
	return m_WeightFromS;
}

void HeapNode::SetWeightFromS(int newWeight)
{//set the weight
	if (newWeight < 0)
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	m_WeightFromS = newWeight;
}

void HeapNode::SetVertex(int vertex)
{//return the vertex number
	if (vertex < 1)
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	m_Vert = vertex;
}