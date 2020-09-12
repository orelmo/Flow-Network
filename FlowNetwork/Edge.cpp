#include "Edge.h"

Edge::Edge(int source, int dest)
{
	m_Source = source;
	m_Dest = dest;
}

Edge::Edge(Edge & edge)
{
	m_Dest = edge.GetDest();
	m_Source = edge.GetSource();
}

int Edge::GetSource() const
{//return source vertex
	return m_Source;
}

int Edge::GetDest() const
{//return destination vertex
	return m_Dest;
}
