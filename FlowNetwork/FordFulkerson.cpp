#include "FordFulkerson.h"

void FordFulkerson::BFS(Graph & flowNetwork, int sourceVert, int destVert)
{//implementation of Ford-Falkerson method by using BFS to find path.
	Graph residualGraph(flowNetwork);
	int iterationCounter = 0;
	int* d=nullptr, *p=nullptr;
	bool isDestAccessable = false;
	residualGraph.FindShortestPath(&p, sourceVert, &d);
	if (p[destVert-1] != NIL)
	{//check if there is an accessible path to dest vertex.
		isDestAccessable = true;
	}
	while (isDestAccessable)
	{//the main loop, increase flow while there is a path to the destination.
		++iterationCounter;
		int minResidualCapacity = residualGraph.FindMinCapacity(p,sourceVert,destVert);
		flowNetwork.IncreaseFlow(p, sourceVert, destVert, minResidualCapacity);
		residualGraph.UpdateResidualGraph(flowNetwork, p, sourceVert, destVert, minResidualCapacity);
		delete[] d;
		delete[] p;
		residualGraph.FindShortestPath(&p, sourceVert, &d);
		if (p[destVert-1] == NIL)
		{
			isDestAccessable = false;
		}

	}
	printValues(residualGraph,flowNetwork, sourceVert, iterationCounter,"BFS");
	delete[] d;
	delete[] p;
}


void FordFulkerson::printValues(Graph& residualGraph,const Graph& flowNetwork,int sourceVert,int iterationCounter,const char* methodName)
{//print the flow network values.
	int maxFlow=flowNetwork.CalcMaxFlow(sourceVert);
	cout << methodName <<" Method:\n" << "Max flow = " << maxFlow << "\n";
	int* minCut = residualGraph.FindMinCut(sourceVert);
	printMinCut(minCut, residualGraph.GetVertsNum(),sourceVert);
	delete[] minCut;
	cout << "Number of iteration = " << iterationCounter << "\n";
}

void FordFulkerson::printMinCut(int* minCut,int size,int sourceVert)
{//print the min cut.
	bool isFirst = true;
	cout << "Min cut: S = ";
	for (int i = 0; i < size; ++i)
	{
		if (minCut[i] != NIL || i == sourceVert-1)
		{
			if (!isFirst)
			{
				cout << ", ";
			}
			cout << i + 1;
			isFirst = false;
		}		
	}
	cout << ". T = ";
	isFirst = true;
	for (int i = 0; i < size; ++i)
	{
		if (minCut[i] == NIL && i != sourceVert-1)
		{
			if (!isFirst)
			{
				cout << ", ";
			}
			cout << i + 1;
			isFirst = false;
		}
	}
	cout << "\n";
}

void FordFulkerson::Greedy(Graph& flowNetwork, int sourceVert, int destVert)
{//implementation of Ford-Falkerson by using greedy method to find path.
	Graph residualGraph(flowNetwork);
	int iterationCounter = 0;
	int* d = nullptr, *p = nullptr;
	bool isDestAccessable = false;
	residualGraph.FindHeaviestPath( &p, sourceVert, &d);
	if (p[destVert - 1] != NIL)
	{//check if there is an accessible path to dest vertex.
		isDestAccessable = true;
	}
	while (isDestAccessable)
	{//the main loop, increase flow while there is a path to the destination.
		++iterationCounter;
		int minResidualCapacity = residualGraph.FindMinCapacity( p, sourceVert, destVert);
		flowNetwork.IncreaseFlow(p, sourceVert, destVert, minResidualCapacity);
		residualGraph.UpdateResidualGraph(flowNetwork, p, sourceVert, destVert, minResidualCapacity);
		delete[] d;
		delete[] p;
		residualGraph.FindHeaviestPath(&p, sourceVert, &d);
		if (p[destVert - 1] == NIL)
		{
			isDestAccessable = false;
		}
	}
	printValues(residualGraph, flowNetwork, sourceVert, iterationCounter,"Greedy");
	delete[] d;
	delete[] p;
}