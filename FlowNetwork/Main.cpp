/*
Algorithm Course-Final Project
-------------------------------

The project purpose is to compare Ford-Fulkerson method by two different implements to find paths from source vertex
to destination vertex in Flow Network: BFS method, Greedy method.
Operation:
The main function gets a text file name that includes the following parameters:
<num of vertexes>
<num of edges>
<source vertex>
<destination vertex>
<trio of: v-u-capacity>
.
.
.
<trio of: v-u-capacity>
#num of edges trios.

The output is:
BFS Method:
Max flow
Min cut
Number of iterations
Greedy Method:
Max flow
Min Cut
Number of iterations
*/

#include <iostream>
#include "FordFulkerson.h"
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[])
{
	int sourceVert, destVert;
	Graph& flowNetwork = Graph::GetGraphFromFile(argv[1], sourceVert, destVert);
	FordFulkerson::BFS(flowNetwork, sourceVert, destVert);
	flowNetwork.InitFlow();
	FordFulkerson::Greedy(flowNetwork, sourceVert, destVert);
	delete &flowNetwork;
}