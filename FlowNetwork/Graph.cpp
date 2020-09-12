using namespace std;
#include "Graph.h"

Graph::Graph(int vertNum,int edgesNum)
{
	SetVertsNum(vertNum);
	SetEdgesNum(edgesNum);
	createNewMatrixes(vertNum);
}

Graph::Graph(const Graph & otherGraph)
{
	m_VertexesNum = otherGraph.m_VertexesNum;
	m_EdgesNum = otherGraph.m_EdgesNum;
	m_NeighborsMatrix = new int*[m_VertexesNum];
	m_FlowMatrix = new int*[m_VertexesNum];
	for (int i = 0; i < m_VertexesNum; ++i)
	{
		m_NeighborsMatrix[i] = new int[m_VertexesNum];
		m_FlowMatrix[i] = new int[m_VertexesNum];
	}
	for (int i = 0; i < m_VertexesNum; ++i)
	{
		for (int j = 0; j < m_VertexesNum; ++j)
		{
			m_NeighborsMatrix[i][j] = otherGraph.m_NeighborsMatrix[i][j];
			m_FlowMatrix[i][j] = otherGraph.m_FlowMatrix[i][j];
		}
	}
}

Graph::~Graph()
{
	deleteMatrixes();
}

void Graph::MakeEmptyGraph(int vertexNum)
{//making a new graph with no edges.
	if (vertexNum < 0)
	{
		cout << "invalid Input\n";
		exit(1);
	}
	deleteMatrixes();
	createNewMatrixes(vertexNum);
	m_VertexesNum = vertexNum;
}

bool Graph::IsAdjacent(int vert1, int vert2) const
{//return true if there is an edge between ver1 to vert2.
	if (vert1 > m_VertexesNum || vert2 > m_VertexesNum ||vert1<0 || vert2<0)
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	return m_NeighborsMatrix[vert1][vert2] == 0 ? false : true;
}

List* Graph::GetAdjList(int vert) const
{//return the adjacent list of vert
	if (vert > m_VertexesNum || vert < 0)
	{
		cout << "invalid Input\n";
		exit(1);
	}
	List* adjList= new List();
	for (int i = 0; i < m_VertexesNum; ++i)
	{
		if (m_NeighborsMatrix[vert-1][i] != 0)
		{
			ListNode* newNode=new ListNode(i+1);
			(*adjList).AddToTail(newNode);

		}
	}
	return adjList;
}

void Graph::AddEdge(int vert1, int vert2, int capacity)
{// add adge to the graph
	if (capacity < 1 || vert1 > m_VertexesNum || vert2 > m_VertexesNum || vert1 == vert2 || vert1 < 0 || vert2 < 0
		|| m_NeighborsMatrix[vert1-1][vert2-1] != 0)
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	m_NeighborsMatrix[vert1-1][vert2-1] = capacity;
}

void Graph::RemoveEdge(int vert1, int vert2)
{//remove edge from graph.
	if (vert1 > m_VertexesNum || vert2 > m_VertexesNum)
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	m_NeighborsMatrix[vert1][vert2] = 0;
}

Graph& Graph::GetGraphFromFile(char* fileName, int& sourceVert, int& destVert)
{// reading the graph properties from "fileName" and build a new graph from it.
	int numOfVerts, numOfEdges;
	ifstream myFile;
	myFile.open(fileName);
	if (myFile.is_open() == false)
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	numOfVerts = getNumberFromFile(myFile);
	numOfEdges = getNumberFromFile(myFile);
	sourceVert = getNumberFromFile(myFile);
	destVert = getNumberFromFile(myFile);
	Graph* flowNetwork = new Graph(numOfVerts, numOfEdges);
	FillGraphEdges(*flowNetwork, myFile);
	myFile.close();
	return *flowNetwork;
}

int Graph::getNumberFromFile(ifstream& myFile)
{//read input from file and check if it number
	char checkString[256];
	int num=0,i=0;
	bool characterWasRead = false;
	myFile.getline(checkString, 256);
	skipSpaces(checkString, i);
	while (checkString[i] != '\0')
	{
		if(checkString[i]-'0'<0 || checkString[i] - '0'>9)
		{
			skipSpaces(checkString, i);
			if (checkString[i] == '\0')
			{
				break;
			}
			cout << "Invalid Input";
			exit(1);
		}
		characterWasRead = true;
		num *= 10;
		num += checkString[i] - '0';
		i++;
	}
	if (characterWasRead==false)
	{//nothing was write in the current line on text
		cout << "Invalid Input";
		exit(1);
	}
	return num;
}

void Graph::skipSpaces(char* string, int& index)
{//increament the index to index after the white spaces.
	while (string[index] == ' ' || string[index] == '\t')
	{
		index++;
	}
}

void Graph::FillGraphEdges(Graph& flowNetwork, ifstream& myFile)
{//read the edges properties from file and add them to the graph.
	int outVert, inVert, capacity;
	for (int i = 0; i < flowNetwork.m_EdgesNum; ++i)
	{
		getEdgePropertiesFromFile(myFile,outVert,inVert,capacity);
		flowNetwork.AddEdge(outVert, inVert, capacity);
	}
}

