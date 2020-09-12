#ifndef _HEAPNODE_H
#define _HEAPNODE_H

#define INF -1
#define NIL -1

class HeapNode
{
	int m_Vert;
	int m_WeightFromS;

public:
	HeapNode(int vert = NIL, int weightFromS = INF);

	int GetVertex() const;
	int GetWeightFromS() const;

	void SetWeightFromS(int newWeight);
	void SetVertex(int vertex);
};

#endif // !_HEAPNODE_H
