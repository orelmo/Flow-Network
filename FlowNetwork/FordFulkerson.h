#ifndef _FORDFULKERSON_H
#define _FORDFULKERSON_H
#include<iostream>
#include<math.h>
#include"Graph.h"

using namespace std;

class FordFulkerson
{
public:
	FordFulkerson() = delete;
	static void BFS(Graph & flowNetwork, int sourceVert, int destVert);
	static void Greedy(Graph& flowNetwork, int sourceVert, int destVert);

private:
	static void printValues(Graph& residualGraph, const Graph& flowNetwork, int sourceVert, int iterationCounter, const char* methodName);
	static void printMinCut(int* minCut, int size, int sourceVert);
};
#endif // !_FORDFULKERSON_H