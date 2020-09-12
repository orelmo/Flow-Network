#ifndef _POINT_H
#define _POINT_H

class Edge
{
	int m_Source;
	int m_Dest;

public:
	Edge(int source, int dest);
	Edge(Edge& edge);
	
	int GetSource() const;
	int GetDest() const;
};
#endif // !_POINT_H