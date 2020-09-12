#ifndef _GRAPH_H
#define _GRAPH_H

#include <fstream>
#include <stdlib.h>
#include <iostream>
#include<string>
#include "List.h"
#include"Queue.h"
#include"MaxHeap.h"

using namespace std;

class Graph
{
	int** m_NeighborsMatrix;
	int** m_FlowMatrix;
	int m_VertexesNum;
	int m_EdgesNum;

public:
	Graph(int vertNum, int edgesNum);
	Graph(const Graph& otherGraph);
	~Graph();

	void MakeEmptyGraph(int vertexNum);
	bool IsAdjacent(int vert1, int vert2) const;
	List* GetAdjList(int vert) const;
	void AddEdge(int vert1, int vert2, int capacity);
	void RemoveEdge(int vert1, int vert2);
	static Graph& GetGraphFromFile(char* fileName, int& sourceVert, int& destVert);
	static void FillGraphEdges(Graph& graph, ifstream& myFile);
	void InitFlow();

	void SetEdgesNum(int edgesNum);
	void SetVertsNum(int vertsNum);
	int GetVertsNum() const;
	int** GetCapacityMatrix() const;
	int** GetFlowMatrix() const;

	void FindShortestPath(int** p, int sourceVert, int** d);
	int FindMinCapacity(int* p, int sourceVert, int destVert) const;
	int* FindMinCut(int sourceVert);
	void IncreaseFlow(int* p, int sourceVert, int destVert, int minResidualCapacity);
	void UpdateResidualGraph(const Graph& flowNetwork, int* p, int sourceVert, int destVert, int minResidualCapacity);
	int CalcMaxFlow(int sourceVert) const;
	void FindHeaviestPath(int** p, int sourceVert, int** d);

private:
	void deleteMatrixes();
	void createNewMatrixes(int vertNum);
	void initSingleSource(int sourceVert, int** p, int**d) const;
	void relax(int u, int v, int* d, int* p, MaxHeap& heaviestPathHeap, int* vertexPosInHeap);
	static int getNumberFromFile(ifstream& myFile);
	static void getEdgePropertiesFromFile(ifstream& myFile, int& utVert, int& inVert, int& capacity);
	static void skipSpaces(char* string, int& index);
	static int extractNumberFromString(char* checkString, int& i);
};
#endif // !_GRAPH_H