void Graph::getEdgePropertiesFromFile(ifstream& myFile, int& outVert, int& inVert, int& capacity)
{//get and check the edge properties from file.
	char checkString[256];
	int num = 0, i = 0, j = 0;
	int numArr[] = { 0,0,0 };
	myFile.getline(checkString, 256);
	while (checkString[i] != '\0' && j<3)
	{	
		skipSpaces(checkString, i);
		if (checkString[i] == '\0')
		{
			break;
		}
		numArr[j] = extractNumberFromString(checkString,i);
		j++;
	}
	skipSpaces(checkString, i);
	if (j != 3 ||checkString[i]!='\0')
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	outVert = numArr[0];
	inVert = numArr[1];
	capacity = numArr[2];
}

int Graph::extractNumberFromString(char* checkString, int& i)
{//extract nuber from string.
	int num = 0;
	while (checkString[i] != ' ' && checkString[i] != '\t' && checkString[i] != '\0')
	{
		if (checkString[i] - '0' < 0 || checkString[i] - '0'>9)
		{
			cout << "Invalid Input\n";
			exit(1);
		}
		num *= 10;
		num += checkString[i] - '0';
		i++;
	}
	return num;
}

void Graph::SetEdgesNum(int edgesNum)
{//set the edges number
	if (edgesNum < 0)
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	m_EdgesNum = edgesNum;
}

void Graph::SetVertsNum(int vertsNum)
{//set the vertexes number
	if (vertsNum < 0)
	{
		cout << "Invalid Input\n";
		exit(1);
	}
	m_VertexesNum = vertsNum;
}

int Graph::GetVertsNum() const 
{//return the vertexes number
	return m_VertexesNum;
}

int ** Graph::GetCapacityMatrix() const
{//return the capacity of the edges
	return m_NeighborsMatrix;
}

int ** Graph::GetFlowMatrix() const
{//return the flow values 
	return m_FlowMatrix;
}

void Graph::deleteMatrixes()
{//delete matrix
	for (int i = 0; i < m_VertexesNum; ++i)
	{
		delete[] m_NeighborsMatrix[i];
		delete[] m_FlowMatrix[i];
	}
	delete[] m_NeighborsMatrix;
	delete[] m_FlowMatrix;
}

void Graph::createNewMatrixes(int vertNum)
{//create new matrix
	m_NeighborsMatrix = new int*[vertNum];
	m_FlowMatrix = new int*[vertNum];
	for (int i = 0; i < vertNum; ++i)
	{
		m_NeighborsMatrix[i] = new int[vertNum];
		m_FlowMatrix[i] = new int[vertNum];
	}
	for (int i = 0; i < vertNum; ++i)
	{
		for (int j = 0; j < vertNum; ++j)
		{
			m_NeighborsMatrix[i][j] = 0;
			m_FlowMatrix[i][j] = 0;
		}
	}
}

void Graph::InitFlow()
{//initialize flows to 0 
	for (int i = 0; i < m_VertexesNum; ++i)
	{
		for (int j = 0; j < m_VertexesNum; ++j)
		{
			m_FlowMatrix[i][j] = 0;
		}
	}
}

void Graph::FindShortestPath(int** p, int sourceVert, int** d)
{//update p to the shortest pathes tree (BFS)
	Queue queue;
	initSingleSource(sourceVert, p, d);
	queue.EnQueue(sourceVert);
	while (!queue.IsEmpty())
	{
		int curretVert = queue.DeQueue();
		List* neighborsList = GetAdjList(curretVert);
		ListNode* currentNeighbor = neighborsList->GetHead();
		while (currentNeighbor != nullptr)
		{
			if ((*d)[currentNeighbor->GetData() - 1] == INF)
			{
				(*d)[currentNeighbor->GetData() - 1] = (*d)[curretVert - 1] + 1;
				(*p)[currentNeighbor->GetData() - 1] = curretVert;
				queue.EnQueue(currentNeighbor->GetData());
			}
			currentNeighbor = currentNeighbor->GetNext();
		}
		delete neighborsList;
	}
}

int Graph::FindMinCapacity(int* p, int sourceVert, int destVert) const
{//return the min capacity of a path
	int currentVertex = destVert;
	int minCapacity = GetCapacityMatrix()[p[currentVertex - 1] - 1][currentVertex - 1];
	currentVertex = p[currentVertex - 1];
	while (currentVertex != sourceVert)
	{
		if (GetCapacityMatrix()[p[currentVertex - 1] - 1][currentVertex - 1] < minCapacity)
		{
			minCapacity = GetCapacityMatrix()[p[currentVertex - 1] - 1][currentVertex - 1];
		}
		currentVertex = p[currentVertex - 1];
	}
	return minCapacity;
}

void Graph::IncreaseFlow(int* p, int sourceVert, int destVert, int minResidualCapacity)
{// increase the flow of the network by "minResidualCapacity".
	int currentVertex = destVert;
	while (currentVertex != sourceVert)
	{
		GetFlowMatrix()[p[currentVertex - 1] - 1][currentVertex - 1] += minResidualCapacity;
		GetFlowMatrix()[currentVertex - 1][p[currentVertex - 1] - 1] = -1 * (GetFlowMatrix()[p[currentVertex - 1] - 1][currentVertex - 1]);
		currentVertex = p[currentVertex - 1];
	}
}

void Graph::UpdateResidualGraph(const Graph& flowNetwork,int* p, int sourceVert, int destVert, int minResidualCapacity) 
{//update the residual graph by "minResidualCapacity"
	int currentVertex = destVert;
	while (currentVertex != sourceVert)
	{
		GetCapacityMatrix()[p[currentVertex - 1] - 1][currentVertex - 1] =
			flowNetwork.GetCapacityMatrix()[p[currentVertex - 1] - 1][currentVertex - 1] - flowNetwork.GetFlowMatrix()[p[currentVertex - 1] - 1][currentVertex - 1];
		GetCapacityMatrix()[currentVertex - 1][p[currentVertex - 1] - 1] =
			flowNetwork.GetCapacityMatrix()[currentVertex - 1][p[currentVertex - 1] - 1] - flowNetwork.GetFlowMatrix()[currentVertex - 1][p[currentVertex - 1] - 1];
		currentVertex = p[currentVertex - 1];
	}
}

int Graph::CalcMaxFlow(int sourceVert) const
{//return the max flow of the network.
	int maxFlow = 0;
	List* sourceNeighbors = GetAdjList(sourceVert);
	ListNode* currentNeighbor = sourceNeighbors->GetHead();
	while (currentNeighbor != nullptr)
	{
		maxFlow += GetFlowMatrix()[sourceVert - 1][currentNeighbor->GetData() - 1];
		currentNeighbor = currentNeighbor->GetNext();
	}
	delete sourceNeighbors;
	return maxFlow;
}

int* Graph::FindMinCut(int sourceVert) 
{//return the min cut.
	int* d = nullptr, *p = nullptr;
	FindShortestPath(&p, sourceVert, &d);
	delete[] d;
	return p;
}

void Graph::FindHeaviestPath( int** p, int sourceVert, int** d)
{//update p to the heaviest path (Greedy method)
	HeapNode* weightFromS = new HeapNode[GetVertsNum()];
	List* uAdjList = nullptr;
	for (int i = 0; i < GetVertsNum(); ++i)
	{//initialize every heap node 
		weightFromS[i].SetVertex(i + 1);
	}
	weightFromS[sourceVert - 1].SetWeightFromS(0);//source weight = 0.
	initSingleSource(sourceVert, p, d);
	int* vertexPosInHeap = new int[GetVertsNum()];//save the positions of the vertexes in the max heap(heap array).
	for (int i = 0; i < GetVertsNum(); ++i)
	{
		vertexPosInHeap[i] = i;
	}
	MaxHeap heaviestPathHeap(weightFromS,GetVertsNum(), vertexPosInHeap);
	while (!heaviestPathHeap.IsEmpty())
	{//the main loop. finding the heaviest path by relax.
		HeapNode u = heaviestPathHeap.DeleteMax(vertexPosInHeap);
		uAdjList = GetAdjList(u.GetVertex());
		ListNode* currentNeighbor = uAdjList->GetHead();
		while (currentNeighbor != nullptr)
		{
			relax(u.GetVertex(), currentNeighbor->GetData(), *d, *p,heaviestPathHeap, vertexPosInHeap);
			currentNeighbor = currentNeighbor->GetNext();
		}
		delete uAdjList;
	}
	delete[] vertexPosInHeap;
}

void Graph::initSingleSource(int sourceVert, int** p, int**d) const
{//initialize p and d arrays
	*p = new int[GetVertsNum()];
	*d = new int[GetVertsNum()];
	for (int i = 0; i < GetVertsNum(); ++i)
	{
		(*d)[i] = INF;
		(*p)[i] = NIL;
	}
	(*d)[sourceVert - 1] = 0;
}

void Graph::relax(int u, int v, int* d, int* p, MaxHeap& heaviestPathHeap, int* vertexPosInHeap)
{
	if (d[u - 1] == 0)
	{//neghibors of source vertex
		d[v - 1] = GetCapacityMatrix()[u - 1][v - 1];
		p[v - 1] = u;
		heaviestPathHeap.IncreaseKey(v, d[v - 1], vertexPosInHeap,GetVertsNum());
	}
	else if (d[v - 1] < fmin(d[u - 1], GetCapacityMatrix()[u - 1][v - 1]))
	{//other vertexes
		d[v - 1] = fmin(d[u - 1], GetCapacityMatrix()[u - 1][v - 1]);
		p[v - 1] = u;
		heaviestPathHeap.IncreaseKey(v, d[v - 1], vertexPosInHeap, GetVertsNum());
	}
}